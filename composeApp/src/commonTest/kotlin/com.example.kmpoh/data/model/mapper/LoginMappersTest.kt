package com.example.kmpoh.data.model.mapper

import com.example.kmpoh.data.model.dto.LoginResponseDto
import com.example.kmpoh.data.model.entity.UserEntity
import kotlin.test.Test
import kotlin.test.assertEquals

class LoginMappersTest {

    @Test
    fun tokenFieldCompatibilityRules() {
        // token 优先
        assertEquals("tok", resolveAccessToken(token = "tok", accessToken = "acc"))
        // token 为空取 access_token
        assertEquals("acc", resolveAccessToken(token = "", accessToken = "acc"))
        // refresh 为空兜底 access
        assertEquals("acc", resolveRefreshToken(refreshToken = "", accessToken = "acc"))
        assertEquals("ref", resolveRefreshToken(refreshToken = "ref", accessToken = "acc"))
    }

    @Test
    fun loginResponseResolvesEffectiveTokens() {
        val dto = LoginResponseDto(token = "", accessToken = "acc", refreshToken = "")
        assertEquals("acc", dto.effectiveAccessToken())
        assertEquals("acc", dto.effectiveRefreshToken())

        val full = LoginResponseDto(token = "tok", accessToken = "acc", refreshToken = "ref")
        assertEquals("tok", full.effectiveAccessToken())
        assertEquals("ref", full.effectiveRefreshToken())
    }

    @Test
    fun dtoToEntityKeepsIdentity() {
        val entity = LoginResponseDto(token = "t", userId = 7, name = "张三").toUserEntity()
        assertEquals(UserEntity(id = 1, userId = 7, name = "张三"), entity)
    }

    @Test
    fun entityToUiModelKeepsOriginalPlaceholderBehavior() {
        val model = UserEntity(id = 1, userId = 7, name = "13812345678").toUiModel()
        assertEquals(1, model.id)
        assertEquals("13812345678", model.displayName)
        // 原工程占位怪癖：maskedPhone 对 name 做手机号掩码（design 决策 8 原样保留）
        assertEquals("138****5678", model.maskedPhone)
        assertEquals("13812345678", model.avatarUrl)
        assertEquals("13812345678", model.role)
        assertEquals("13812345678", model.email)
    }

    @Test
    fun maskPhoneShortValuesPassThrough() {
        val model = UserEntity(id = 1, userId = 1, name = "张三").toUiModel()
        assertEquals("张三", model.maskedPhone)
    }
}
