package com.example.kmpoh.logger

import android.util.Log

actual fun platformLogLine(level: LogLevel, tag: String, message: String) {
    // 分片后 ≤3000 字符，规避 logcat 单条 ~4KB 上限
    when (level) {
        LogLevel.DEBUG -> Log.d(tag, message)
        LogLevel.INFO -> Log.i(tag, message)
        LogLevel.WARN -> Log.w(tag, message)
        LogLevel.ERROR -> Log.e(tag, message)
    }
}
