package com.example.kmpoh.data.model.ui

import com.example.kmpoh.data.model.entity.UserEntity

/**
 * 用户 UI 模型（对齐原工程 data/model/ui/UserUiModel.kt）。
 * fromEntity 的 maskedPhone/avatarUrl/role/email 为**原工程既有占位行为**（都塞了 name），
 * 本期原样保留（design 决策 8），修正列入后续变更。
 */
data class UserUiModel(
    val id: Long,
    val displayName: String,
    val maskedPhone: String,
    val avatarUrl: String,
    /** 角色原始编码（admin / technician / manager），UI 层映射为中文标签 */
    val role: String,
    val email: String = ""
) {
    companion object {
        fun fromEntity(entity: UserEntity): UserUiModel = UserUiModel(
            id = entity.id,
            displayName = entity.name,
            maskedPhone = maskPhone(entity.name),
            avatarUrl = entity.name,
            role = entity.name,
            email = entity.name
        )

        private fun maskPhone(phone: String): String {
            if (phone.length < 7) return phone
            return phone.substring(0, 3) + "****" + phone.takeLast(4)
        }
    }
}
