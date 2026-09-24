package com.example.kmpoh.logger

import kotlinx.cinterop.ExperimentalForeignApi
import platform.PerformanceAnalysisKit.HiLog.LOG_APP
import platform.PerformanceAnalysisKit.HiLog.LOG_INFO
import platform.PerformanceAnalysisKit.HiLog.OH_LOG_PrintMsg

/**
 * 鸿蒙端经 Kotlin/Native 工具链自带 cinterop（platform.PerformanceAnalysisKit.HiLog → libhilog_ndk.z）
 * 直调 HiLog NDK C-API，输出可在 DevEco「日志 → HiLog」页签 / `hdc shell hilog` 按 tag 过滤。
 *
 * - 级别固定 LOG_INFO：系统可控最低级别可能滤掉 DEBUG，INFO 保证默认可见；
 *   prod 静默由 Logger.isTestEnvironment 把关。
 * - domain 0x0001 对齐 Technician-Harmony 的 Constants.LOG_DOMAIN；tag 用 Logger 传入值。
 * - OH_LOG_PrintMsg（@since 18，本工程 compatibleSdkVersion 20）非变参、消息原文直出，
 *   无 printf 转义与 {private} 遮蔽问题。
 */
private const val LOG_DOMAIN = 0x0001u

@OptIn(ExperimentalForeignApi::class)
actual fun platformLogLine(tag: String, message: String) {
    OH_LOG_PrintMsg(LOG_APP, LOG_INFO, LOG_DOMAIN, tag, message)
}
