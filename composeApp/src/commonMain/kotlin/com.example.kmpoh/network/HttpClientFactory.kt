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
    // 网络日志统一收敛在信封出口 requestEnvelopeText（url+参数+响应 两行制，
    // 脱敏+8KB 裁剪、测试环境门控；原 Ktor Logging 插件碎片输出已移除）
}

const val NETWORK_TIMEOUT_MILLIS = 30_000L
