package com.example.kmpoh.network

import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update

/** 全局加载跳过标记（对齐原工程 X-Show-Global-Loading 控制头；发送前会从请求上剥掉）。 */
const val HEADER_SHOW_GLOBAL_LOADING = "X-Show-Global-Loading"

/**
 * 全局请求计数（对齐原工程 NetworkRequestTracker）：任意请求数 > 0 即为忙碌，
 * 供界面消费。跳过标记的请求不计入；计数随请求结束（无论成败）正确回落。
 *
 * 计数用 StateFlow.update（CAS）保证跨线程安全，零额外依赖。
 */
class NetworkRequestTracker {

    private val _activeRequests = MutableStateFlow(0)

    /** 进行中的请求数（> 0 即忙碌）。 */
    val activeRequests: StateFlow<Int> = _activeRequests.asStateFlow()

    fun onRequestStarted() {
        _activeRequests.update { it + 1 }
    }

    fun onRequestFinished() {
        _activeRequests.update { (it - 1).coerceAtLeast(0) }
    }

    companion object {
        /** 应用内共享实例。 */
        val global = NetworkRequestTracker()
    }
}
