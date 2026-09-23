package com.example.kmpoh.data.model.dto

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable

/**
 * 登录请求 DTO（对齐原工程 data/model/dto/LoginRequestDto.kt）。
 * 密码按与服务端既定约定传输（当前与原工程实现一致：JSON 字段原样传输，见 design Open Questions）。
 * DTO 严禁进 UI 层。
 */
@Serializable
data class LoginRequestDto(
    /** 员工编号（不是手机号） */
    @SerialName("staff_code") val staffCode: String,
    val password: String,
    val deviceId: String = "",
    val platform: String = ""
)

/**
 * 登录响应 DTO（对齐原工程 data/model/dto/LoginResponseDto.kt 字段命名）。
 * `location_tracking` 等未纳入字段由 ignoreUnknownKeys 兜底，随对应能力迁移时补入。
 */
@Serializable
data class LoginResponseDto(
    /** 主令牌字段 */
    val token: String = "",
    @SerialName("user_id") val userId: Int = 0,
    val name: String = "",
    val code: String = "",
    val phone: String = "",
    /** 兼容字段（主字段为空时取此字段） */
    @SerialName("access_token") val accessToken: String = "",
    @SerialName("refresh_token") val refreshToken: String = "",
    val user: UserDto? = null
)

/** 用户信息 DTO（对齐原工程 data/model/dto/UserDto.kt）。 */
@Serializable
data class UserDto(
    val id: Long = 0,
    val userId: Int = 0,
    val name: String = "",
    val phone: String = "",
    @SerialName("avatar_url") val avatarUrl: String = "",
    val email: String = "",
    /** 角色：admin/technician/manager */
    val role: String = "",
    @SerialName("is_active") val isActive: Boolean = false
)
