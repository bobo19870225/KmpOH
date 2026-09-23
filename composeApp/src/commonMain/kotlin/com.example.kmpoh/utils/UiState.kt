package com.example.kmpoh.utils

/**
 * 统一页面加载状态
 *
 * 【全局状态管理规范】
 * 所有页面的加载状态必须统一封装为以下五种状态。
 * 严禁各页面自定义状态枚举。
 *
 * 使用方式：
 *   sealed class UiState<out T> {
 *       object Loading : UiState<Nothing>()
 *       data class Success<T>(val data: T) : UiState<T>()
 *       object Empty : UiState<Nothing>()
 *       data class Error(val message: String, val throwable: Throwable? = null) : UiState<Nothing>()
 *       object NoPermission : UiState<Nothing>()
 *   }
 *
 * ViewModel 中通过 StateFlow 管理：
 *   private val _uiState = MutableStateFlow<UiState<List<UserUiModel>>>(UiState.Loading)
 *   val uiState: StateFlow<UiState<List<UserUiModel>>> = _uiState.asStateFlow()
 */
sealed class UiState<out T> {

    /** 空闲：尚未发起加载 */
    data object Idle : UiState<Nothing>()

    /** 加载中：显示 LoadingView */
    data object Loading : UiState<Nothing>()

    /** 成功：显示数据内容 */
    data class Success<T>(val data: T) : UiState<T>()

    /** 空数据：显示空状态占位图 */
    data object Empty : UiState<Nothing>()

    /** 异常：显示错误信息与重试按钮 */
    data class Error(
        val message: String,
        val throwable: Throwable? = null
    ) : UiState<Nothing>()

    /** 无权限：显示无权限提示与引导 */
    data object NoPermission : UiState<Nothing>()
}
