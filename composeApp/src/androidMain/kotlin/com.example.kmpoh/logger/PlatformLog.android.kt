package com.example.kmpoh.logger

import android.util.Log

actual fun platformLogLine(tag: String, message: String) {
    // 分片后 ≤3000 字符，规避 logcat 单条 ~4KB 上限
    Log.d(tag, message)
}
