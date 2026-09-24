package com.example.kmpoh.page.workorder

import com.example.kmpoh.data.model.entity.WorkOrderPageEntity
import kotlinx.datetime.LocalDate
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertTrue

class WorkOrderListLogicTest {

    private val day = LocalDate(2025, 1, 5)

    private fun order(id: Long, date: LocalDate = day, status: WorkOrderStatus = WorkOrderStatus.Waiting, dataType: String = "job_order") =
        WorkOrder(
            title = "t$id", date = date, timeRange = "09:00-10:00", address = "a",
            status = status, tags = emptyList(), riskLabel = "", riskColor = 0,
            latitude = 0.0, longitude = 0.0, id = id, dataType = dataType
        )

    @Test
    fun mergeOrdersAppendsAndDedupesByIdAndDataType() {
        val merged = mergeOrders(
            current = listOf(order(1), order(2)),
            incoming = listOf(order(2), order(2, dataType = "follow"), order(3))
        )
        assertEquals(listOf(1L, 2L, 2L, 3L), merged.map { it.id })
        assertEquals(listOf("job_order", "job_order", "follow", "job_order"), merged.map { it.dataType })
    }

    @Test
    fun filterVisibleByDateAndStatus() {
        val orders = listOf(
            order(1, status = WorkOrderStatus.Waiting),
            order(2, status = WorkOrderStatus.Running),
            order(3, date = LocalDate(2025, 1, 6), status = WorkOrderStatus.Waiting)
        )
        assertEquals(listOf(1L), filterVisible(orders, day, WorkOrderStatus.Waiting).map { it.id })
        assertEquals(listOf(2L), filterVisible(orders, day, WorkOrderStatus.Running).map { it.id })
        assertTrue(filterVisible(orders, day, WorkOrderStatus.Done).isEmpty())
    }

    @Test
    fun loadMoreFlagsFollowPaging() {
        assertEquals(true to false, loadMoreFlags(listOf(order(1)), WorkOrderPageEntity(currentPage = 1, totalPage = 3)))
        assertEquals(false to true, loadMoreFlags(listOf(order(1)), WorkOrderPageEntity(currentPage = 3, totalPage = 3)))
        assertEquals(false to false, loadMoreFlags(emptyList(), WorkOrderPageEntity(currentPage = 1, totalPage = 3)))
        // 无分页信息 = 无更多（原工程语义，spec「没有更多提示」）
        assertEquals(false to true, loadMoreFlags(listOf(order(1)), null))
    }

    @Test
    fun reloadOnlyWhenForcedOrNotCached() {
        assertFalse(shouldReload(hasCached = true, force = false)) // 缓存命中切回免重载
        assertTrue(shouldReload(hasCached = true, force = true)) // 日期切换/刷新强制
        assertTrue(shouldReload(hasCached = false, force = false))
    }
}
