package com.example.kmpoh.storage

import android.content.Context
import android.content.SharedPreferences

/**
 * Android 应用上下文持有者。SharedPreferences 需要 Context，
 * 由 MainActivity.onCreate 首行调用 [init] 注入（design 决策 6）。
 */
object AndroidAppContext {
    @Volatile
    private var appContext: Context? = null

    fun init(context: Context) {
        appContext = context.applicationContext
    }

    internal fun require(): Context =
        checkNotNull(appContext) {
            "AndroidAppContext.init(context) must be called before KeyValueStore is used"
        }
}

actual fun createKeyValueStore(): KeyValueStore = AndroidKeyValueStore()

private class AndroidKeyValueStore : KeyValueStore {

    private val prefs: SharedPreferences
        get() = AndroidAppContext.require().getSharedPreferences(PREFERENCES_NAME, Context.MODE_PRIVATE)

    override fun getString(key: String): String? = prefs.getString(key, null)

    override fun putString(key: String, value: String) {
        prefs.edit().putString(key, value).apply()
    }

    override fun remove(key: String) {
        prefs.edit().remove(key).apply()
    }

    private companion object {
        const val PREFERENCES_NAME = "kmpoh_kv"
    }
}
