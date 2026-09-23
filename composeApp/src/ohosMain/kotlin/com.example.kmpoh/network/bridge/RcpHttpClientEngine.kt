@file:OptIn(io.ktor.utils.io.InternalAPI::class)

package com.example.kmpoh.network.bridge

import io.ktor.client.engine.HttpClientEngineBase
import io.ktor.client.engine.HttpClientEngineConfig
import io.ktor.client.request.HttpRequestData
import io.ktor.client.request.HttpResponseData
import io.ktor.http.Headers
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpProtocolVersion
import io.ktor.http.HttpStatusCode
import io.ktor.http.content.ByteArrayContent
import io.ktor.http.content.OutgoingContent
import io.ktor.http.content.TextContent
import io.ktor.util.date.GMTDate
import io.ktor.util.decodeBase64Bytes
import io.ktor.util.encodeBase64
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
 * - 请求：`{ url, method, headers, bodyText?|bodyBase64? }`
 * - 成功响应（任意 HTTP 状态码原样透传，由 ktor 层判非 2xx）：`{ status, headers, bodyBase64 }`
 * - 传输失败：`{ error, rcpCode }`（rcpCode 为 RCP BusinessError 码，
 *   映射语义对齐 Technician-Harmony 的 HttpError.fromRcpError）
 */
internal class RcpHttpClientEngine : HttpClientEngineBase("RcpBridge") {

    override val config: HttpClientEngineConfig = HttpClientEngineConfig()

    override suspend fun execute(data: HttpRequestData): HttpResponseData {
        val requestJson = encodeRequest(data)
        val responseJson = OhosHttpTransport.execute(requestJson)
        return decodeResponse(responseJson, data.executionContext)
    }

    private suspend fun encodeRequest(data: HttpRequestData): String {
        val content = data.body
        val headers = mutableMapOf<String, String>()
        fun merge(h: Headers) {
            h.forEach { name, values ->
                headers[name] = if (values.size == 1) values[0] else values.joinToString(", ")
            }
        }
        merge(data.headers)
        when (content) {
            is OutgoingContent -> merge(content.headers)
            else -> {}
        }

        var bodyText: String? = null
        var bodyBase64: String? = null
        when (content) {
            is OutgoingContent.NoContent -> {}
            is TextContent -> bodyText = content.text
            is ByteArrayContent -> bodyBase64 = content.bytes().encodeBase64()
            is OutgoingContent.ReadChannelContent ->
                bodyBase64 = content.readFrom().readRemaining().readByteArray().encodeBase64()
            is OutgoingContent.WriteChannelContent ->
                throw UnsupportedOperationException(
                    "WriteChannelContent 不受桥接层支持（请用 Text/ByteArray 内容）：" +
                        content::class.simpleName
                )
            else -> {}
        }

        return buildJsonObject {
            put("url", data.url.toString())
            put("method", data.method.value)
            putJsonObject("headers") {
                headers.forEach { (name, value) -> put(name, value) }
            }
            bodyText?.let { put("bodyText", it) }
            bodyBase64?.let { put("bodyBase64", it) }
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
