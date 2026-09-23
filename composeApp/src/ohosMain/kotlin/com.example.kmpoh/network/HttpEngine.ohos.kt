package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.HttpClientConfig

// 鸿蒙端引擎内置于 ktor-client-core 的 ohosArm64 变体（klib 含 CIOEngine/CIOEngineConfig
// 与 nonJvm 引擎装载器），无独立引擎 artifact，故走默认引擎装载。
actual fun createPlatformHttpClient(block: HttpClientConfig<*>.() -> Unit): HttpClient =
    HttpClient(block)
