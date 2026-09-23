package com.example.kmpoh.storage

/**
 * 跨端轻量字符串 KV 存储（openspec/changes/migrate-network-and-login/design.md 决策 6）：
 * Android = SharedPreferences、iOS = NSUserDefaults、鸿蒙 = Native Preferences
 * （经工具链 cinterop `platform.ArkData.Preferences` 直调 libohpreferences，无需 ArkTS 桥接）。
 *
 * 注：本期为普通 KV（用户决策），弱于原工程 AndroidKeyStore 加密存储；
 * 加密升级列入后续变更。
 */
interface KeyValueStore {
    fun getString(key: String): String?
    fun putString(key: String, value: String)
    fun remove(key: String)
}

/** 存储键名，沿用原工程 SecureStorageKeys 的命名约定。 */
object StorageKeys {
    const val AUTH_ACCESS_TOKEN = "auth.access_token"
    const val AUTH_REFRESH_TOKEN = "auth.refresh_token"
    const val DEVICE_ID = "device.id"
}

/** 创建平台默认 KV 存储实例。 */
expect fun createKeyValueStore(): KeyValueStore
