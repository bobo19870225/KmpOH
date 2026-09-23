package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.HttpClientConfig

/**
 * 创建平台 HTTP 客户端（openspec/changes/migrate-network-and-login/design.md 决策 2）：
 * Android = OkHttp 引擎、iOS = Darwin 引擎、鸿蒙 = ktor-client-core 的 ohosArm64 变体
 * 内置引擎（klib 内含 CIOEngine 符号与 nonJvm Loader，经引擎装载自动解析，
 * Nexus 无独立引擎 artifact）。
 */
expect fun createPlatformHttpClient(block: HttpClientConfig<*>.() -> Unit = {}): HttpClient
