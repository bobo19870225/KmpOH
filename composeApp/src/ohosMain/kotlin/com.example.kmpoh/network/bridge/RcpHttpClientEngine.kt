@file:OptIn(io.ktor.utils.io.InternalAPI::class)

package com.example.kmpoh.network.bridge

import io.ktor.client.engine.HttpClientEngineBase
import io.ktor.client.engine.HttpClientEngineCapability
import io.ktor.client.engine.HttpClientEngineConfig
import io.ktor.client.engine.callContext
import io.ktor.client.plugins.HttpTimeoutCapability
import io.ktor.client.request.HttpRequestData
import io.ktor.client.request.HttpResponseData
import io.ktor.http.Headers
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpProtocolVersion
import io.ktor.http.HttpStatusCode
import io.ktor.http.content.OutgoingContent
import io.ktor.util.date.GMTDate
import io.ktor.util.decodeBase64Bytes
import io.ktor.util.encodeBase64
import com.example.kmpoh.network.BridgeWireBody
import com.example.kmpoh.network.toBridgeWireBody
import io.ktor.utils.io.ByteReadChannel
import io.ktor.utils.io.readRemaining
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.JsonObject
import kotlinx.serialization.json.buildJsonObject
import kotlinx.serialization.json.contentOrNull
import kotlinx.serialization.json.int
import kotlinx.serialization.json.intOrNull
import kotlinx.serialization.json.jsonObject
import kotlinx.serialization.json.jsonPrimitive
import kotlinx.serialization.json.put
import kotlinx.serialization.json.putJsonObject
import kotlinx.io.readByteArray
import kotlin.coroutines.CoroutineContext

/**
 * 鸿蒙自定义 HTTP 引擎：把 Ktor 请求序列化成桥接 JSON，经 [OhosHttpTransport]
 * 交给 ArkTS RCP（RemoteCommunicationKit，系统 TLS 栈）执行，再还原为 [HttpResponseData]。
 *
 * 背景见 [OhosHttpTransport]：ktor-network-tls nonJvm 是 error() 桩，CIO 无法做 TLS，
 * HTTPS 在 Native 上不可用，鸿蒙端必须桥接系统网络栈。
 *
 * 线协议（两侧同构，改一侧必改另一侧，ArkTS 端在
 * harmonyApp/entry/src/main/ets/network/HttpBridge.ets）：
 * - 请求：`{ url, method, headers, bodyJson?|bodyForm?|bodyMultipart?|bodyBase64? }`
 *   （JSON body 传**文本**、ArkTS 侧 JSON.parse 成对象后交 RCP——与 Technician-Harmony
 *   传 Record 的路径同款，RCP 按对象自动以 application/json 发出；表单/multipart 传**字段表**、
 *   ArkTS 侧分别用 rcp.Form / rcp.MultipartForm（application/x-www-form-urlencoded 与
 *   multipart/form-data，与原工程 @FormUrlEncoded/@Multipart 同形）；二进制才走 bodyBase64。
 *   裸 string/ArrayBuffer 会被 RCP 按 text/plain/octet-stream 发出，服务端读不到参数
 *   （实测登录报"请输入账号"、dayOrder 报"请选择日期"），表单/multipart **禁止**降级为 bodyBase64。
 *   请求体形态编码统一在 commonMain 的 BridgeWireBody.kt（有单测），此处只做序列化）
 * - 成功响应（任意 HTTP 状态码原样透传，由 ktor 层判非 2xx）：`{ status, headers, bodyBase64 }`
 * - 传输失败：`{ error, rcpCode }`（rcpCode 为 RCP BusinessError 码，
 *   映射语义对齐 Technician-Harmony 的 HttpError.fromRcpError）
 *
 * 两条铁律：
 * 1. 传输层头（Content-Length/Host/Connection 等）禁止转发给 RCP——冲突会造成 body 截断/悬挂；
 * 2. 响应 callContext 必须用 ktor 的 [callContext]（独立 callJob）——若把 `data.executionContext`
 *    直接传入，HttpTimeout 的 30s killer 子 Job 会与调用 Job 互相等待，每次请求固定卡满
 *    requestTimeout 才返回（nova 13 实测）。
 */
internal class RcpHttpClientEngine : HttpClientEngineBase("RcpBridge") {

    override val config: HttpClientEngineConfig = HttpClientEngineConfig()

    // HttpTimeout 插件 setCapability 时会 require 引擎声明该能力（否则抛
    // "Engine doesn't support HttpTimeoutCapability"）。声明后整体 requestTimeout 仍由
    // 插件级 withTimeout 兜底；connect/socket 超时由 ArkTS RCP 会话配置承担
    //（10s/30s，见 HttpBridge.ets），插件传入的逐请求超时暂不透传给桥。
    override val supportedCapabilities: Set<HttpClientEngineCapability<*>> = setOf(HttpTimeoutCapability)

    override suspend fun execute(data: HttpRequestData): HttpResponseData {
        val requestJson = encodeRequest(data)
        val responseJson = OhosHttpTransport.execute(requestJson)
        // callContext() 提供 ktor 创建的独立 callJob（见文件头铁律 2）
        return decodeResponse(responseJson, callContext())
    }

    /** 传输层头黑名单：由 RCP/系统网络栈自行管理，转发会与实际 body 冲突。 */
    private val hopByHopHeaders = setOf(
        "content-length", "host", "connection", "keep-alive",
        "transfer-encoding", "accept-encoding", "content-encoding",
        "upgrade", "te", "trailer", "proxy-authorization", "proxy-connection"
    )

    private suspend fun encodeRequest(data: HttpRequestData): String {
        val content = data.body
        val headers = mutableMapOf<String, String>()
        fun merge(h: Headers) {
            h.forEach { name, values ->
                if (name.lowercase() !in hopByHopHeaders) {
                    headers[name] = if (values.size == 1) values[0] else values.joinToString(", ")
                }
            }
        }
        merge(data.headers)
        merge(content.headers)

        // 请求体 → 线协议形态（bodyJson/bodyForm/bodyMultipart/bodyBase64 的编码规则与
        // 「表单为何不能走裸 ArrayBuffer」见 BridgeWireBody.kt，有单测钉回归）。
        // 流式内容在此读成字节；其余形态由公共编码统一处理。
        val wireBody = if (content is OutgoingContent.ReadChannelContent) {
            BridgeWireBody(bodyBase64 = content.readFrom().readRemaining().readByteArray().encodeBase64())
        } else {
            content.toBridgeWireBody()
        }

        return buildJsonObject {
            put("url", data.url.toString())
            put("method", data.method.value)
            putJsonObject("headers") {
                headers.forEach { (name, value) -> put(name, value) }
            }
            wireBody.bodyJson?.let { put("bodyJson", it) }
            wireBody.bodyBase64?.let { put("bodyBase64", it) }
            wireBody.bodyForm?.let { fields ->
                putJsonObject("bodyForm") { fields.forEach { (name, value) -> put(name, value) } }
            }
            wireBody.bodyMultipart?.let { fields ->
                putJsonObject("bodyMultipart") { fields.forEach { (name, value) -> put(name, value) } }
            }
        }.toString()
    }

    private fun decodeResponse(responseJson: String, callContext: CoroutineContext): HttpResponseData {
        val root = try {
            Json.parseToJsonElement(responseJson).jsonObject
        } catch (cause: Throwable) {
            throw IllegalStateException("HTTP 桥响应非法 JSON", cause)
        }
        val error = root["error"]?.jsonPrimitive?.contentOrNull?.takeIf { it.isNotEmpty() }
        if (error != null) {
            throw mapRcpFailure(root["rcpCode"]?.jsonPrimitive?.intOrNull ?: 0, error)
        }
        val status = root["status"]?.jsonPrimitive?.int
            ?: throw IllegalStateException("HTTP 桥响应缺少 status 字段")
        val headers = Headers.build {
            root["headers"]?.jsonObject?.forEach { (name, value) ->
                append(name, value.jsonPrimitive.contentOrNull ?: "")
            }
        }
        val bodyBytes = root["bodyBase64"]?.jsonPrimitive?.contentOrNull?.takeIf { it.isNotEmpty() }
            ?.decodeBase64Bytes()
            ?: ByteArray(0)
        return HttpResponseData(
            HttpStatusCode.fromValue(status),
            GMTDate(),
            headers,
            HttpProtocolVersion.HTTP_1_1,
            ByteReadChannel(bodyBytes),
            callContext
        )
    }

    /**
     * RCP 错误码 → 传输层异常（类名与 mapTransportFailure 的按名归一对齐：
     * ConnectTimeout/SocketTimeout → Timeout、UnknownHost/Connect → Unavailable）。
     * 码值语义对齐 Technician-Harmony HttpError.fromRcpError。
     */
    private fun mapRcpFailure(rcpCode: Int, message: String): Exception = when (rcpCode) {
        1007900028 -> ConnectTimeoutException(message) // Timeout was reached
        1007900005, 1007900006 -> UnknownHostException(message) // resolve proxy/host name
        1007900007, 1007900052, 1007900055, 1007900056, 1007900986, 1007900993 ->
            ConnectException(message) // connect/send/recv/session closed/cellular
        1007900035, 1007900058, 1007900060, 1007900077, 1007900090 ->
            ConnectException("SSL 连接失败：$message") // SSL 系（对齐 fromRcpError 归入网络不可用）
        else -> IllegalStateException(message)
    }
}

/** 传输层异常（simpleName 与 ApiCall.mapTransportFailure 的按名归一对齐，勿改名）。 */
class ConnectTimeoutException(message: String) : Exception(message)

class SocketTimeoutException(message: String) : Exception(message)

class UnknownHostException(message: String) : Exception(message)

class ConnectException(message: String) : Exception(message)
