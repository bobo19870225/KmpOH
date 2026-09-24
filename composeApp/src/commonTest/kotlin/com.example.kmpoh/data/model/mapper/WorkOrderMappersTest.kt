package com.example.kmpoh.data.model.mapper

import com.example.kmpoh.data.model.dto.DayOrderDataDto
import com.example.kmpoh.data.model.dto.DisplayTagDto
import com.example.kmpoh.data.model.dto.WorkOrderDto
import com.example.kmpoh.data.model.entity.WorkOrderEntity
import com.example.kmpoh.page.workorder.WorkOrderStatus
import kotlinx.serialization.json.JsonPrimitive
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

class WorkOrderMappersTest {

    private fun dto(
        id: Long = 1L,
        status: Int? = null,
        nameZh: String? = "门店",
        displayTags: List<DisplayTagDto> = emptyList()
    ) = WorkOrderDto(
        id = id,
        status = status,
        nameZh = nameZh,
        jobDate = "2025-01-05 00:00:00",
        jobStartTime = "09:30",
        jobEndTime = "11:00",
        displayTags = displayTags
    )

    @Test
    fun dayOrderDataMergesBucketsWithStatusOverrideAndFallback() {
        val data = DayOrderDataDto(
            begin = listOf(dto(1)),
            inProgress = listOf(dto(2)),
            complete = listOf(dto(3, status = 9)),
            beginPage = 2,
            inProgressCurrentPage = 3,
            completePage = 0
        )
        val entity = data.toEntity()
        assertEquals(listOf(1L, 2L, 3L), entity.orders.map { it.id })
        assertEquals(WorkOrderEntity.STATUS_WAITING, entity.orders[0].status) // be_gein 桶覆写
        assertEquals(WorkOrderEntity.STATUS_RUNNING, entity.orders[1].status)
        assertEquals(WorkOrderEntity.STATUS_DONE, entity.orders[2].status) // complete 桶覆写优先于 dto.status
        // 分页字段防御式夹取
        assertEquals(2, entity.paging.getValue(WorkOrderListKeys.BEGIN).totalPage)
        assertEquals(3, entity.paging.getValue(WorkOrderListKeys.IN_PROGRESS).currentPage)
        assertEquals(0, entity.paging.getValue(WorkOrderListKeys.COMPLETE).totalPage)
    }

    @Test
    fun dayOrderDataFallsBackToFlatListAndDedupes() {
        val data = DayOrderDataDto(list = listOf(dto(1), dto(1), dto(2, status = 2)))
        val entity = data.toEntity()
        assertEquals(listOf(1L, 2L), entity.orders.map { it.id })
        assertEquals(WorkOrderEntity.STATUS_UNKNOWN, entity.orders[0].status) // 无覆写用 dto.status（null→0）
        assertEquals(WorkOrderEntity.STATUS_RUNNING, entity.orders[1].status)
    }

    @Test
    fun statusMapsToDayOrderTypeAndBack() {
        assertEquals(WorkOrderListKeys.BEGIN, WorkOrderStatus.Waiting.toDayOrderType())
        assertEquals(WorkOrderListKeys.IN_PROGRESS, WorkOrderStatus.Running.toDayOrderType())
        assertEquals(WorkOrderListKeys.COMPLETE, WorkOrderStatus.Done.toDayOrderType())
        assertEquals(WorkOrderStatus.Waiting, 1.toWorkOrderStatus())
        assertEquals(WorkOrderStatus.Running, 2.toWorkOrderStatus())
        assertEquals(WorkOrderStatus.Done, 3.toWorkOrderStatus())
        assertEquals(WorkOrderStatus.Waiting, 99.toWorkOrderStatus()) // 未知按待开始
    }

    @Test
    fun entityToUiModelMapsFieldsAndProgress() {
        val entity = WorkOrderEntity.fromDto(
            dto(displayTags = listOf(DisplayTagDto("service_type", "灭虫"))),
            statusOverride = WorkOrderEntity.STATUS_RUNNING
        )
        val model = entity.toUiModel(requestedDate = kotlinx.datetime.LocalDate(2025, 1, 1))
        assertEquals("门店", model.title)
        assertEquals("09:30-11:00", model.timeRange)
        assertEquals(WorkOrderStatus.Running, model.status)
        assertEquals(kotlinx.datetime.LocalDate(2025, 1, 5), model.date) // jobDate 取前 10 位
        assertTrue(model.tags.any { it.label == "灭虫" })
    }

    @Test
    fun parseColorIgnoresIllegalValues() {
        assertEquals(0xFF112233.toInt(), parseColorArgb("#112233"))
        assertEquals(0x80112233.toInt(), parseColorArgb("#80112233"))
        assertEquals(null, parseColorArgb("112233"))
        assertEquals(null, parseColorArgb("#12345"))
        assertEquals(null, parseColorArgb("#GGHHII"))
    }

    @Test
    fun displayTagsSelectByPriorityAndRiskUsesRiskColor() {
        val tags = listOf(
            com.example.kmpoh.data.model.entity.WorkOrderDisplayTagEntity("service_type", "灭虫"),
            com.example.kmpoh.data.model.entity.WorkOrderDisplayTagEntity("data_type", "勘察服务"),
            com.example.kmpoh.data.model.entity.WorkOrderDisplayTagEntity("customer_level", "重点项目"),
            com.example.kmpoh.data.model.entity.WorkOrderDisplayTagEntity("customer_risk", "高风险"),
            com.example.kmpoh.data.model.entity.WorkOrderDisplayTagEntity("service_type", "重复应忽略")
        ).toWorkOrderTags(riskColorOf = { 0xFFEF4444.toInt() })
        assertEquals(listOf("灭虫", "勘察服务", "重点项目", "高风险"), tags.map { it.label })
        assertEquals(0xFFEF4444.toInt(), tags[3].textColor) // 风险标签走 riskColorOf
    }
}
