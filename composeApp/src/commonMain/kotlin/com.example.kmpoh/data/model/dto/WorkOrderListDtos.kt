package com.example.kmpoh.data.model.dto

import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable

/** 日工单接口 data 节点（原样迁原工程，含防御式分页字段）。 */
@Serializable
data class DayOrderDataDto(
    val list: List<WorkOrderDto> = emptyList(),
    @SerialName("be_gein")
    val begin: List<WorkOrderDto> = emptyList(),
    @SerialName("in_progress")
    val inProgress: List<WorkOrderDto> = emptyList(),
    val complete: List<WorkOrderDto> = emptyList(),
    @SerialName("be_gein_count")
    val beginCount: Int = 0,
    @SerialName("in_progress_count")
    val inProgressCount: Int = 0,
    @SerialName("complete_count")
    val completeCount: Int = 0,
    @SerialName("be_gein_page")
    val beginPage: Int = 1,
    @SerialName("be_gein_current_page")
    val beginCurrentPage: Int = 1,
    @SerialName("in_progress_page")
    val inProgressPage: Int = 1,
    @SerialName("in_progress_current_page")
    val inProgressCurrentPage: Int = 1,
    @SerialName("complete_page")
    val completePage: Int = 1,
    @SerialName("complete_current_page")
    val completeCurrentPage: Int = 1
)

@Serializable
data class WorkOrderColorConfigDto(
    @SerialName("risk_title")
    val riskTitle: Map<String, String> = emptyMap()
)

/** 指定日期前未完成工单日期 DTO。 */
@Serializable
data class UnfinishedJobDateDto(
    @SerialName("job_date")
    val jobDate: String = ""
)

/** 日历月份工单数量 DTO。 */
@Serializable
data class WorkOrderDayCountDto(
    val date: String = "",
    val count: Int = 0,
    val unfinish: Int = 0,
    val overdue: Int = 0
)

/** 日工单接口 DTO（原样迁原工程启用字段；注释停用字段随原文件保留于归档）。 */
@Serializable
data class WorkOrderDto(
    @SerialName("id") val id: Long,
    @SerialName("job_id") val jobId: Long? = null,
    @SerialName("job_type") val jobType: Long? = null,
    @SerialName("job_date") val jobDate: String? = null,
    @SerialName("job_start_time") val jobStartTime: String? = null,
    @SerialName("job_end_time") val jobEndTime: String? = null,
    val status: Int? = null,
    val addr: String? = null,
    @SerialName("customer_id") val customerId: Long? = null,
    @SerialName("customer_code") val customerCode: String? = null,
    @SerialName("customer_name") val customerName: String? = null,
    @SerialName("name_zh") val nameZh: String? = null,
    @SerialName("contact_name") val contactName: String? = null,
    @SerialName("contact_mobile") val contactMobile: String? = null,
    @SerialName("customer_type") val customerType: kotlinx.serialization.json.JsonElement? = null,
    @SerialName("customer_type_text") val customerTypeText: String? = null,
    val mobile: String? = null,
    val tel: String? = null,
    val lat: kotlinx.serialization.json.JsonElement? = null,
    val lng: kotlinx.serialization.json.JsonElement? = null,
    @SerialName("service_type") val serviceType: Long? = null,
    @SerialName("service_type_name") val serviceTypeName: String? = null,
    @SerialName("service_type_alias_name") val serviceTypeAliasName: String? = null,
    @SerialName("risk_title") val riskTitle: String? = null,
    @SerialName("level_title") val levelTitle: String? = null,
    @SerialName("risk_level") val riskLevel: String? = null,
    @SerialName("data_type") val dataType: String? = null,
    @SerialName("need_sign_in") val needSignIn: Int? = null,
    @SerialName("job_progress") val jobProgress: kotlinx.serialization.json.JsonElement? = null,
    @SerialName("display_tags") val displayTags: List<DisplayTagDto> = emptyList(),
    val remarks: String? = null,
    @SerialName("first_job_flag") val firstJobFlag: kotlinx.serialization.json.JsonElement? = null
)

@Serializable
data class DisplayTagDto(
    val key: String = "",
    val text: String = ""
)
