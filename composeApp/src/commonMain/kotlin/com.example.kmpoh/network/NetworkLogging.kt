package com.example.kmpoh.network

import io.ktor.client.HttpClientConfig
import io.ktor.client.plugins.logging.LogLevel
import io.ktor.client.plugins.logging.Logger
import io.ktor.client.plugins.logging.Logging

/** 日志体裁剪上限（对齐原工程 8KB 文本 body 打印上限）。 */
const val LOG_BODY_MAX_CHARS = 8 * 1024

/** 脱敏后的替换文本。 */
const val LOG_MASK = "***"

/**
 * 敏感字段集合（design 决策 5：显式包含令牌/密码/签名/设备标识，
 * 比原工程当前只遮蔽 device-id 更严——原配置属已知疏漏）。
 */
private val SENSITIVE_KEYS = listOf(
    "password", "token", "access_token", "refresh_token", "api_token",
    "sign", "authorization", "device-id", "deviceid"
)

/**
 * 文本脱敏：遮蔽 JSON 字段（`"password":"x"`）、key=value 形式与头行（`Authorization: x`）。
 * 只做防御性展示处理，不承担安全职责。
 */
fun maskSensitiveText(text: String): String {
    var result = text
    for (key in SENSITIVE_KEYS) {
        // JSON 形式：\"key\":\"...\" 或 'key':'...'（只遮值，保留结构）
        result = result.replace(Regex("(\"$key\"\\s*:\\s*\")[^\"]*(\")", RegexOption.IGNORE_CASE), "$1$LOG_MASK$2")
        result = result.replace(Regex("('$key'\\s*:\\s*')[^']*(')", RegexOption.IGNORE_CASE), "$1$LOG_MASK$2")
        // 行式 key=value / key: value（头行如 `Authorization: Bearer x` 须遮到行尾，避免残留令牌）
        result = result.replace(Regex("(?im)((^|[\\s&;,])$key\\s*[=:]\\s*).+$"), "$1$LOG_MASK")
    }
    return result
}

/** 日志裁剪：超出上限截断并标注。 */
fun truncateForLog(text: String, maxChars: Int = LOG_BODY_MAX_CHARS): String =
    if (text.length <= maxChars) text
    else text.substring(0, maxChars) + "...<truncated ${text.length - maxChars} chars>"

/** 脱敏 + 裁剪后输出的 Logger（仅测试环境启用时安装）。 */
private object SanitizedLogger : Logger {
    override fun log(message: String) {
        println(truncateForLog(maskSensitiveText(message)))
    }
}

/**
 * 安装网络日志（对齐原工程 NetworkLoggingInterceptor：仅测试环境 uat 输出，
 * 单行化合并日志、敏感字段脱敏、文本体裁剪 8KB）。头级脱敏由插件 sanitizeHeader 完成。
 */
fun HttpClientConfig<*>.installNetworkLogging(enabled: Boolean = GeneratedApiConfig.ENVIRONMENT == "uat") {
    if (!enabled) return
    install(Logging) {
        logger = SanitizedLogger
        level = LogLevel.ALL
        sanitizeHeader { header -> header.lowercase() in SENSITIVE_KEYS || header.lowercase() == "user-agent" }
    }
}
