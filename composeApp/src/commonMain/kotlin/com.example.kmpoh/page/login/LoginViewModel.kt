package com.example.kmpoh.page.login

import com.example.kmpoh.utils.UiState
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch

/**
 * 登录页状态容器。
 *
 * 【为何不继承 androidx.lifecycle.ViewModel】
 * 官方 KMP lifecycle 无 `ohosArm64` 变体，而 Nexus 中两条 fork 路线在 Android 端
 * 分别因「要求 AGP 9.1+」与「与 Google 官方 artifact 类重复」而不可用 —— 即当前依赖
 * 组合下官方 ViewModel 无法同时满足 Android 与鸿蒙两端。故此处退化为自写纯 Kotlin
 * 容器（零新依赖），由页面用 `remember` 持有，协程作用域由页面传入。
 * 完整实测记录见 openspec/changes/migrate-login-page-ui/design.md 决策 1。
 *
 * 状态结构与对外 API 与原安卓工程 `LoginViewModel` 保持一致，
 * 后续接入网络层时只需替换依赖，本类与 UI 不动。
 *
 * 【关于 uiState 的负载类型】
 * 原工程为 `UiState<UserUiModel>`；用户数据模型属于数据层，不在本次范围内，
 * 故暂用 `Unit` 占位。接入网络层时替换为真实的用户模型。
 */
class LoginViewModel(
    private val repository: FakeLoginRepository,
    private val scope: CoroutineScope
) {

    private val _uiState = MutableStateFlow<UiState<Unit>>(UiState.Idle)
    val uiState: StateFlow<UiState<Unit>> = _uiState.asStateFlow()

    private val _phone = MutableStateFlow("")
    val phone: StateFlow<String> = _phone.asStateFlow()

    private val _password = MutableStateFlow("")
    val password: StateFlow<String> = _password.asStateFlow()

    /** 仅在账号与密码去除首尾空白后均非空时为真。 */
    private val _loginEnabled = MutableStateFlow(false)
    val loginEnabled: StateFlow<Boolean> = _loginEnabled.asStateFlow()

    /** 一次性提示消息；UI 消费后须调用 [onToastShown] 清除。 */
    private val _toastMessage = MutableStateFlow<String?>(null)
    val toastMessage: StateFlow<String?> = _toastMessage.asStateFlow()

    fun onPhoneChanged(value: String) {
        _phone.value = value
        refreshLoginEnabled()
    }

    fun onPasswordChanged(value: String) {
        _password.value = value
        refreshLoginEnabled()
    }

    fun onLoginClick() {
        // 双保险：按钮本身在禁用时不响应点击，这里再挡一次，
        // 避免加载期间或状态不同步时重复发起登录。
        if (!_loginEnabled.value) return
        if (_uiState.value is UiState.Loading) return

        val phone = _phone.value.trim()
        val password = _password.value.trim()

        scope.launch {
            _uiState.value = UiState.Loading

            repository.login(phone, password).fold(
                onSuccess = {
                    _uiState.value = UiState.Success(Unit)
                },
                onFailure = { error ->
                    _uiState.value = UiState.Error(
                        message = error.message ?: "",
                        throwable = error
                    )
                    _toastMessage.value = error.message ?: ""
                }
            )
        }
    }

    /** UI 已消费该提示，清除以免页面重组时重复弹出。 */
    fun onToastShown() {
        _toastMessage.value = null
    }

    private fun refreshLoginEnabled() {
        _loginEnabled.value =
            _phone.value.trim().isNotEmpty() && _password.value.trim().isNotEmpty()
    }
}
