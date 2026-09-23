package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.call.body
import io.ktor.client.request.HttpRequestBuilder
import io.ktor.client.request.accept
import io.ktor.client.request.post
import io.ktor.client.request.setBody
import io.ktor.client.request.url
import io.ktor.http.ContentType
import io.ktor.http.contentType
import io.ktor.http.isSuccess
import com.example.kmpoh.logger.Logger
import com.example.kmpoh.logger.NETWORK_LOG_TAG
import kotlinx.coroutines.CancellationException
import kotlinx.serialization.KSerializer
import kotlinx.serialization.SerializationException
import kotlinx.serialization.json.JsonNull
import kotlinx.serialization.json.JsonObject
import kotlinx.serialization.json.JsonPrimitive
import kotlinx.serialization.json.buildJsonObject
import kotlinx.serialization.json.intOrNull
import kotlinx.serialization.json.jsonObject
import kotlinx.serialization.serializer

/**
 * 统一 API 调用（design 决策 4：信封解析、业务码校验与异常归一集中在调用包装一处）。
 *
 * - `code == 200` → 返回 `data`；
 * - `code != 200` → 先把不稳定的 `data` 归一为空再解码，随后抛 [BusinessApiException]；
 * - 非 2xx 状态 → [NetworkException.Http]（登录失效判定场景由上层识别处理）；
 * - 传输/超时/解析失败 → [NetworkException] 对应类别。
 */
internal suspend inline fun <reified T> HttpClient.callEnvelope(
    path: String,
    body: Any? = null,
    baseUrl: String = GeneratedApiConfig.BASE_URL,
    noinline requestExtras: HttpRequestBuilder.() -> Unit = {}
): T = callEnvelopeWith(path, serializer<T>(), body, baseUrl, requestExtras)

/** [callEnvelope] 的序列化器显式形态，供非 inline 调用方（认证重试编排）使用。 */
internal suspend fun <T> HttpClient.callEnvelopeWith(
    path: String,
    deserializer: KSerializer<T>,
    body: Any? = null,
    baseUrl: String = GeneratedApiConfig.BASE_URL,
    requestExtras: HttpRequestBuilder.() -> Unit = {},
    onRawResponse: ((headers: io.ktor.http.Headers, rawBody: String) -> Unit)? = null,
    loadingTracker: NetworkRequestTracker? = NetworkRequestTracker.global
): T {
    var loadingStarted = false
    Logger.debug(NETWORK_LOG_TAG, "→ POST $path")
    val response = try {
        post {
            url(baseUrl + path)
            contentType(ContentType.Application.Json)
            accept(ContentType.Application.Json)
            if (body != null) setBody(body)
            requestExtras()
            // 全局加载跳过标记（发送前剥掉，对齐原工程控制头语义）
            if (headers.contains(HEADER_SHOW_GLOBAL_LOADING)) {
                val skip = headers[HEADER_SHOW_GLOBAL_LOADING] == "false"
                headers.remove(HEADER_SHOW_GLOBAL_LOADING)
                if (!skip) {
                    loadingTracker?.onRequestStarted()
                    loadingStarted = true
                }
            } else {
                loadingTracker?.onRequestStarted()
                loadingStarted = true
            }
        }
    } catch (e: CancellationException) {
        if (loadingStarted) loadingTracker?.onRequestFinished()
        throw e
    } catch (e: Exception) {
        // Ktor 引擎在不同平台的网络异常基类不一致，统一走类名归一
        if (loadingStarted) loadingTracker?.onRequestFinished()
        Logger.debugSingleLine(
            NETWORK_LOG_TAG,
            "✗ POST $path send-failed chain=" +
                generateSequence<Throwable>(e) { it.cause }.joinToString(" <- ") { it::class.simpleName ?: "?" }
        )
        throw mapTransportFailure(e)
    }
    // 响应头到达即结束 Loading 生命周期（对齐原工程）
    if (loadingStarted) loadingTracker?.onRequestFinished()

    if (!response.status.isSuccess()) {
        Logger.debug(NETWORK_LOG_TAG, "✗ POST $path http=${response.status.value} ${response.status.description}")
        throw NetworkException.Http(response.status.value, response.status.description)
    }
    Logger.debug(NETWORK_LOG_TAG, "← POST $path status=${response.status.value}")

    val text = try {
        response.body<String>()
    } catch (e: CancellationException) {
        throw e
    } catch (e: Exception) {
        throw NetworkException.Parsing(e)
    }

    onRawResponse?.invoke(response.headers, text)

    return decodeEnvelopeWith(text, deserializer)
}

internal inline fun <reified T> decodeEnvelope(text: String): T =
    decodeEnvelopeWith(text, serializer<T>())

/** 解析信封：失败响应先把 `data` 归一为空（其结构不稳定），再解码并做业务码校验。 */
internal fun <T> decodeEnvelopeWith(text: String, deserializer: KSerializer<T>): T {
    val root = try {
        ApiJson.parseToJsonElement(text).jsonObject
    } catch (e: Exception) {
        throw NetworkException.Parsing(e)
    }

    val code = (root["code"] as? JsonPrimitive)?.intOrNull ?: 0
    val normalized: JsonObject =
        if (code == 200) root
        else buildJsonObject {
            root.forEach { (k, v) -> put(k, if (k == "data") JsonNull else v) }
        }

    val envelope = try {
        ApiJson.decodeFromJsonElement(ApiResponse.serializer(deserializer), normalized)
    } catch (e: SerializationException) {
        throw NetworkException.Parsing(e)
    } catch (e: IllegalArgumentException) {
        throw NetworkException.Parsing(e)
    }

    if (!envelope.isBusinessSuccess()) {
        Logger.debug(NETWORK_LOG_TAG, "✗ business code=${envelope.code} msg=${envelope.message}")
        throw BusinessApiException(envelope.code, envelope.message)
    }
    return envelope.data ?: throw NetworkException.Parsing(IllegalStateException("响应缺少 data"))
}

/**
 * 传输失败归一（对齐原工程 NetworkResponseInterceptor）：
 * 超时 → [NetworkException.Timeout]；不可达/拒绝连接 → [NetworkException.Unavailable]；其余 IO → Transport。
 *
 * KMP 公共代码无法引用各平台专有网络异常类（java.net.* / CFNetwork / libc），
 * 故按异常类名沿因果链识别（单测用同名假异常覆盖）。
 */
fun mapTransportFailure(failure: Throwable): NetworkException {
    var current: Throwable? = failure
    while (current != null) {
        val simpleName = current::class.simpleName
        when {
            simpleName == "HttpRequestTimeoutException" ||
                simpleName == "ConnectTimeoutException" ||
                simpleName == "SocketTimeoutException" ->
                return NetworkException.Timeout(failure)

            simpleName == "UnresolvedAddressException" ||
                simpleName == "UnknownHostException" ||
                simpleName == "ConnectException" ->
                return NetworkException.Unavailable(failure)
        }
        current = current.cause
    }
    return NetworkException.Transport(failure)
}
