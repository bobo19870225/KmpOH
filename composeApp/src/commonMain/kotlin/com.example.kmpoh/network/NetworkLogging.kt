package com.example.kmpoh.network

import com.example.kmpoh.logger.Logger
import com.example.kmpoh.logger.NETWORK_LOG_TAG
import io.ktor.client.HttpClientConfig
import io.ktor.client.plugins.logging.LogLevel
import io.ktor.client.plugins.logging.Logging
import io.ktor.client.plugins.logging.Logger as KtorLogger

/** 日志体裁剪上限（对齐原工程 8KB 文本 body 打印上限）。 */
const val LOG_BODY_MAX_CHARS = 8 * 1024

/**
 * 文本脱敏入口（实现统一收敛在 [Logger.sanitize]：JSON 值 / 行式 key: value / query key=value，
 * 字段集合含令牌/密码/签名/设备标识等——比原工程当前生效配置更严，design 决策 5）。
 */
fun maskSensitiveText(text: String): String = Logger.sanitize(text)

/** 日志裁剪：超出上限截断并标注（截断后的文本再由 Logger 单行分片输出）。 */
fun truncateForLog(text: String, maxChars: Int = LOG_BODY_MAX_CHARS): String =
    if (text.length <= maxChars) text
    else text.substring(0, maxChars) + "...<truncated ${text.length - maxChars} chars>"

/** Ktor 日志出口：脱敏 + 裁剪 + 分片防截断（迁移后的 Logger 承担分片）。 */
private object SanitizedLogger : KtorLogger {
    override fun log(message: String) {
        Logger.debugSingleLine(NETWORK_LOG_TAG, truncateForLog(message))
    }
}

/**
 * 安装网络日志（对齐原工程 NetworkLoggingInterceptor：仅测试环境 uat 输出，
 * 单行化合并日志、敏感字段脱敏、文本体裁剪 8KB）。头级脱敏由插件 sanitizeHeader 完成。
 */
fun HttpClientConfig<*>.installNetworkLogging(enabled: Boolean = Logger.isTestEnvironment) {
    if (!enabled) return
    install(Logging) {
        logger = SanitizedLogger
        level = LogLevel.ALL
        sanitizeHeader { header -> header.lowercase() in listOf("authorization", "apitoken", "sign", "nonce", "cookie", "set-cookie") }
    }
}
