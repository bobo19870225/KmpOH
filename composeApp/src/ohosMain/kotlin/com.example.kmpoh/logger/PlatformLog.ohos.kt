package com.example.kmpoh.logger

actual fun platformLogLine(tag: String, message: String) {
    // stdout 由 hilog 侧捕获；如需原生 hilog 可后续接 OH_LOG C-API（hilog_ndk 已链接）
    println("[$tag] $message")
}
