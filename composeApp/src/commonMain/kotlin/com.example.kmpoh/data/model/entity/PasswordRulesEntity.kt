package com.example.kmpoh.data.model.entity

/** 密码规则（原样迁原工程）：长度区间 + 全局正则 + 规则条目 + 描述文案。 */
data class PasswordRulesEntity(
    val minLength: Int = DEFAULT_MIN_LENGTH,
    val maxLength: Int = DEFAULT_MAX_LENGTH,
    val strengthLevel: Int = 1,
    val regex: String = "",
    val description: String = "",
    val rules: List<PasswordRuleEntity> = emptyList()
) {
    val maxInputLength: Int
        get() = maxLength.coerceAtLeast(DEFAULT_MIN_LENGTH)

    companion object {
        const val DEFAULT_MIN_LENGTH = 6
        const val DEFAULT_MAX_LENGTH = 50
    }
}

data class PasswordRuleEntity(
    val regex: String,
    val message: String
)
