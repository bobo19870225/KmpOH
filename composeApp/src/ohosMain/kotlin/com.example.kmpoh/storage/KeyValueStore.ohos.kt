package com.example.kmpoh.storage

import kotlinx.cinterop.ByteVar
import kotlinx.cinterop.CPointerVar
import kotlinx.cinterop.ExperimentalForeignApi
import kotlinx.cinterop.IntVar
import kotlinx.cinterop.UIntVar
import kotlinx.cinterop.alloc
import kotlinx.cinterop.memScoped
import kotlinx.cinterop.ptr
import kotlinx.cinterop.toKString
import kotlinx.cinterop.value
import platform.ArkData.Preferences.OH_Preferences_Close
import platform.ArkData.Preferences.OH_Preferences_Delete
import platform.ArkData.Preferences.OH_Preferences_FreeString
import platform.ArkData.Preferences.OH_Preferences_GetString
import platform.ArkData.Preferences.OH_Preferences_Open
import platform.ArkData.Preferences.OH_Preferences_SetString
import platform.ArkData.Preferences.OH_PreferencesOption_Create
import platform.ArkData.Preferences.OH_PreferencesOption_Destroy
import platform.ArkData.Preferences.OH_PreferencesOption_SetFileName

actual fun createKeyValueStore(): KeyValueStore = OhosPreferencesKeyValueStore()

/**
 * 鸿蒙端经 Kotlin/Native 工具链自带 cinterop（platform.ArkData.Preferences → libohpreferences）
 * 直调 Native Preferences C API（运行期要求 OHOS 13+），无需 ArkTS 存储桥接。
 *
 * 采用「开-写-关」单次操作模式：OH_Preferences_Flush 自 OHOS 23 才可用，
 * 以 Close 收尾落盘；持久化行为由实机验证（tasks 6.4）把关。
 *
 * 注：OH_Preferences/OH_PreferencesOption 为不完整结构体，cinterop 未生成可导入的
 * 类型名（仅在函数签名中以短名出现），故各操作段不显式声明指针类型、全靠返回值推断。
 */
@OptIn(ExperimentalForeignApi::class)
private class OhosPreferencesKeyValueStore : KeyValueStore {

    override fun getString(key: String): String? {
        val option = requireNotNull(OH_PreferencesOption_Create()) { "OH_PreferencesOption_Create failed" }
        try {
            OH_PreferencesOption_SetFileName(option, PREFERENCES_FILE_NAME)
            return memScoped {
                val errCode = alloc<IntVar>()
                val prefs = requireNotNull(OH_Preferences_Open(option, errCode.ptr)) {
                    "OH_Preferences_Open failed, errCode=${errCode.value}"
                }
                try {
                    val value = alloc<CPointerVar<ByteVar>>()
                    val len = alloc<UIntVar>()
                    val rc = OH_Preferences_GetString(prefs, key, value.ptr, len.ptr)
                    val result = if (rc == 0) value.value?.toKString() else null
                    value.value?.let { OH_Preferences_FreeString(it) }
                    result
                } finally {
                    OH_Preferences_Close(prefs)
                }
            }
        } finally {
            OH_PreferencesOption_Destroy(option)
        }
    }

    override fun putString(key: String, value: String) {
        val option = requireNotNull(OH_PreferencesOption_Create()) { "OH_PreferencesOption_Create failed" }
        try {
            OH_PreferencesOption_SetFileName(option, PREFERENCES_FILE_NAME)
            memScoped {
                val errCode = alloc<IntVar>()
                val prefs = requireNotNull(OH_Preferences_Open(option, errCode.ptr)) {
                    "OH_Preferences_Open failed, errCode=${errCode.value}"
                }
                try {
                    OH_Preferences_SetString(prefs, key, value)
                } finally {
                    OH_Preferences_Close(prefs)
                }
            }
        } finally {
            OH_PreferencesOption_Destroy(option)
        }
    }

    override fun remove(key: String) {
        val option = requireNotNull(OH_PreferencesOption_Create()) { "OH_PreferencesOption_Create failed" }
        try {
            OH_PreferencesOption_SetFileName(option, PREFERENCES_FILE_NAME)
            memScoped {
                val errCode = alloc<IntVar>()
                val prefs = requireNotNull(OH_Preferences_Open(option, errCode.ptr)) {
                    "OH_Preferences_Open failed, errCode=${errCode.value}"
                }
                try {
                    OH_Preferences_Delete(prefs, key)
                } finally {
                    OH_Preferences_Close(prefs)
                }
            }
        } finally {
            OH_PreferencesOption_Destroy(option)
        }
    }

    private companion object {
        const val PREFERENCES_FILE_NAME = "kmpoh_kv"
    }
}
