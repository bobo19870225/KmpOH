package com.example.kmpoh.network.signature

import com.example.kmpoh.network.ApiJson
import kotlinx.serialization.json.JsonNull
import kotlinx.serialization.json.JsonObject
import kotlinx.serialization.json.JsonPrimitive
import kotlinx.serialization.json.jsonObject

/**
 * API 签名算法（原样移植原工程 network/signature/ApiSignatureEngine.kt，与 iOS 协议一致）。
 *
 * 协议：`MD5(apiSecret + timestamp + nonce + canonicalParams + apiSecret)`，结果大写十六进制。
 *
 * 参数规范化规则：
 * 1. 将请求体 JSON 解析为扁平 key-value 字典（仅基本类型，嵌套对象不展开）
 * 2. 排除 key 为 `sign`、`timestamp`、`nonce`、`file` 的参数（忽略大小写）
 * 3. 排除 value 为空字符串或 null 的参数
 * 4. 按 key 字典序升序排列，拼接为 `key=value&key2=value2`
 *
 * 本期请求体均为 JSON；表单与 multipart 文本字段的规范化随对应接口迁移时补充。
 * 响应验签时 `paramsString` 传服务端返回的原始响应正文。
 */
object ApiSignatureEngine {

    private val EXCLUDED_KEYS = setOf("sign", "timestamp", "nonce", "file")

    fun sign(
        apiSecret: String,
        timestamp: String,
        nonce: String,
        paramsString: String
    ): String = md5UpperHex(apiSecret + timestamp + nonce + paramsString + apiSecret)

    /** 从请求体文本提取并规范化签名参数。无法解析为 JSON 时原样返回文本（对齐原工程）。 */
    fun canonicalParamsOf(bodyText: String?): String {
        if (bodyText.isNullOrBlank()) return ""
        val params = parseBodyToMap(bodyText) ?: return bodyText
        return params.entries
            .filter { (key, value) ->
                key.lowercase() !in EXCLUDED_KEYS && value.isNotBlank()
            }
            .sortedBy { (key, _) -> key }
            .joinToString("&") { (key, value) -> "$key=$value" }
    }

    /** 校验时间戳是否位于允许的客户端时钟偏差范围内。 */
    fun isTimestampValid(timestamp: String, nowEpochSeconds: Long, maxClockSkewSeconds: Long): Boolean {
        val epochSeconds = timestamp.toLongOrNull() ?: return false
        return epochSeconds in (nowEpochSeconds - maxClockSkewSeconds)..(nowEpochSeconds + maxClockSkewSeconds)
    }

    /** 比较预期签名和实际签名（不区分大小写，常量时间比较）。 */
    fun signaturesMatch(expected: String, actual: String): Boolean =
        constantTimeEqualsIgnoreCase(expected, actual)

    private fun parseBodyToMap(bodyString: String): Map<String, String>? {
        val element = try {
            ApiJson.parseToJsonElement(bodyString)
        } catch (_: Exception) {
            return null
        }
        val obj = when {
            element is JsonObject -> element
            element is JsonPrimitive -> return null
            else -> {
                // 尝试取外层 data 字段（如果包裹在 ApiResponse 中，对齐原工程）
                try {
                    element.jsonObject["data"]?.jsonObject ?: return null
                } catch (_: Exception) {
                    return null
                }
            }
        }
        return obj.entries.mapNotNull { (key, value) ->
            when (value) {
                is JsonNull -> null
                is JsonPrimitive -> key to value.content
                else -> null
            }
        }.toMap()
    }
}
