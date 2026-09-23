package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.plugins.HttpTimeout
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.serialization.kotlinx.json.json

/**
 * API 客户端工厂（openspec/changes/migrate-network-and-login/design.md 决策 2/3/5）。
 * 引擎按平台（[createPlatformHttpClient]）；超时 30s/30s/30s 对齐原工程 OkHttp 配置；
 * 序列化走 ContentNegotiation + [ApiJson]。日志与全局计数插件在任务 3.5 装配。
 */
fun createApiClient(): HttpClient = createPlatformHttpClient {
    install(ContentNegotiation) {
        json(ApiJson)
    }
    install(HttpTimeout) {
        requestTimeoutMillis = NETWORK_TIMEOUT_MILLIS
        connectTimeoutMillis = NETWORK_TIMEOUT_MILLIS
        socketTimeoutMillis = NETWORK_TIMEOUT_MILLIS
    }
    // 脱敏网络日志：仅测试环境输出（tasks 3.5 / spec「请求日志与脱敏」）
    installNetworkLogging()
}

const val NETWORK_TIMEOUT_MILLIS = 30_000L
