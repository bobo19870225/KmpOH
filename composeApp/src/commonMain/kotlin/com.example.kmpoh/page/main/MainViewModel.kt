package com.example.kmpoh.page.main

import com.example.kmpoh.data.repository.ProfileRepository
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

data class MainUiState(
    val requiresPasswordChange: Boolean = false,
    val isCheckingPasswordStatus: Boolean = false
)

/**
 * 主框架壳 ViewModel（spec ui/profile「强制修改密码提示」）：密码状态查询。
 * 触发点：进入 Main 路由时刷新一次（design 决策 4，简化原工程 ON_RESUME）；
 * 查询失败按「无需改密」处理、不阻断主框架。自写纯 Kotlin 状态容器（对齐 LoginViewModel 样板）。
 */
class MainViewModel(
    private val profileRepository: ProfileRepository,
    private val scope: CoroutineScope
) {
    private val _state = MutableStateFlow(MainUiState())
    val state: StateFlow<MainUiState> = _state.asStateFlow()

    init {
        refreshPasswordStatus()
    }

    fun refreshPasswordStatus() {
        scope.launch {
            _state.update { it.copy(isCheckingPasswordStatus = true) }
            profileRepository.loadPasswordStatus()
                .onSuccess { passStatus ->
                    _state.update {
                        it.copy(
                            requiresPasswordChange = passStatus == 0,
                            isCheckingPasswordStatus = false
                        )
                    }
                }
                .onFailure {
                    _state.update { it.copy(requiresPasswordChange = false, isCheckingPasswordStatus = false) }
                }
        }
    }
}
