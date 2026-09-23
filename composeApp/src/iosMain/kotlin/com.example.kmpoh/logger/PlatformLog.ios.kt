package com.example.kmpoh.logger

actual fun platformLogLine(tag: String, message: String) {
    // stdout 进 Xcode 控制台；如需 os_log 统一日志可后续接 NSLog/Logger.framework
    println("[$tag] $message")
}
