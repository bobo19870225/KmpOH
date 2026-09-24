package com.example.kmpoh.page.workorder

import com.example.kmpoh.data.model.entity.WorkOrderPageEntity
import com.example.kmpoh.data.repository.DAY_ORDER_PAGE_SIZE
import com.example.kmpoh.data.repository.FIRST_PAGE
import com.example.kmpoh.data.repository.WorkOrderListRepository
import com.example.kmpoh.data.model.mapper.WorkOrderListKeys
import com.example.kmpoh.data.model.mapper.defaultRiskColorArgb
import com.example.kmpoh.data.model.mapper.toDayOrderType
import com.example.kmpoh.data.model.mapper.toUiModel
import com.example.kmpoh.network.BusinessApiException
import com.example.kmpoh.utils.UiState
import com.example.kmpoh.utils.date.atSafeDay
import com.example.kmpoh.utils.date.plusWeeks
import com.example.kmpoh.utils.date.plusMonths
import com.example.kmpoh.utils.date.todayDate
import com.example.kmpoh.utils.date.yearMonthOf
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import kotlinx.datetime.Clock
import kotlinx.datetime.LocalDate
import kotlinx.datetime.YearMonth

/** 一次性提示（类型化文案由 Page 映射多语言，决策 2 同款）。 */
sealed interface WorkOrderListToast {
    data object LoadFailed : WorkOrderListToast
    data class ServerMessage(val message: String) : WorkOrderListToast
}

data class WorkOrderCalendarMarkerState(
    val hasUnfinished: Boolean = false,
    val hasFinished: Boolean = false,
    val hasOverdue: Boolean = false
)

data class WorkOrderListState(
    val selectedDate: LocalDate = todayDate(),
    val displayedMonth: YearMonth = yearMonthOf(todayDate()),
    val expanded: Boolean = false,
    val selectedStatus: WorkOrderStatus = WorkOrderStatus.Waiting,
    val uiState: UiState<List<WorkOrder>> = UiState.Loading,
    val orders: List<WorkOrder> = emptyList(),
    val visibleOrders: List<WorkOrder> = emptyList(),
    val calendarMarkers: Map<LocalDate, WorkOrderCalendarMarkerState> = emptyMap(),
    val monthOrderCount: Int = 0,
    val isRefreshing: Boolean = false,
    val toast: WorkOrderListToast? = null,
    val isLoadingMore: Boolean = false,
    val canLoadMore: Boolean = false,
    val showNoMore: Boolean = false
)

/**
 * 工单列表状态唯一持有者（原样迁原工程 WorkOrderListViewModel 语义；剔除签到流三件套——
 * 随签到变更迁移）。自写纯 Kotlin 状态容器（对齐 LoginViewModel 样板）。
 */
class WorkOrderViewModel(
    private val repository: WorkOrderListRepository,
    private val scope: CoroutineScope
) {
    private val ordersByDate = linkedMapOf<LocalDate, List<WorkOrder>>()
    private val pagingByDate = mutableMapOf<LocalDate, Map<String, WorkOrderPageEntity>>()
    private val loadingDates = mutableSetOf<LocalDate>()
    private val loadingMonths = mutableSetOf<YearMonth>()
    private val _state = MutableStateFlow(WorkOrderListState())
    val state: StateFlow<WorkOrderListState> = _state.asStateFlow()
    private var lastResumeRefreshAtMillis: Long = 0L

    init {
        scope.launch {
            repository.loadRiskColors().onSuccess { publishCachedOrders() }
        }
        loadDate(_state.value.selectedDate)
        loadDayCounts(_state.value.displayedMonth)
        loadUnfinishedDatesForToday()
    }

    fun selectDate(date: LocalDate) {
        val monthChanged = yearMonthOf(date) != _state.value.displayedMonth
        _state.update {
            it.copy(
                selectedDate = date,
                displayedMonth = yearMonthOf(date),
                monthOrderCount = if (monthChanged) 0 else it.monthOrderCount
            )
        }
        // 日期切换必须重新请求，缓存仅用于请求过程展示
        loadDate(date, force = true)
        if (monthChanged) {
            loadDayCounts(yearMonthOf(date), force = true)
        }
    }

    fun shiftMonth(delta: Int) {
        val current = _state.value
        val month = current.displayedMonth.plusMonths(delta)
        selectDate(month.atSafeDay(current.selectedDate.day))
    }

    fun selectMonth(month: YearMonth) = selectDate(month.atSafeDay(1))

    fun selectToday() = selectDate(todayDate())

    fun shiftWeek(delta: Int) = selectDate(_state.value.selectedDate.plusWeeks(delta))

    fun toggleExpanded() = _state.update { it.copy(expanded = !it.expanded) }

    fun selectStatus(status: WorkOrderStatus) {
        _state.update { it.copy(selectedStatus = status) }
        // dayOrder 一次返回三种状态，状态切换只筛选本地单一数据源，避免短时间重复请求
        publishCachedOrders()
    }

    fun retry() = loadDate(_state.value.selectedDate, force = true)

    fun refresh() {
        loadDate(_state.value.selectedDate, force = true, refreshing = true)
        loadDayCounts(_state.value.displayedMonth, force = true)
    }

    fun refreshAfterReturn() {
        val now = Clock.System.now().toEpochMilliseconds()
        if (now - lastResumeRefreshAtMillis < RESUME_REFRESH_INTERVAL_MILLIS) return
        lastResumeRefreshAtMillis = now
        refresh()
    }

    fun loadMore() {
        val current = _state.value
        if (current.isLoadingMore || !current.canLoadMore) return
        val date = current.selectedDate
        val dayOrderType = current.selectedStatus.toDayOrderType()
        val currentPage = pagingByDate[date]?.get(dayOrderType)?.currentPage ?: FIRST_PAGE
        scope.launch {
            _state.update { it.copy(isLoadingMore = true) }
            repository.loadDayOrders(
                jobDate = date.toString(),
                dayOrderType = dayOrderType,
                page = currentPage + 1,
                limit = DAY_ORDER_PAGE_SIZE
            ).fold(
                onSuccess = { result ->
                    val appendedOrders = result.orders.map { entity ->
                        entity.toUiModel(date, riskColorOf = ::riskColorArgb)
                    }
                    ordersByDate[date] = mergeOrders(
                        current = ordersByDate[date].orEmpty(),
                        incoming = appendedOrders
                    )
                    pagingByDate[date] = pagingByDate[date].orEmpty() +
                        result.paging.filterKeys { it == dayOrderType }
                    _state.update { it.copy(isLoadingMore = false) }
                    publishCachedOrders()
                },
                onFailure = { error ->
                    _state.update {
                        it.copy(isLoadingMore = false, toast = error.toToast())
                    }
                }
            )
        }
    }

    fun onToastShown() {
        _state.update { it.copy(toast = null) }
    }

    private fun loadDayCounts(month: YearMonth, force: Boolean = false) {
        if (month in loadingMonths) return
        if (!force && _state.value.calendarMarkers.keys.any { yearMonthOf(it) == month }) return
        loadingMonths.add(month)
        scope.launch {
            try {
                repository.loadDayCounts(month.toString())
                    .onSuccess { counts ->
                        val markers = counts.mapNotNull { item ->
                            val date = runCatching { LocalDate.parse(item.date.take(10)) }.getOrNull()
                                ?: return@mapNotNull null
                            date to WorkOrderCalendarMarkerState(
                                hasUnfinished = item.hasUnfinished,
                                hasFinished = item.hasFinished,
                                hasOverdue = item.hasOverdue
                            )
                        }.toMap()
                        val monthOrderCount = counts.sumOf { item ->
                            val date = runCatching { LocalDate.parse(item.date.take(10)) }.getOrNull()
                            if (date != null && yearMonthOf(date) == month) item.count else 0
                        }
                        _state.update { state ->
                            state.copy(
                                calendarMarkers = state.calendarMarkers
                                    .filterKeys { yearMonthOf(it) != month } + markers,
                                monthOrderCount = if (state.displayedMonth == month) {
                                    monthOrderCount
                                } else {
                                    state.monthOrderCount
                                }
                            )
                        }
                    }
                    .onFailure { error ->
                        _state.update { it.copy(toast = error.toToast()) }
                    }
            } finally {
                loadingMonths.remove(month)
            }
        }
    }

    private fun loadUnfinishedDatesForToday() {
        scope.launch {
            repository.loadUnfinishedJobDates(todayDate().plusWeeks(0).toString().let {
                // 对齐原工程：以「明日」为查询基准取近未完结日期
                todayDate().let { d -> LocalDate.fromEpochDays(d.toEpochDays() + 1) }.toString()
            })
                .onSuccess { dates ->
                    _state.update {
                        it.copy(
                            calendarMarkers = it.calendarMarkers + dates.mapNotNull { value ->
                                runCatching { LocalDate.parse(value.take(10)) }.getOrNull()
                            }.associateWith {
                                WorkOrderCalendarMarkerState(hasUnfinished = true)
                            }
                        )
                    }
                }
                .onFailure { error ->
                    _state.update { it.copy(toast = error.toToast()) }
                }
        }
    }

    private fun loadDate(date: LocalDate, force: Boolean = false, refreshing: Boolean = false) {
        if (date in loadingDates) return
        if (!shouldReload(hasCached = ordersByDate.containsKey(date), force = force)) {
            publishCachedOrders()
            return
        }
        loadingDates.add(date)
        scope.launch {
            try {
                _state.update {
                    it.copy(
                        uiState = if (refreshing) it.uiState else UiState.Loading,
                        isRefreshing = refreshing
                    )
                }
                repository.loadDayOrders(
                    jobDate = date.toString(),
                    dayOrderType = WorkOrderListKeys.ALL,
                    page = FIRST_PAGE,
                    limit = DAY_ORDER_PAGE_SIZE
                ).fold(
                    onSuccess = { result ->
                        ordersByDate[date] = result.orders.map { entity ->
                            entity.toUiModel(date, riskColorOf = ::riskColorArgb)
                        }
                        pagingByDate[date] = result.paging
                        if (result.orders.isNotEmpty()) {
                            _state.update { it.copy(isRefreshing = false) }
                            publishCachedOrders()
                        } else {
                            publishEmpty(date)
                        }
                    },
                    onFailure = { error ->
                        val toast = error.toToast()
                        _state.update {
                            it.copy(
                                uiState = UiState.Error(message = error.toToastText(), throwable = error),
                                orders = emptyList(),
                                visibleOrders = emptyList(),
                                isRefreshing = false,
                                toast = toast
                            )
                        }
                    }
                )
            } finally {
                loadingDates.remove(date)
            }
        }
    }

    private fun publishEmpty(date: LocalDate) {
        pagingByDate.remove(date)
        ordersByDate.remove(date)
        _state.update {
            it.copy(
                uiState = UiState.Empty,
                orders = emptyList(),
                visibleOrders = emptyList(),
                isRefreshing = false
            )
        }
    }

    private fun publishCachedOrders() {
        val current = _state.value
        val orders = ordersByDate.values.flatten()
            .distinctBy { it.id to it.date }
            .sortedBy { it.date }
        val visible = filterVisible(orders, current.selectedDate, current.selectedStatus)
        val paging = pagingByDate[current.selectedDate]?.get(current.selectedStatus.toDayOrderType())
        val (canLoadMore, showNoMore) = loadMoreFlags(visible, paging)
        _state.update {
            it.copy(
                uiState = if (orders.isEmpty()) UiState.Empty else UiState.Success(orders),
                orders = orders,
                visibleOrders = visible,
                canLoadMore = canLoadMore,
                showNoMore = showNoMore
            )
        }
    }

    private fun riskColorArgb(label: String): Int =
        repository.riskColor(label) ?: defaultRiskColorArgb(label)

    private fun Throwable.toToast(): WorkOrderListToast {
        val business = generateSequence(this) { it.cause }
            .filterIsInstance<BusinessApiException>()
            .firstOrNull()
        if (business != null) {
            return business.businessMessage.takeIf { it.isNotBlank() }
                ?.let(WorkOrderListToast::ServerMessage) ?: WorkOrderListToast.LoadFailed
        }
        val message = message?.takeIf { value ->
            value.isNotBlank() && !value.contains("request failed", ignoreCase = true)
        }
        return message?.let(WorkOrderListToast::ServerMessage) ?: WorkOrderListToast.LoadFailed
    }

    private fun Throwable.toToastText(): String = when (val toast = toToast()) {
        is WorkOrderListToast.ServerMessage -> toast.message
        WorkOrderListToast.LoadFailed -> "" // Page 以 LoadFailed 文案呈现
    }

    private companion object {
        const val RESUME_REFRESH_INTERVAL_MILLIS = 1_500L
    }
}
