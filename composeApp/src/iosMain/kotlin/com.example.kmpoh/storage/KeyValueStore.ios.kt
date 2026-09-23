package com.example.kmpoh.storage

import platform.Foundation.NSUserDefaults

actual fun createKeyValueStore(): KeyValueStore = IosKeyValueStore()

private class IosKeyValueStore : KeyValueStore {

    private val defaults get() = NSUserDefaults.standardUserDefaults

    override fun getString(key: String): String? = defaults.stringForKey(key)

    override fun putString(key: String, value: String) {
        defaults.setObject(value, forKey = key)
        // 凭证写入后立即落盘：synchronize 虽被标注为通常不需要，
        // 但它是唯一保证同步写盘的入口，避免「登录后随即杀进程」丢令牌（design 决策 6）。
        defaults.synchronize()
    }

    override fun remove(key: String) {
        defaults.removeObjectForKey(key)
        defaults.synchronize()
    }
}
