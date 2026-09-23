package com.example.kmpoh.network

import com.example.kmpoh.storage.KeyValueStore
import com.example.kmpoh.storage.StorageKeys
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.SharedFlow
import kotlinx.coroutines.flow.asSharedFlow

/** 登录会话事件（对齐原工程 AuthSessionManager）；路由跳转由后续变更接线。 */
sealed interface AuthSessionEvent {
    data class LoginExpired(val message: String) : AuthSessionEvent
}

/**
 * 会话令牌读写与「登录已失效」事件分发（openspec/changes/migrate-network-and-login/design.md 决策 5/6）。
 * 令牌持久化在 [KeyValueStore]（键名见 [StorageKeys]）。
 */
class AuthSessionManager(private val store: KeyValueStore) {

    private val _events = MutableSharedFlow<AuthSessionEvent>(extraBufferCapacity = 1)
    val events: SharedFlow<AuthSessionEvent> = _events.asSharedFlow()

    fun accessToken(): String? =
        store.getString(StorageKeys.AUTH_ACCESS_TOKEN)?.takeIf { it.isNotBlank() }

    fun refreshToken(): String? =
        store.getString(StorageKeys.AUTH_REFRESH_TOKEN)?.takeIf { it.isNotBlank() }

    /** 对齐原工程：刷新成功后 access/refresh 同值保存。 */
    fun saveTokens(accessToken: String, refreshToken: String) {
        store.putString(StorageKeys.AUTH_ACCESS_TOKEN, accessToken)
        store.putString(StorageKeys.AUTH_REFRESH_TOKEN, refreshToken)
    }

    fun clearTokens() {
        store.remove(StorageKeys.AUTH_ACCESS_TOKEN)
        store.remove(StorageKeys.AUTH_REFRESH_TOKEN)
    }

    fun notifyLoginExpired(message: String = NetworkMessages.LOGIN_EXPIRED) {
        _events.tryEmit(AuthSessionEvent.LoginExpired(message))
    }
}
