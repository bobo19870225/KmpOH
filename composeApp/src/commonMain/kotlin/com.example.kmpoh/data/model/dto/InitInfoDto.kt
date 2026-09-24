package com.example.kmpoh.data.model.dto

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable

/**
 * `Order.Order/initInfo` 接口 data 节点（本变更只取密码状态；工单迁移时在此扩展
 * `color_config` 等字段并复用）。`pass_status` 缺失视为无需改密（spec data/profile）。
 */
@Serializable
data class InitInfoDto(
    @SerialName("pass_status")
    val passStatus: Int? = null
)
