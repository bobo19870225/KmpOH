package com.example.kmpoh.network

import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertFalse
import kotlin.test.assertTrue

class NetworkModelsTest {

    @Test
    fun fiveExceptionCategoriesCarryDocumentedMessages() {
        assertEquals("当前网络不可用，请检查网络", NetworkException.Unavailable().message)
        assertEquals("网络请求超时，请稍后重试", NetworkException.Timeout().message)
        assertEquals("网络连接异常，请稍后重试", NetworkException.Transport().message)
        assertEquals("网络数据解析失败，请稍后重试", NetworkException.Parsing().message)
        assertEquals("HTTP 500：Internal Error", NetworkException.Http(500, "Internal Error").message)
    }

    @Test
    fun envelopeBusinessSuccessIsCode200() {
        assertTrue(ApiResponse<String>(code = 200, msg = "ok", data = "x").isBusinessSuccess())
        assertFalse(ApiResponse<String>(code = 500, msg = "bad").isBusinessSuccess())
    }

    @Test
    fun requireBusinessSuccessThrowsWithCodeAndMessage() {
        val e = assertFailsWith<BusinessApiException> {
            ApiResponse<String>(code = 401, msg = "token 失效").requireBusinessSuccess("默认文案")
        }
        assertEquals(401, e.businessCode)
        assertEquals("token 失效", e.businessMessage)
    }

    @Test
    fun requireBusinessSuccessUsesDefaultWhenMessageBlank() {
        val e = assertFailsWith<BusinessApiException> {
            ApiResponse<String>(code = 500, msg = "").requireBusinessSuccess("默认文案")
        }
        assertEquals("默认文案", e.businessMessage)
    }

    @Test
    fun apiJsonUsesAgreedConfiguration() {
        val config = ApiJson.configuration
        assertTrue(config.ignoreUnknownKeys)
        assertTrue(config.coerceInputValues)
        assertFalse(config.explicitNulls)
        assertTrue(config.encodeDefaults)
    }
}
