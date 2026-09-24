package com.example.kmpoh.logger

import kotlinx.cinterop.ExperimentalForeignApi
import platform.PerformanceAnalysisKit.HiLog.LOG_APP
import platform.PerformanceAnalysisKit.HiLog.LOG_DEBUG
import platform.PerformanceAnalysisKit.HiLog.LOG_ERROR
import platform.PerformanceAnalysisKit.HiLog.LOG_INFO
import platform.PerformanceAnalysisKit.HiLog.LOG_WARN
import platform.PerformanceAnalysisKit.HiLog.OH_LOG_PrintMsg

/** HiLog 服务域：0x0001 对齐 Technician-Harmony 的 Constants.LOG_DOMAIN。 */
private const val LOG_DOMAIN = 0x0001u

/**
 * 鸿蒙端经 Kotlin/Native 工具链自带 cinterop（platform.PerformanceAnalysisKit.HiLog → libhilog_ndk.z）
 * 直调 HiLog NDK C-API，输出可在 DevEco「日志 → HiLog」页签 / `hdc shell hilog` 按级别/tag 过滤。
 *
 * - [LogLevel] 逐级映射 OH_LOG 级别；DEBUG 可见性取决于系统最低级别设置
 *   （DevEco 页签级别筛选 / `hilog -L D` 可看）。
 * - tag 用 Logger 传入值；prod 静默与脱敏在 Logger 层把关。
 * - OH_LOG_PrintMsg（@since 18，本工程 compatibleSdkVersion 20）非变参、消息原文直出，
 *   无 printf 转义与 {private} 遮蔽问题。
 */
@OptIn(ExperimentalForeignApi::class)
actual fun platformLogLine(level: LogLevel, tag: String, message: String) {
    val nativeLevel = when (level) {
        LogLevel.DEBUG -> LOG_DEBUG
        LogLevel.INFO -> LOG_INFO
        LogLevel.WARN -> LOG_WARN
        LogLevel.ERROR -> LOG_ERROR
    }
    OH_LOG_PrintMsg(LOG_APP, nativeLevel, LOG_DOMAIN, tag, message)
}
