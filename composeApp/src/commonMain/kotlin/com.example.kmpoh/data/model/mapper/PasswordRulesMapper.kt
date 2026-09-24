package com.example.kmpoh.data.model.mapper

import com.example.kmpoh.data.model.dto.PasswordRulesDto
import com.example.kmpoh.data.model.entity.PasswordRuleEntity
import com.example.kmpoh.data.model.entity.PasswordRulesEntity

/**
 * 密码规则 DTO→Entity 映射（原样迁原工程 `getPasswordRules` 的防御式逻辑）：
 * - 字段别名兼容（`minLength/minLen/passwordMin` 等）；
 * - 长度区间优先从规则正则 `{m,n}` 提取，其次取别名字段，最终回落默认区间；
 * - 空白规则条目剔除、字段去空白。
 */
internal fun PasswordRulesDto.toEntity(): PasswordRulesEntity {
    val ruleEntities = rules.mapNotNull { rule ->
        val regex = rule.regex.trim()
        val message = rule.message.trim()
        if (regex.isBlank() || message.isBlank()) {
            null
        } else {
            PasswordRuleEntity(regex = regex, message = message)
        }
    }
    val lengthRange = ruleEntities.firstNotNullOfOrNull { it.regex.extractLengthRange() }
    return PasswordRulesEntity(
        minLength = lengthRange?.first
            ?: intValue(minLength, minLen, passwordMin)
            ?: PasswordRulesEntity.DEFAULT_MIN_LENGTH,
        maxLength = lengthRange?.second
            ?: intValue(maxLength, maxLen, passwordMax)
            ?: PasswordRulesEntity.DEFAULT_MAX_LENGTH,
        strengthLevel = intValue(strength, passwordStrength, level) ?: 1,
        regex = regex.orEmpty(),
        description = lengthMessage?.takeIf { it.isNotBlank() }
            ?: desc?.takeIf { it.isNotBlank() }
            ?: rule.orEmpty(),
        rules = ruleEntities
    )
}

/** 从正则中的 `{m,n}` 片段提取长度区间（原工程 `extractLengthRange`）。 */
internal fun String.extractLengthRange(): Pair<Int, Int>? {
    val match = Regex("""(\d+),(\d+)""").find(this) ?: return null
    val min = match.groupValues.getOrNull(1)?.toIntOrNull() ?: return null
    val max = match.groupValues.getOrNull(2)?.toIntOrNull() ?: return null
    return min to max
}
