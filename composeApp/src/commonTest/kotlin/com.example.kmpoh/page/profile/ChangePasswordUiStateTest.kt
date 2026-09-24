package com.example.kmpoh.page.profile

import com.example.kmpoh.data.model.entity.PasswordRuleEntity
import com.example.kmpoh.data.model.entity.PasswordRulesEntity
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNull
import kotlin.test.assertTrue

class ChangePasswordUiStateTest {

    private val rules = PasswordRulesEntity(
        minLength = 8,
        maxLength = 16,
        description = "长度 8-16 位",
        rules = listOf(PasswordRuleEntity(regex = "(?=.*\\d)", message = "需包含数字"))
    )

    @Test
    fun mismatchFlagsRespectConfirmLengthRelation() {
        val shorterConfirm = ChangePasswordUiState(newPassword = "abc", confirmPassword = "ab", passwordRules = rules)
        assertTrue(shorterConfirm.isConfirmMismatch)
        assertFalse(shorterConfirm.shouldShowConfirmMismatch)

        val equalLength = ChangePasswordUiState(newPassword = "abc", confirmPassword = "abd", passwordRules = rules)
        assertTrue(equalLength.isConfirmMismatch)
        assertTrue(equalLength.shouldShowConfirmMismatch)

        val sameValue = ChangePasswordUiState(newPassword = "abc", confirmPassword = "abc", passwordRules = rules)
        assertFalse(sameValue.isConfirmMismatch)
        assertFalse(sameValue.shouldShowConfirmMismatch)

        val blankConfirm = ChangePasswordUiState(newPassword = "abc", confirmPassword = "", passwordRules = rules)
        assertFalse(blankConfirm.isConfirmMismatch)
    }

    @Test
    fun ruleErrorReportsFirstFailedRegexMessage() {
        val failed = ChangePasswordUiState(newPassword = "abcdefgh", passwordRules = rules)
        assertEquals("需包含数字", failed.passwordRuleError)
    }

    @Test
    fun ruleErrorFallsBackToLengthDescription() {
        val tooShort = ChangePasswordUiState(newPassword = "abc1", passwordRules = rules)
        assertEquals("长度 8-16 位", tooShort.passwordRuleError)

        val blank = ChangePasswordUiState(newPassword = "", passwordRules = rules)
        assertNull(blank.passwordRuleError)
    }

    @Test
    fun validRuleAndLengthHasNoError() {
        val ok = ChangePasswordUiState(newPassword = "abcd1234", passwordRules = rules)
        assertNull(ok.passwordRuleError)
    }

    @Test
    fun canSubmitRequiresAllConditions() {
        val valid = ChangePasswordUiState(
            newPassword = "abcd1234",
            confirmPassword = "abcd1234",
            passwordRules = rules
        )
        assertTrue(valid.canSubmit)

        assertFalse(valid.copy(isSubmitting = true).canSubmit)
        assertFalse(valid.copy(newPassword = "").canSubmit)
        assertFalse(valid.copy(confirmPassword = "abcd1235").canSubmit)
        assertFalse(valid.copy(newPassword = "abcdefgh").canSubmit)
    }
}
