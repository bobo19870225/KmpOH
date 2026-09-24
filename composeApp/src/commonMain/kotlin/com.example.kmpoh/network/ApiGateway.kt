package com.example.kmpoh.network

import com.example.kmpoh.data.model.mapper.resolveAccessToken
import com.example.kmpoh.logger.DEBUG_LOG_TAG
import com.example.kmpoh.logger.Logger
import com.example.kmpoh.logger.NETWORK_LOG_TAG
import com.example.kmpoh.network.signature.ApiSignatureMode
import com.example.kmpoh.network.signature.ApiSignaturePolicy
import com.example.kmpoh.network.signature.applyRequestSignature
import com.example.kmpoh.network.signature.verifyResponseSignature
import com.example.kmpoh.storage.PLATFORM_NAME
import io.ktor.client.HttpClient
import io.ktor.client.request.HttpRequestBuilder
import io.ktor.client.request.header
import io.ktor.http.HttpHeaders
import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock
import kotlinx.serialization.KSerializer
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.encodeToString
import kotlinx.serialization.serializer

const val APP_VERSION = "1.0"
private const val PATH_LOGIN = "mobile/Staff.Login/login"
private const val PATH_REFRESH_TOKEN = "mobile/Staff.Login/refreshToken"

/**
 * 刷新令牌响应（字段兼容规则与登录响应一致：`token` 优先、空则取 `access_token`）。
 */
@Serializable
internal data class RefreshTokenData(
    val token: String = "",
    @SerialName("access_token") val accessToken: String = ""
)

/** 登录失效判定：HTTP 401 或 2xx 响应内的业务码 401（对齐原工程 unauthorizedMessage 判定）。 */
fun isLoginExpired(failure: Throwable): Boolean = when (failure) {
    is NetworkException.Http -> failure.statusCode == 401
    is BusinessApiException -> failure.businessCode == 401
    else -> false
}

/**
 * 认证 API 网关（openspec/changes/migrate-network-and-login/design.md 决策 5，
 * 对齐原工程 AuthInterceptor 全部行为）：
 * - 公共请求头 + `Authorization: Bearer`/`ApiToken` 注入；
 * - 401（HTTP 或业务码）→ 刷新令牌 → **重试原请求一次**；
 * - 刷新用空 body POST + 令牌头，成功后同值保存新令牌；
 * - 并发 401 经 [Mutex] 共享一次刷新（对齐原 `@Synchronized`）；
 * - 刷新失败或重试后仍 401：清令牌并发出一次「登录已失效」事件；
 * - 登录、刷新与 skipAuthRefresh 标记的调用不触发刷新
 *   （原工程的 `X-Skip-Auth-Refresh` 是发送前会剥掉的内部控制头，此处等价为参数）。
 */
class ApiGateway(
    private val http: HttpClient,
    val session: AuthSessionManager,
    private val deviceId: String,
    private val appVersion: String = APP_VERSION,
    private val language: String = "zh-CN",
    private val signature: ApiSignaturePolicy = ApiSignaturePolicy.fromConfig()
) {
    private val refreshMutex = Mutex()

    init {
        // spec「签名密钥缺失」：签名关闭但不崩溃；仅测试环境显式告警
        if (signature.mode != ApiSignatureMode.Off &&
            signature.apiSecret.isBlank() &&
            GeneratedApiConfig.ENVIRONMENT == "uat"
        ) {
            Logger.debug(DEBUG_LOG_TAG, "[ApiSignature] API_SIGNATURE_SECRET 未配置，请求签名已关闭")
        }
    }

    suspend fun <T> post(
        path: String,
        deserializer: KSerializer<T>,
        body: Any? = null,
        bodyText: String? = null,
        authenticated: Boolean = true,
        skipAuthRefresh: Boolean = false,
        baseUrl: String = GeneratedApiConfig.BASE_URL
    ): T = requestWithAuthRetry(path, body, bodyText, authenticated, skipAuthRefresh, baseUrl) {
        execute(path, deserializer, body, bodyText, authenticated, baseUrl)
    }

    /** 业务结果只取信封 msg 的调用（logout / passwordEdit）：复用同一 401 刷新编排。 */
    suspend fun postMessage(
        path: String,
        body: Any? = null,
        bodyText: String? = null,
        authenticated: Boolean = true,
        skipAuthRefresh: Boolean = false,
        baseUrl: String = GeneratedApiConfig.BASE_URL
    ): String = requestWithAuthRetry(path, body, bodyText, authenticated, skipAuthRefresh, baseUrl) {
        http.callEnvelopeMessage(
            path = path,
            body = body,
            bodyText = bodyText,
            baseUrl = baseUrl,
            requestExtras = {
                applyCommonHeaders(authenticated = authenticated, forcedToken = null)
                applyRequestSignature(path, bodyText, signature)
            },
            onRawResponse = { headers, raw -> verifyIfEnabled(path, headers, raw) }
        )
    }

    private suspend fun <T> requestWithAuthRetry(
        path: String,
        body: Any?,
        bodyText: String?,
        authenticated: Boolean,
        skipAuthRefresh: Boolean,
        baseUrl: String,
        call: suspend () -> T
    ): T {
        val sentToken = if (authenticated) session.accessToken() else null
        val firstFailure: Exception
        try {
            return call()
        } catch (e: CancellationException) {
            throw e
        } catch (e: Exception) {
            if (!isLoginExpired(e) || !authenticated || skipAuthRefresh || isRefreshExemptPath(path)) {
                throw e
            }
            firstFailure = e
        }

        // 登录失效：刷新令牌并重试原请求一次
        Logger.debug(NETWORK_LOG_TAG, "401 on $path → try refresh token")
        val newToken = refreshMutex.withLock {
            val latest = session.accessToken()
            if (latest != null && latest != sentToken) {
                Logger.debug(NETWORK_LOG_TAG, "refresh skipped: token already renewed by concurrent call")
                latest // 并发场景下别的调用已完成刷新
            } else {
                try {
                    val refreshResult = http.callEnvelopeWith(
                        path = PATH_REFRESH_TOKEN,
                        deserializer = RefreshTokenData.serializer(),
                        body = null,
                        baseUrl = baseUrl,
                        requestExtras = {
                            applyCommonHeaders(authenticated = true, forcedToken = session.refreshToken() ?: sentToken)
                            applyRequestSignature(PATH_REFRESH_TOKEN, null, signature)
                        },
                        onRawResponse = { headers, raw -> verifyIfEnabled(PATH_REFRESH_TOKEN, headers, raw) }
                    )
                    val token = resolveAccessToken(refreshResult.token, refreshResult.accessToken)
                    session.saveTokens(accessToken = token, refreshToken = token)
                    Logger.debug(NETWORK_LOG_TAG, "refresh token ok, retry $path")
                    token
                } catch (ce: CancellationException) {
                    throw ce
                } catch (refreshError: Exception) {
                    Logger.debugSingleLine(
                        NETWORK_LOG_TAG,
                        "refresh failed chain=" +
                            generateSequence<Throwable>(refreshError) { it.cause }
                                .joinToString(" <- ") { it::class.simpleName ?: "?" } +
                            " → clear session & emit LoginExpired"
                    )
                    session.clearTokens()
                    session.notifyLoginExpired()
                    throw firstFailure
                }
            }
        }

        try {
            return call()
        } catch (retryError: Exception) {
            if (isLoginExpired(retryError)) {
                Logger.debug(NETWORK_LOG_TAG, "retry $path still unauthorized → clear session & emit LoginExpired")
                session.clearTokens()
                session.notifyLoginExpired()
            }
            throw retryError
        }
    }

    private fun verifyIfEnabled(path: String, headers: io.ktor.http.Headers, rawBody: String) {
        if (signature.verifiesResponses && !signature.isUnverifiedResponsePath(path)) {
            verifyResponseSignature(signature, headers, rawBody)
        }
    }

    private suspend fun <T> execute(
        path: String,
        deserializer: KSerializer<T>,
        body: Any?,
        bodyText: String?,
        authenticated: Boolean,
        baseUrl: String
    ): T = http.callEnvelopeWith(
        path = path,
        deserializer = deserializer,
        body = body,
        bodyText = bodyText,
        baseUrl = baseUrl,
        requestExtras = {
            applyCommonHeaders(authenticated = authenticated, forcedToken = null)
            applyRequestSignature(path, bodyText, signature)
        },
        onRawResponse = { headers, raw -> verifyIfEnabled(path, headers, raw) }
    )

    private fun HttpRequestBuilder.applyCommonHeaders(authenticated: Boolean, forcedToken: String?) {
        header("Platform", PLATFORM_NAME)
        header("Version", appVersion)
        header("X-App-Version", appVersion)
        header("DeviceId", deviceId)
        header("X-Device-Id", deviceId)
        header("Language", language)
        header(HttpHeaders.UserAgent, "Technician-$PLATFORM_NAME/$appVersion")
        val token = forcedToken ?: if (authenticated) session.accessToken() else null
        if (token != null) {
            header(HttpHeaders.Authorization, "Bearer $token")
            header("ApiToken", token)
        }
    }

    private fun isRefreshExemptPath(path: String): Boolean =
        path == PATH_LOGIN || path == PATH_REFRESH_TOKEN
}

/** reified 便捷重载（无请求体）。 */
internal suspend inline fun <reified R> ApiGateway.postJson(
    path: String,
    authenticated: Boolean = true,
    skipAuthRefresh: Boolean = false
): R = post(
    path = path,
    deserializer = serializer<R>(),
    body = null,
    bodyText = null,
    authenticated = authenticated,
    skipAuthRefresh = skipAuthRefresh
)

/** reified 便捷重载（带请求体）：body 先序列化为 JSON 文本供签名覆盖。 */
internal suspend inline fun <reified R, reified B> ApiGateway.postJson(
    path: String,
    body: B,
    authenticated: Boolean = true,
    skipAuthRefresh: Boolean = false
): R = post(
    path = path,
    deserializer = serializer<R>(),
    body = body,
    bodyText = ApiJson.encodeToString(body),
    authenticated = authenticated,
    skipAuthRefresh = skipAuthRefresh
)
