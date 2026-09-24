package com.example.kmpoh.logger

actual fun platformLogLine(level: LogLevel, tag: String, message: String) {
    // iOS 维持 stdout 出口（os_log 属后续变更）；级别用单字母前缀标记
    val marker = when (level) {
        LogLevel.DEBUG -> "D"
        LogLevel.INFO -> "I"
        LogLevel.WARN -> "W"
        LogLevel.ERROR -> "E"
    }
    println("[$marker/$tag] $message")
}
