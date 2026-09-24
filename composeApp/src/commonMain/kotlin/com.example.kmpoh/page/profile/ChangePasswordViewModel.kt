package com.example.kmpoh.page.profile

import com.example.kmpoh.data.model.entity.PasswordRulesEntity
import com.example.kmpoh.data.repository.ProfileRepository
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

/** 修改密码页一次性提示：类型化文案由 Page 映射 `stringResource`（决策 2，VM 不引 Context）。 */
sealed interface ChangePasswordToast {
    data object Required : ChangePasswordToast
    data object ConfirmMismatch : ChangePasswordToast
    data class MinLength(val min: Int) : ChangePasswordToast
    data class MaxLength(val max: Int) : ChangePasswordToast
    data object RulesLoadFailed : ChangePasswordToast
    data object Failed : ChangePasswordToast

    /** 成功提示：message 为服务端文案（空则 Page 用默认成功文案）。 */
    data class Success(val message: String?) : ChangePasswordToast

    /** 服务端/规则文案原样透传。 */
    data class Error(val message: String) : ChangePasswordToast
}

data class ChangePasswordUiState(
    val newPassword: String = "",
    val confirmPassword: String = "",
    val passwordRules: PasswordRulesEntity = PasswordRulesEntity(),
    val isSubmitting: Boolean = false,
    val passwordChanged: Boolean = false,
    val requestErrorMessage: String? = null,
    val toast: ChangePasswordToast? = null
) {
    val isConfirmMismatch: Boolean
        get() = newPassword.isNotBlank() &&
            confirmPassword.isNotBlank() &&
            newPassword != confirmPassword

    val shouldShowConfirmMismatch: Boolean
        get() = isConfirmMismatch && confirmPassword.length >= newPassword.length

    val canSubmit: Boolean
        get() = newPassword.isNotBlank() &&
            confirmPassword.isNotBlank() &&
            !isConfirmMismatch &&
            passwordRuleError == null &&
            !isSubmitting

    val passwordRuleDescription: String
        get() = passwordRules.rules.joinToString("；") { it.message }
            .ifBlank { passwordRules.description }

    val isPasswordLengthInvalid: Boolean
        get() = newPassword.isNotBlank() &&
            (newPassword.length < passwordRules.minLength || newPassword.length > passwordRules.maxLength)

    /** 规则错误：服务端规则文案优先（原样透传），其次长度描述；无错为 null。 */
    val passwordRuleError: String?
        get() {
            if (newPassword.isBlank()) return null
            passwordRules.rules.forEach { rule ->
                val passed = runCatching {
                    Regex(rule.regex).containsMatchIn(newPassword)
                }.getOrDefault(true)
                if (!passed) return rule.message
            }
            return if (isPasswordLengthInvalid) {
                passwordRules.description.takeIf { it.isNotBlank() }
            } else {
                null
            }
        }
}

/**
 * 修改密码页 ViewModel（原样迁原工程校验语义；自写纯 Kotlin 状态容器，对齐 LoginViewModel 样板）。
 * 校验/结果文案以 [ChangePasswordToast] 入 state，Page 映射多语言（design 决策 2）。
 */
class ChangePasswordViewModel(
    private val profileRepository: ProfileRepository,
    private val scope: CoroutineScope
) {
    private val _state = MutableStateFlow(ChangePasswordUiState())
    val state: StateFlow<ChangePasswordUiState> = _state.asStateFlow()

    init {
        loadPasswordRules()
    }

    fun onNewPasswordChange(value: String) {
        _state.update {
            it.copy(
                newPassword = value.take(it.passwordRules.maxInputLength),
                requestErrorMessage = null
            )
        }
    }

    fun onConfirmPasswordChange(value: String) {
        _state.update {
            it.copy(
                confirmPassword = value.take(it.passwordRules.maxInputLength),
                requestErrorMessage = null
            )
        }
    }

    fun submit() {
        val current = _state.value
        if (!current.canSubmit) {
            _state.update { it.copy(toast = current.validationToast()) }
            return
        }

        scope.launch {
            _state.update { it.copy(isSubmitting = true, requestErrorMessage = null) }
            profileRepository.changePassword(current.newPassword).fold(
                onSuccess = { message ->
                    // 成功：清会话（spec data/profile「修改密码」）→ passwordChanged 一次性事件驱动回登录
                    _state.value = ChangePasswordUiState(
                        toast = ChangePasswordToast.Success(message),
                        passwordRules = current.passwordRules,
                        passwordChanged = true
                    )
                },
                onFailure = { error ->
                    val serverMessage = error.message?.takeIf { it.isNotBlank() }
                    _state.update {
                        it.copy(
                            isSubmitting = false,
                            requestErrorMessage = serverMessage,
                            toast = serverMessage?.let { m -> ChangePasswordToast.Error(m) }
                                ?: ChangePasswordToast.Failed
                        )
                    }
                }
            )
        }
    }

    fun onToastShown() {
        _state.update { it.copy(toast = null) }
    }

    fun onPasswordChangedHandled() {
        _state.update { it.copy(passwordChanged = false) }
    }

    private fun loadPasswordRules() {
        scope.launch {
            profileRepository.getPasswordRules()
                .onSuccess { rules -> _state.update { it.copy(passwordRules = rules) } }
                .onFailure { error ->
                    val serverMessage = error.message?.takeIf { it.isNotBlank() }
                    _state.update {
                        it.copy(
                            toast = serverMessage?.let { m -> ChangePasswordToast.Error(m) }
                                ?: ChangePasswordToast.RulesLoadFailed
                        )
                    }
                }
        }
    }
}

/** 校验失败提示（对齐原工程 toast 优先级：规则错误 → 长度 → 不一致 → 必填）。 */
private fun ChangePasswordUiState.validationToast(): ChangePasswordToast =
    passwordRuleError?.let { ChangePasswordToast.Error(it) }
        ?: if (isPasswordLengthInvalid) {
            passwordRules.description.takeIf { it.isNotBlank() }
                ?.let { ChangePasswordToast.Error(it) }
                ?: if (newPassword.length < passwordRules.minLength) {
                    ChangePasswordToast.MinLength(passwordRules.minLength)
                } else {
                    ChangePasswordToast.MaxLength(passwordRules.maxLength)
                }
        } else if (isConfirmMismatch) {
            ChangePasswordToast.ConfirmMismatch
        } else {
            ChangePasswordToast.Required
        }
