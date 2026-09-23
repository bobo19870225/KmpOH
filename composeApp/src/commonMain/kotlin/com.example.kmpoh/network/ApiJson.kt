package com.example.kmpoh.network

import kotlinx.serialization.json.Json

/**
 * 全局 Json 配置，逐项对齐原工程 AppModule.provideJson()：
 * ignoreUnknownKeys / coerceInputValues / explicitNulls=false / encodeDefaults=true。
 */
val ApiJson: Json = Json {
    ignoreUnknownKeys = true
    coerceInputValues = true
    explicitNulls = false
    encodeDefaults = true
}
