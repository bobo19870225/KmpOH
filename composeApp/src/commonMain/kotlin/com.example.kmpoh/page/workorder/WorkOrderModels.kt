package com.example.kmpoh.page.workorder

import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.toArgb
import com.example.kmpoh.ui.theme.AppColors
import kotlinx.datetime.LocalDate

/** 工单状态（原样迁原工程页面模型；色值为 ARGB）。 */
enum class WorkOrderStatus(
    val label: String,
    val color: Int,
    val softColor: Int
) {
    Waiting(
        "待开始",
        AppColors.WorkOrderList.Warning.toArgb(),
        AppColors.WorkOrderList.AccentLight.toArgb()
    ),
    Running(
        "进行中",
        AppColors.WorkOrderList.Primary.toArgb(),
        AppColors.WorkOrderList.PrimaryLight.toArgb()
    ),
    Done(
        "已完成",
        AppColors.WorkOrderList.Success.toArgb(),
        AppColors.WorkOrderList.DoneBackground.toArgb()
    )
}

data class WorkOrder(
    val title: String,
    val date: LocalDate,
    val timeRange: String,
    val address: String,
    val status: WorkOrderStatus,
    val tags: List<WorkOrderTag>,
    val riskLabel: String,
    val riskColor: Int,
    val latitude: Double,
    val longitude: Double,
    val id: Long = 0L,
    val levelTitle: String? = null,
    val serviceTypeAliasName: String? = null,
    val dataType: String = "job_order",
    val customerName: String? = null,
    val customerLevel: String? = null,
    val customerLevelTitle: String? = null,
    val phone: String? = null,
    val requiresSignIn: Boolean = false,
    val progress: WorkOrderProgress = WorkOrderProgress()
)

data class WorkOrderTag(
    val label: String,
    val backgroundColor: Int,
    val textColor: Int
)

/** 工单列表展示用的五步服务进度。 */
data class WorkOrderProgress(
    val signedIn: Boolean = false,
    val customerSigned: Boolean = false,
    val signedOff: Boolean = false,
    val reportReady: Boolean = false,
    val completed: Boolean = false
)
