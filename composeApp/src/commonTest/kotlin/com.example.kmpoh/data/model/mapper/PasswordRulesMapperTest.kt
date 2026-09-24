package com.example.kmpoh.data.model.mapper

import com.example.kmpoh.data.model.dto.PasswordRuleDto
import com.example.kmpoh.data.model.dto.PasswordRulesDto
import com.example.kmpoh.data.model.entity.PasswordRulesEntity
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlinx.serialization.json.JsonPrimitive

class PasswordRulesMapperTest {

    @Test
    fun extractsLengthRangeFromRuleRegex() {
        val dto = PasswordRulesDto(
            rules = listOf(PasswordRuleDto(regex = "(?=.*\\d)(.{8,16})", message = "需包含数字"))
        )
        val entity = dto.toEntity()
        assertEquals(8, entity.minLength)
        assertEquals(16, entity.maxLength)
    }

    @Test
    fun fallsBackToAliasFieldsThenDefaults() {
        val fromAlias = PasswordRulesDto(minLen = JsonPrimitive(4), maxLen = JsonPrimitive(20)).toEntity()
        assertEquals(4, fromAlias.minLength)
        assertEquals(20, fromAlias.maxLength)

        val fromDefaults = PasswordRulesDto().toEntity()
        assertEquals(PasswordRulesEntity.DEFAULT_MIN_LENGTH, fromDefaults.minLength)
        assertEquals(PasswordRulesEntity.DEFAULT_MAX_LENGTH, fromDefaults.maxLength)
    }

    @Test
    fun regexRangeTakesPrecedenceOverAliasFields() {
        val dto = PasswordRulesDto(
            rules = listOf(PasswordRuleDto(regex = "(.{6,10})", message = "m")),
            passwordMin = JsonPrimitive(3),
            passwordMax = JsonPrimitive(99)
        )
        val entity = dto.toEntity()
        assertEquals(6, entity.minLength)
        assertEquals(10, entity.maxLength)
    }

    @Test
    fun dropsBlankRulesAndTrimsFields() {
        val dto = PasswordRulesDto(
            rules = listOf(
                PasswordRuleDto(regex = " (?=.*[a-z]) ", message = " 需小写字母 "),
                PasswordRuleDto(regex = "", message = "x"),
                PasswordRuleDto(regex = "y", message = "  ")
            )
        )
        val entity = dto.toEntity()
        assertEquals(1, entity.rules.size)
        assertEquals("(?=.*[a-z])", entity.rules[0].regex)
        assertEquals("需小写字母", entity.rules[0].message)
    }

    @Test
    fun descriptionPrefersLengthMessageThenDescThenRule() {
        assertEquals(
            "长度说明",
            PasswordRulesDto(lengthMessage = "长度说明", desc = "d", rule = "r").toEntity().description
        )
        assertEquals("d", PasswordRulesDto(desc = "d", rule = "r").toEntity().description)
        assertEquals("r", PasswordRulesDto(rule = "r").toEntity().description)
        assertEquals("", PasswordRulesDto().toEntity().description)
    }

    @Test
    fun maxInputLengthNeverBelowDefaultMin() {
        assertEquals(50, PasswordRulesDto().toEntity().maxInputLength)
        assertEquals(
            PasswordRulesEntity.DEFAULT_MIN_LENGTH,
            PasswordRulesDto(maxLen = JsonPrimitive(3)).toEntity().maxInputLength
        )
    }
}
