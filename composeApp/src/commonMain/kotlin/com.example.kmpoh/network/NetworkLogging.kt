package com.example.kmpoh.network

import com.example.kmpoh.logger.Logger
import io.ktor.client.request.forms.FormDataContent
import io.ktor.client.request.forms.MultiPartFormDataContent

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

/**
 * 统一请求日志行：`→ POST {url} | params=… | headers=…`（脱敏 + 8KB 裁剪；
 * 输出随 Logger 的测试环境门控，prod 静默——spec「请求日志与脱敏」）。
 */
fun formatRequestLine(url: String, params: String?, headers: String? = null): String {
    val maskedParams = params?.let { maskSensitiveText(truncateForLog(it)) } ?: "-"
    val maskedHeaders = headers?.let { maskSensitiveText(it) } ?: "-"
    return "→ POST $url | params=$maskedParams | headers=$maskedHeaders"
}

/** 统一响应日志行：`← {path} | status=… | body=…`（脱敏 + 8KB 裁剪）。 */
fun formatResponseLine(path: String, status: String, body: String): String =
    "← $path | status=$status | body=${maskSensitiveText(truncateForLog(body))}"

/** 请求参数可读化：签名/日志用 bodyText（JSON 或字段 JSON）优先；否则按请求体形态描述。 */
fun describeRequestParams(bodyText: String?, body: Any?): String? =
    bodyText ?: when (body) {
        null -> null
        is FormDataContent -> body.formData.entries().joinToString("&") { (key, values) ->
            "$key=${values.firstOrNull()}"
        }
        is MultiPartFormDataContent -> "<multipart>"
        else -> body.toString()
    }
