package com.example.kmpoh.network

import com.example.kmpoh.storage.FakeKeyValueStore
import kotlin.test.Test
import kotlin.test.assertNull

class AuthSessionManagerTest {

    @Test
    fun clearTokensRemovesAccessAndRefreshTokens() {
        val session = AuthSessionManager(FakeKeyValueStore())
        session.saveTokens("tok-1", "ref-1")
        session.clearTokens()
        assertNull(session.accessToken())
        assertNull(session.refreshToken())
    }
}
