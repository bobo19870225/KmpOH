package com.example.kmpoh.data.model.mapper

import com.example.kmpoh.data.model.dto.DayOrderDataDto
import com.example.kmpoh.data.model.dto.DisplayTagDto
import com.example.kmpoh.data.model.entity.WorkOrderDayOrdersEntity
import com.example.kmpoh.data.model.entity.WorkOrderDisplayTagEntity
import com.example.kmpoh.data.model.entity.WorkOrderEntity
import com.example.kmpoh.data.model.entity.WorkOrderPageEntity
import com.example.kmpoh.data.model.entity.WorkOrderProgressEntity
import com.example.kmpoh.page.workorder.WorkOrder
import com.example.kmpoh.page.workorder.WorkOrderProgress
import com.example.kmpoh.page.workorder.WorkOrderStatus
import com.example.kmpoh.page.workorder.WorkOrderTag
import com.example.kmpoh.ui.theme.AppColors
import androidx.compose.ui.graphics.toArgb
import kotlinx.datetime.LocalDate

/** 日工单接口状态类型键（对应服务端 `be_gein`/`in_progress`/`complete`/`all` 取值）。 */
object WorkOrderListKeys {
    const val ALL = "all"
    const val BEGIN = "be_gein"
    const val IN_PROGRESS = "in_progress"
    const val COMPLETE = "complete"
}

/**
 * 日工单 DTO→Entity 聚合（原样迁原工程 `toEntity`：三状态桶覆写状态、空桶回落平铺 list、按 id 去重、
 * 分页字段防御式夹取）。见 spec data/work-order-list「日工单获取与筛选」。
 */
internal fun DayOrderDataDto.toEntity(): WorkOrderDayOrdersEntity {
    val entities = buildList {
        addAll(begin.map { WorkOrderEntity.fromDto(it, WorkOrderEntity.STATUS_WAITING) })
        addAll(inProgress.map { WorkOrderEntity.fromDto(it, WorkOrderEntity.STATUS_RUNNING) })
        addAll(complete.map { WorkOrderEntity.fromDto(it, WorkOrderEntity.STATUS_DONE) })
        if (isEmpty()) {
            addAll(list.map { WorkOrderEntity.fromDto(it) })
        }
    }.distinctBy { it.id }
    return WorkOrderDayOrdersEntity(
        orders = entities,
        paging = mapOf(
            WorkOrderListKeys.BEGIN to WorkOrderPageEntity(
                currentPage = beginCurrentPage.coerceAtLeast(1),
                totalPage = beginPage.coerceAtLeast(0)
            ),
            WorkOrderListKeys.IN_PROGRESS to WorkOrderPageEntity(
                currentPage = inProgressCurrentPage.coerceAtLeast(1),
                totalPage = inProgressPage.coerceAtLeast(0)
            ),
            WorkOrderListKeys.COMPLETE to WorkOrderPageEntity(
                currentPage = completeCurrentPage.coerceAtLeast(1),
                totalPage = completePage.coerceAtLeast(0)
            )
        )
    )
}

/** 状态筛选 → 服务端状态类型（原工程 `toDayOrderType`）。 */
internal fun WorkOrderStatus.toDayOrderType(): String = when (this) {
    WorkOrderStatus.Waiting -> WorkOrderListKeys.BEGIN
    WorkOrderStatus.Running -> WorkOrderListKeys.IN_PROGRESS
    WorkOrderStatus.Done -> WorkOrderListKeys.COMPLETE
}

/** 服务端状态整型 → 页面状态（未知按待开始，对齐原工程）。 */
internal fun Int.toWorkOrderStatus(): WorkOrderStatus = when (this) {
    WorkOrderEntity.STATUS_RUNNING -> WorkOrderStatus.Running
    WorkOrderEntity.STATUS_DONE -> WorkOrderStatus.Done
    else -> WorkOrderStatus.Waiting
}

/**
 * Entity→UIModel（原样迁原工程 `toUiModel`）。`fallbackTitle` 为门店名缺失时的兜底文案
 * （中文常量对齐 NetworkMessages 先例；jobDate 取前 10 位解析，失败回落请求日）。
 */
internal fun WorkOrderEntity.toUiModel(
    requestedDate: LocalDate,
    fallbackTitle: String = "未知客户",
    riskColorOf: (String) -> Int = ::defaultRiskColorArgb
): WorkOrder {
    val date = runCatching { LocalDate.parse(jobDate.take(10)) }.getOrDefault(requestedDate)
    return WorkOrder(
        id = id,
        title = customerName.ifBlank { fallbackTitle },
        date = date,
        timeRange = listOf(startTime, endTime).filter(String::isNotBlank).joinToString("-"),
        address = address,
        status = status.toWorkOrderStatus(),
        tags = displayTags.toWorkOrderTags(riskColorOf),
        riskLabel = riskTitle,
        riskColor = riskColorOf(riskTitle),
        latitude = latitude,
        longitude = longitude,
        serviceTypeAliasName = serviceTypeAliasName,
        levelTitle = levelTitle,
        dataType = dataType.ifBlank { "job_order" },
        phone = contactMobile.takeIf { it.isNotBlank() },
        requiresSignIn = requiresSignIn,
        progress = WorkOrderProgress(
            signedIn = jobProgress.signedIn,
            customerSigned = jobProgress.customerSigned,
            signedOff = jobProgress.signedOff,
            reportReady = jobProgress.reportReady,
            completed = jobProgress.completed
        )
    )
}

/**
 * 展示标签按优先级取首枚（service_type → data_type → customer_level → customer_risk），
 * 风险标签色经 [riskColorOf] 解析、背景取其 12% 透明度（原工程 `toWorkOrderTags`）。
 */
internal fun List<WorkOrderDisplayTagEntity>.toWorkOrderTags(
    riskColorOf: (String) -> Int = ::defaultRiskColorArgb
): List<WorkOrderTag> {
    val styles = mapOf(
        "service_type" to (AppColors.WorkOrderList.ServiceTypeBackground.toArgb() to AppColors.WorkOrderList.ServiceTypeText.toArgb()),
        "data_type" to (AppColors.WorkOrderList.ServiceModeBackground.toArgb() to AppColors.WorkOrderList.ServiceModeText.toArgb()),
        "customer_level" to (AppColors.WorkOrderList.CustomerLevelBackground.toArgb() to AppColors.WorkOrderList.CustomerLevelText.toArgb())
    )
    return listOf("service_type", "data_type", "customer_level", "customer_risk")
        .mapNotNull { key -> firstOrNull { it.key == key && it.text.isNotBlank() } }
        .mapNotNull { tag ->
            if (tag.key == "customer_risk") {
                val color = riskColorOf(tag.text)
                WorkOrderTag(tag.text, color.withAlpha12(), color)
            } else {
                styles[tag.key]?.let { (background, text) -> WorkOrderTag(tag.text, background, text) }
            }
        }
}

/** 风险标签默认色：高/中/低 关键字兜底（原工程 `riskTextColor` 兜底逻辑）。 */
internal fun defaultRiskColorArgb(label: String): Int = when {
    label.contains("高") -> AppColors.WorkOrderList.HighRiskText.toArgb()
    label.contains("中") -> AppColors.WorkOrderList.MediumRiskText.toArgb()
    else -> AppColors.WorkOrderList.LowRiskText.toArgb()
}

/** 服务端颜色串解析（`#RRGGBB`/`#AARRGGBB`，非法返回 null 由调用方忽略——spec「风险标签色配置」）。 */
internal fun parseColorArgb(value: String): Int? {
    val text = value.trim()
    if (!text.startsWith("#")) return null
    val hex = text.substring(1)
    if (hex.length != 6 && hex.length != 8) return null
    if (!hex.all { it.isDigit() || it in 'a'..'f' || it in 'A'..'F' }) return null
    val argb = if (hex.length == 6) "FF$hex" else hex
    return argb.toLongOrNull(16)?.toInt()
}

private fun Int.withAlpha12(): Int = (this and 0x00FFFFFF) or (0x1F shl 24)
