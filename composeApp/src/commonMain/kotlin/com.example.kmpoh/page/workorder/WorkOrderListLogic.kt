package com.example.kmpoh.page.workorder

import com.example.kmpoh.data.model.entity.WorkOrderPageEntity
import kotlinx.datetime.LocalDate

/**
 * 工单列表纯逻辑（design 决策 2/4：缓存合并、可见筛选、分页标志抽离为纯函数便于单测；
 * 语义照搬原工程 `publishCachedOrders`/`mergeOrders`）。
 */

/** 分页追加合并去重（按 id + dataType）。 */
internal fun mergeOrders(current: List<WorkOrder>, incoming: List<WorkOrder>): List<WorkOrder> =
    (current + incoming).distinctBy { it.id to it.dataType }

/** 可见列表 = 选中日期 + 选中状态（dayOrder 一次返回三桶，状态切换只做本地筛选）。 */
internal fun filterVisible(
    orders: List<WorkOrder>,
    date: LocalDate,
    status: WorkOrderStatus
): List<WorkOrder> = orders.filter { it.date == date && it.status == status }

/** 分页标志（canLoadMore → showNoMore）。 */
internal fun loadMoreFlags(
    visible: List<WorkOrder>,
    paging: WorkOrderPageEntity?
): Pair<Boolean, Boolean> {
    val canLoadMore = visible.isNotEmpty() && (paging?.let { it.currentPage < it.totalPage } == true)
    val showNoMore = visible.isNotEmpty() && !canLoadMore
    return canLoadMore to showNoMore
}

/** 缓存命中且非强制时免重载（切回已加载日期直接展示缓存）。 */
internal fun shouldReload(hasCached: Boolean, force: Boolean): Boolean = force || !hasCached
