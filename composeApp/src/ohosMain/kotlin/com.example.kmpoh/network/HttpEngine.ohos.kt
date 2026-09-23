package com.example.kmpoh.network

import com.example.kmpoh.network.bridge.RcpHttpClientEngine
import io.ktor.client.HttpClient
import io.ktor.client.HttpClientConfig

// 鸿蒙端 HTTP(S) 走系统 TLS 栈：ktor-network-tls 的 nonJvm 端是 error() 桩
//（openTLSSession 抛 "TLS sessions are not supported on Native platform"，
//  所有 fork 版本线皆然），CIO 引擎无法完成 TLS 握手，HTTPS 不可用。
// 故用自定义引擎 RcpHttpClientEngine，经手写 NAPI 桥接 ArkTS RCP
//（RemoteCommunicationKit，对齐 Technician-Harmony 的 RcpSession 方案）。
// 背景与线协议见 bridge/OhosHttpTransport.kt、bridge/RcpHttpClientEngine.kt。
actual fun createPlatformHttpClient(block: HttpClientConfig<*>.() -> Unit): HttpClient =
    HttpClient(RcpHttpClientEngine(), block)
