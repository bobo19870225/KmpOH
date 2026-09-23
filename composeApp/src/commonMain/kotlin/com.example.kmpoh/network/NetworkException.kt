package com.example.kmpoh.network

/**
 * 网络层异常归一化（对齐原工程 network/NetworkException.kt 的五类划分）。
 * KMP 公共代码没有 java.io.IOException（原工程继承它仅为 OkHttp 拦截器语义），
 * 基类退化为 Exception，行为契约不变（design 决策 4）。
 *
 * 文案逐字对齐原工程 values-zh-rCN 资源。
 */
sealed class NetworkException(
    message: String,
    cause: Throwable? = null
) : Exception(message, cause) {

    /** 非 2xx HTTP 状态（登录失效判定场景除外）。 */
    class Http(val statusCode: Int, val statusMessage: String) :
        NetworkException("HTTP $statusCode：$statusMessage")

    class Timeout(cause: Throwable? = null) : NetworkException(NetworkMessages.TIMEOUT, cause)

    class Unavailable(cause: Throwable? = null) : NetworkException(NetworkMessages.UNAVAILABLE, cause)

    class Transport(cause: Throwable? = null) : NetworkException(NetworkMessages.TRANSPORT, cause)

    class Parsing(cause: Throwable? = null) : NetworkException(NetworkMessages.PARSING, cause)
}

/** 对外可直接呈现的用户文案（逐字对齐原工程 values-zh-rCN）。 */
object NetworkMessages {
    const val UNAVAILABLE = "当前网络不可用，请检查网络"
    const val TIMEOUT = "网络请求超时，请稍后重试"
    const val TRANSPORT = "网络连接异常，请稍后重试"
    const val PARSING = "网络数据解析失败，请稍后重试"
    const val LOGIN_FALLBACK = "登录失败，请重试"
    const val LOGIN_EXPIRED = "登录信息已过期，请重新登录"
}
