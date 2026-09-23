package com.example.kmpoh.storage

import kotlin.random.Random

/**
 * 平台标识与设备标识（openspec/changes/migrate-network-and-login/design.md 决策 6/8）。
 */

/** 登录请求 `platform` 字段取值（Open Question 1：联调确认后可仅调此处常量）。 */
expect val PLATFORM_NAME: String

/**
 * 设备标识：首次生成 UUID 并持久化到 [KeyValueStore]，之后稳定读取。
 */
fun getOrCreateDeviceId(store: KeyValueStore): String {
    val existing = store.getString(StorageKeys.DEVICE_ID)?.takeIf { it.isNotBlank() }
    if (existing != null) return existing
    val created = randomUuidString()
    store.putString(StorageKeys.DEVICE_ID, created)
    return created
}

/** 纯 Kotlin UUID v4（16 字节随机 + version/variant 位），不依赖平台 API。 */
internal fun randomUuidString(): String {
    val rnd = Random.Default
    val bytes = ByteArray(16) { rnd.nextInt(256).toByte() }
    bytes[6] = ((bytes[6].toInt() and 0x0f) or 0x40).toByte() // version 4
    bytes[8] = ((bytes[8].toInt() and 0x3f) or 0x80).toByte() // variant 10xx
    val hex = bytes.joinToString("") { (it.toInt() and 0xff).toString(16).padStart(2, '0') }
    return buildString(36) {
        append(hex, 0, 8); append('-')
        append(hex, 8, 12); append('-')
        append(hex, 12, 16); append('-')
        append(hex, 16, 20); append('-')
        append(hex, 20, 32)
    }
}
