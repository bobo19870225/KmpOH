package com.example.kmpoh.data.model.entity

import kotlinx.datetime.Clock
import kotlinx.serialization.json.JsonElement
import kotlinx.serialization.json.JsonObject
import kotlinx.serialization.json.doubleOrNull
import kotlinx.serialization.json.intOrNull
import kotlinx.serialization.json.jsonPrimitive

/** 工单业务实体，由 Repository 从网络 DTO 转换后使用（原样迁原工程）。 */
data class WorkOrderEntity(
    val id: Long,
    val address: String,
    val customerName: String,
    val customerId: Long,
    val jobDate: String,
    val startTime: String,
    val endTime: String,
    val jobType: Int,
    val status: Int,
    val serviceType: Int,
    val serviceTypeName: String,
    val riskTitle: String,
    val levelTitle: String,
    val customerCode: String,
    val contactName: String,
    val contactMobile: String,
    val mobile: String,
    val telephone: String,
    val latitude: Double,
    val longitude: Double,
    val remarks: String,
    val cachedAtMillis: Long = Clock.System.now().toEpochMilliseconds(),
    val serviceTypeAliasName: String,
    val displayTags: List<WorkOrderDisplayTagEntity> = emptyList(),
    val dataType: String = "job_order",
    val needSignIn: Boolean = false,
    val jobProgress: WorkOrderProgressEntity = WorkOrderProgressEntity()
) {
    val requiresSignIn: Boolean
        get() = needSignIn || status == STATUS_WAITING

    companion object {
        const val JOB_TYPE_UNKNOWN = 0
        const val JOB_TYPE_REPAIR = 1
        const val JOB_TYPE_REVISIT = 2
        const val JOB_TYPE_SURVEY = 3

        const val STATUS_UNKNOWN = 0
        const val STATUS_WAITING = 1
        const val STATUS_RUNNING = 2
        const val STATUS_DONE = 3

        fun fromDto(
            dto: com.example.kmpoh.data.model.dto.WorkOrderDto,
            statusOverride: Int? = null,
            cachedAtMillis: Long = Clock.System.now().toEpochMilliseconds()
        ): WorkOrderEntity = WorkOrderEntity(
            id = dto.id,
            address = dto.addr.orEmpty(),
            customerName = dto.customerName?.takeIf { it.isNotBlank() }
                ?: dto.nameZh.orEmpty(),
            customerId = dto.customerId ?: 0L,
            jobDate = dto.jobDate.orEmpty(),
            startTime = dto.jobStartTime.orEmpty(),
            endTime = dto.jobEndTime.orEmpty(),
            jobType = dto.jobType?.toInt() ?: JOB_TYPE_UNKNOWN,
            status = statusOverride ?: dto.status ?: STATUS_UNKNOWN,
            serviceType = dto.serviceType?.toInt() ?: 0,
            serviceTypeName = dto.serviceTypeName?.takeIf { it.isNotBlank() } ?: "",
            riskTitle = dto.riskTitle.orEmpty(),
            levelTitle = dto.levelTitle.orEmpty(),
            customerCode = dto.customerCode.orEmpty(),
            contactName = dto.contactName.orEmpty(),
            contactMobile = dto.contactMobile.orEmpty(),
            mobile = dto.mobile.orEmpty(),
            telephone = dto.tel.orEmpty(),
            latitude = dto.lat?.jsonPrimitive?.doubleOrNull ?: 0.0,
            longitude = dto.lng?.jsonPrimitive?.doubleOrNull ?: 0.0,
            remarks = dto.remarks.orEmpty(),
            cachedAtMillis = cachedAtMillis,
            serviceTypeAliasName = dto.serviceTypeAliasName.orEmpty(),
            displayTags = dto.displayTags.map { WorkOrderDisplayTagEntity(it.key, it.text) },
            dataType = dto.dataType.orEmpty(),
            needSignIn = dto.needSignIn == 1,
            jobProgress = dto.jobProgress.toJobProgressEntity()
        )

        private fun JsonElement?.toJobProgressEntity(): WorkOrderProgressEntity {
            val progress = this as? JsonObject
            return WorkOrderProgressEntity(
                signedIn = progress?.flagValue("signed_in") == true,
                customerSigned = progress?.flagValue("customer_signed") == true,
                signedOff = progress?.flagValue("signed_off") == true,
                reportReady = progress?.flagValue("report_ready") == true,
                completed = progress?.flagValue("completed") == true
            )
        }

        private fun JsonObject.flagValue(key: String): Boolean =
            this[key]?.jsonPrimitive?.intOrNull == 1
    }
}

/** 工单五步服务进度，由日工单接口的 job_progress 转换而来。 */
data class WorkOrderProgressEntity(
    val signedIn: Boolean = false,
    val customerSigned: Boolean = false,
    val signedOff: Boolean = false,
    val reportReady: Boolean = false,
    val completed: Boolean = false
)

data class WorkOrderDisplayTagEntity(
    val key: String,
    val text: String
)

/** 日工单分页信息，由 Repository 从接口分页字段转换而来。 */
data class WorkOrderPageEntity(
    val currentPage: Int,
    val totalPage: Int
)

/** 日工单列表和分页信息聚合结果。 */
data class WorkOrderDayOrdersEntity(
    val orders: List<WorkOrderEntity>,
    val paging: Map<String, WorkOrderPageEntity>
)

/** 日历日期工单数量实体。 */
data class WorkOrderDayCountEntity(
    val date: String,
    val count: Int,
    val unfinished: Int,
    val overdue: Int
) {
    val hasUnfinished: Boolean get() = unfinished > 0
    val hasFinished: Boolean get() = count - unfinished > 0
    val hasOverdue: Boolean get() = overdue > 0
}
