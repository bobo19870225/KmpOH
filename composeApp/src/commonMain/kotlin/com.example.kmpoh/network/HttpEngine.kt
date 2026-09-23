package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.HttpClientConfig

/**
 * 创建平台 HTTP 客户端（openspec/changes/migrate-network-and-login/design.md 决策 2）：
 * Android = OkHttp 引擎、iOS = Darwin 引擎、鸿蒙 = ktor-client-cio 的 CIO 引擎
 * （官方三方库适配工件，工厂 io.ktor.client.engine.cio.CIO，显式传入——
 *  鸿蒙端引擎服务发现不可用）。
 */
expect fun createPlatformHttpClient(block: HttpClientConfig<*>.() -> Unit = {}): HttpClient
