package com.example.kmpoh.network.signature

import kotlinx.cinterop.ExperimentalForeignApi
import platform.posix.time

@OptIn(ExperimentalForeignApi::class)
actual fun currentEpochSeconds(): Long = time(null).toLong()
