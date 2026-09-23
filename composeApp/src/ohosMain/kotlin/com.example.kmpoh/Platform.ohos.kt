package com.example.kmpoh

import kotlin.experimental.ExperimentalNativeApi

@OptIn(ExperimentalNativeApi::class)
class OhosPlatform : Platform {
    override val name: String = "HarmonyOS"
}

@OptIn(ExperimentalNativeApi::class)
actual fun getPlatform(): Platform = OhosPlatform()

