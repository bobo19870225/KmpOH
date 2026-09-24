package com.example.kmpoh.data.model.dto

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.intOrNull
import kotlinx.serialization.json.jsonPrimitive

/** 密码规则接口 data 节点，兼容后端字段命名差异（原样迁原工程）。 */
@Serializable
data class PasswordRulesDto(
    @SerialName("rules")
    val rules: List<PasswordRuleDto> = emptyList(),
    @SerialName("min_length")
    val minLength: JsonElement? = null,
    @SerialName("min_len")
    val minLen: JsonElement? = null,
    @SerialName("password_min")
    val passwordMin: JsonElement? = null,
    @SerialName("max_length")
    val maxLength: JsonElement? = null,
    @SerialName("max_len")
    val maxLen: JsonElement? = null,
    @SerialName("password_max")
    val passwordMax: JsonElement? = null,
    @SerialName("strength")
    val strength: JsonElement? = null,
    @SerialName("password_strength")
    val passwordStrength: JsonElement? = null,
    @SerialName("level")
    val level: JsonElement? = null,
    @SerialName("regex")
    val regex: String? = null,
    @SerialName("rule")
    val rule: String? = null,
    @SerialName("desc")
    val desc: String? = null,
    @SerialName("length_message")
    val lengthMessage: String? = null,
    @SerialName("weak_message")
    val weakMessage: String? = null
) {
    fun intValue(vararg values: JsonElement?): Int? {
        return values.firstNotNullOfOrNull { it?.jsonPrimitive?.intOrNull }
    }
}

@Serializable
data class PasswordRuleDto(
    @SerialName("regex")
    val regex: String = "",
    @SerialName("message")
    val message: String = ""
)
