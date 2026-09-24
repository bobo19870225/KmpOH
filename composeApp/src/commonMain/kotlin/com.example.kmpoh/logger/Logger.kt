package com.example.kmpoh.logger

import com.example.kmpoh.network.GeneratedApiConfig

const val NETWORK_LOG_TAG = "########Network#######"
const val BUSINESS_LOG_TAG = "########BUSINESS#######"
const val DEBUG_LOG_TAG = "########DEBUG#######"

/** 脱敏后的替换文本。 */
const val LOG_MASK = "***"

/** 日志级别（跨平台统一四级；到平台原生级别的映射见各 [platformLogLine] actual）。 */
enum class LogLevel { DEBUG, INFO, WARN, ERROR }

/**
 * Logger 工具类 —— 迁移自原工程 logger/Logger.kt。
 *
 * 与原工程差异（KMP 化）：
 * - Timber 换为平台输出 [platformLogLine]（Android=logcat、iOS=stdout、鸿蒙=hilog），
 *   并提供 [LogLevel] 四级入口（debug/info/warn/error）；
 * - 输出门控：DEBUG/INFO 仅测试环境输出（对齐 spec「请求日志与脱敏」的
 *   非测试环境 MUST NOT 输出网络日志）；WARN/ERROR 全环境输出（对齐原工程
 *   ReleaseTree「release 记 WARN+」的业务预期）；
 * - 敏感脱敏保留并并入网络层更严的字段集合（原工程列表曾被注释停用，属已知疏漏）。
 *
 * 保留的原工程核心能力：
 * - [debugSingleLine]：压缩单行 + 分片（`[i/n]` 序号），规避 logcat 单条长度上限；
 * - [debugJson]：按 JSON 结构边界分片，拼回即可还原正文；
 * - [sanitize]：敏感字段脱敏（JSON / 行式 key: value / query key=value）。
 *
 * 业务代码通过 Logger 写日志，禁止直接输出认证信息和客户资料。
 */
object Logger {

    /**
     * 测试环境判断：非 prod 即测试环境（dev / uat 都输出——原工程「仅 uat」的收窄
     * 会造成 dev/uat 联调时看不到日志，此处按 spec 语义放宽）。门控规则见 [shouldOutput]。
     */
    val isTestEnvironment: Boolean get() = GeneratedApiConfig.ENVIRONMENT != "prod"

    /** 级别门控：测试环境全级别输出；prod 仅 WARN/ERROR（纯函数便于单测）。 */
    internal fun shouldOutput(level: LogLevel, isTestEnvironment: Boolean): Boolean =
        isTestEnvironment || level == LogLevel.WARN || level == LogLevel.ERROR

    /** DEBUG 级日志入口（仅测试环境输出），统一脱敏后输出。 */
    fun debug(tag: String, message: String) = log(LogLevel.DEBUG, tag, message)

    /** INFO 级日志入口（仅测试环境输出），统一脱敏后输出。 */
    fun info(tag: String, message: String) = log(LogLevel.INFO, tag, message)

    /** WARN 级日志入口（全环境输出），统一脱敏后输出。 */
    fun warn(tag: String, message: String) = log(LogLevel.WARN, tag, message)

    /** ERROR 级日志入口（全环境输出），统一脱敏后输出。 */
    fun error(tag: String, message: String) = log(LogLevel.ERROR, tag, message)

    /**
     * 网络响应统一压缩为单行，并主动分片以规避 Logcat 单条日志长度上限。
     * 每片均包含分片序号，可按同一 tag 检索并顺序拼接得到完整原文。
     */
    fun debugSingleLine(tag: String, message: String) {
        if (!isTestEnvironment) return
        val normalized = sanitize(message).replace("\r", "").replace("\n", "")
        val chunks = normalized.chunked(MAX_SINGLE_LINE_LOG_LENGTH)
        if (chunks.size <= 1) {
            platformLogLine(LogLevel.DEBUG, tag, normalized)
            return
        }
        chunks.forEachIndexed { index, chunk ->
            platformLogLine(LogLevel.DEBUG, tag, "[${index + 1}/${chunks.size}] $chunk")
        }
    }

    /**
     * 输出可复制还原的 JSON 响应体：分片只落在 JSON 结构边界，
     * 按顺序复制正文后可直接交给 JSON 格式化工具。
     */
    fun debugJson(tag: String, header: String, json: String) {
        if (!isTestEnvironment) return
        val normalized = sanitize(json).replace("\r", "").replace("\n", "")
        val chunks = normalized.splitAtJsonBoundaries(MAX_SINGLE_LINE_LOG_LENGTH)
        platformLogLine(LogLevel.DEBUG, tag, "$header body_parts=${chunks.size}")
        chunks.forEach { chunk -> platformLogLine(LogLevel.DEBUG, tag, chunk) }
    }

    /** 无 tag 便捷入口，默认业务 TAG。 */
    fun debug(message: String) = debug(BUSINESS_LOG_TAG, message)

    fun info(message: String) = info(BUSINESS_LOG_TAG, message)

    fun warn(message: String) = warn(BUSINESS_LOG_TAG, message)

    fun error(message: String) = error(BUSINESS_LOG_TAG, message)

    /** 级别出口：门控 + 脱敏后交给平台 [platformLogLine]。 */
    private fun log(level: LogLevel, tag: String, message: String) {
        if (!shouldOutput(level, isTestEnvironment)) return
        platformLogLine(level, tag, sanitize(message))
    }

    /**
     * 敏感字段脱敏（并入原工程三形式：JSON 值 / 行式 `key: value` 遮到行尾 / query `?key=` 与 `&key=`）。
     * 只做防御性展示处理，不承担安全职责。
     */
    fun sanitize(message: String): String {
        var result = maskSensitiveValues(message)
        // query 形式：?key= / &key=（原工程 sanitize 的第三分支）
        for (key in SENSITIVE_KEYS) {
            result = result.replace(Regex("(?i)([?&]$key=)[^&\\s]+"), "$1$LOG_MASK")
        }
        return result
    }

    /** JSON 值与行式 key=value 的核心脱敏（被 [sanitize] 与网络层 maskSensitiveText 复用）。 */
    internal fun maskSensitiveValues(text: String): String {
        var result = text
        for (key in SENSITIVE_KEYS) {
            // JSON 形式：\"key\":\"...\" 或 'key':'...'（只遮值，保留结构）
            result = result.replace(Regex("(\"$key\"\\s*:\\s*\")[^\"]*(\")", RegexOption.IGNORE_CASE), "$1$LOG_MASK$2")
            result = result.replace(Regex("('$key'\\s*:\\s*')[^']*(')", RegexOption.IGNORE_CASE), "$1$LOG_MASK$2")
            // 行式 key=value / key: value（头行如 `Authorization: Bearer x` 须遮到行尾）
            result = result.replace(Regex("(?im)((^|[\\s&;,])$key\\s*[=:]\\s*).+$"), "$1$LOG_MASK")
        }
        return result
    }

    /**
     * 敏感字段集合（design 决策 5：令牌/密码/签名/设备标识等，
     * 含原工程被注释停用的完整列表；比原工程当前生效配置更严）。
     */
    private val SENSITIVE_KEYS = listOf(
        "authorization", "apitoken", "api_token", "token", "access_token", "refresh_token",
        "password", "pwd", "secret", "sign", "nonce", "cookie", "set-cookie",
        "phone", "mobile", "tel", "id_card", "credential", "auth",
        "customer_id", "customer_code", "customer_name", "contact_name",
        "address", "addr", "lat", "lng", "staff_code", "device-id", "deviceid", "x-device-id"
    )

    /** 按 JSON 结构边界分片（原样移植原工程实现，供单测覆盖取 internal 可见性）。 */
    internal fun String.splitAtJsonBoundaries(maxLength: Int): List<String> {
        if (length <= maxLength) return listOf(this)

        val result = mutableListOf<String>()
        var chunkStart = 0
        var lastBoundary = -1
        var inString = false
        var escaped = false

        forEachIndexed { index, character ->
            if (inString) {
                when {
                    escaped -> escaped = false
                    character == '\\' -> escaped = true
                    character == '"' -> inString = false
                }
            } else {
                when (character) {
                    '"' -> inString = true
                    ',', '}', ']' -> lastBoundary = index
                }
            }

            if (index - chunkStart + 1 >= maxLength) {
                val chunkEnd = lastBoundary.takeIf { it >= chunkStart } ?: index
                result += substring(chunkStart, chunkEnd + 1)
                chunkStart = chunkEnd + 1
                lastBoundary = -1
            }
        }
        if (chunkStart < length) result += substring(chunkStart)
        return result
    }

    private const val MAX_SINGLE_LINE_LOG_LENGTH = 3_000
}

/** 平台日志输出（单行、已脱敏）：级别 + tag + 消息。 */
expect fun platformLogLine(level: LogLevel, tag: String, message: String)
