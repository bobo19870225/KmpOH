package com.example.kmpoh.data.model.entity

/**
 * 用户实体（领域模型，由 Repository 从 DTO 转换而来）。
 * 禁止在 UI 层直接使用，须转换为 UserUiModel（对齐原工程分层约定）。
 *
 * 原工程此类型同时是 Room 表映射；本期无本地库，Room 缓存随 SQLDelight 迁移补入。
 */
data class UserEntity(
    /** 本地占位主键（登录响应无本地主键，对齐原工程固定为 1） */
    val id: Long,
    val userId: Int,
    val name: String
)
