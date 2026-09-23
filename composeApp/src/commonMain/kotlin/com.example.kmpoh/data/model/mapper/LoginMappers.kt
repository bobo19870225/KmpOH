package com.example.kmpoh.data.model.mapper

import com.example.kmpoh.data.model.dto.LoginResponseDto
import com.example.kmpoh.data.model.entity.UserEntity
import com.example.kmpoh.data.model.ui.UserUiModel

/**
 * 登录链 DTO → Entity → UiModel 显式映射（对齐原工程 mapper 约定）。
 * 令牌取值兼容规则与原工程 AuthInterceptor / LoginRepository 一致。
 */

/** `token` 优先，为空取 `access_token`。 */
fun resolveAccessToken(token: String, accessToken: String): String = token.ifBlank { accessToken }

/** `refresh_token` 为空时以访问令牌兜底。 */
fun resolveRefreshToken(refreshToken: String, accessToken: String): String = refreshToken.ifBlank { accessToken }

/** 登录响应携带的访问令牌（主字段优先）。 */
fun LoginResponseDto.effectiveAccessToken(): String = resolveAccessToken(token, accessToken)

/** 登录响应携带的刷新令牌（为空兜底访问令牌）。 */
fun LoginResponseDto.effectiveRefreshToken(): String = resolveRefreshToken(refreshToken, effectiveAccessToken())

/** 组装用户实体（本地主键固定 1，对齐原工程）。 */
fun LoginResponseDto.toUserEntity(): UserEntity = UserEntity(id = 1, userId = userId, name = name)

fun UserEntity.toUiModel(): UserUiModel = UserUiModel.fromEntity(this)
