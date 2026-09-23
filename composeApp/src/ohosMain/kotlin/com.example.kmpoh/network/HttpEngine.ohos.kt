package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.HttpClientConfig
import io.ktor.client.engine.cio.CIO

// 鸿蒙端引擎用官方适配的 ktor-client-cio（CPF-KMP-CMP 三方库文档，3.3.3-1.0.0），
// 工厂为 io.ktor.client.engine.cio.CIO。不能用无参 HttpClient()——服务发现在鸿蒙
// 不可用（抛 "Failed to find HTTP client engine implementation"，nova 13 实测）；
// 也不能用 ktor-client-core 内置的 io.ktor.client.utils.CIO 替代品——功能不完整，
// 网络请求异常。依赖在 ohosMain.dependencies 声明。
actual fun createPlatformHttpClient(block: HttpClientConfig<*>.() -> Unit): HttpClient =
    HttpClient(CIO, block)
