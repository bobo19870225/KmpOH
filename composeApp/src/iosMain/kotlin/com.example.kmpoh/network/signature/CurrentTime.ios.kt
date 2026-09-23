package com.example.kmpoh.network.signature

import platform.Foundation.NSDate
import platform.Foundation.timeIntervalSince1970

actual fun currentEpochSeconds(): Long = NSDate().timeIntervalSince1970.toLong()
