package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.HttpClientConfig

/**
 * 创建平台 HTTP 客户端（openspec/changes/migrate-network-and-login/design.md 决策 2）：
 * Android = OkHttp 引擎、iOS = Darwin 引擎、鸿蒙 = 自定义 RcpHttpClientEngine
 * （经 NAPI 桥接 ArkTS RCP 系统网络栈——ktor-network-tls nonJvm 无 TLS 实现，
 *  CIO 不能用于 HTTPS；见 ohosMain 的 bridge/ 包）。
 */
expect fun createPlatformHttpClient(block: HttpClientConfig<*>.() -> Unit = {}): HttpClient
