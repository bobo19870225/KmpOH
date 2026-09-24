package com.example.kmpoh.page.workorder

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.gestures.detectDragGestures
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.ExperimentalLayoutApi
import androidx.compose.foundation.layout.FlowRow
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.offset
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.material3.pulltorefresh.PullToRefreshBox
import androidx.compose.material3.pulltorefresh.rememberPullToRefreshState
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableFloatStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.toArgb
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.window.Dialog
import com.example.kmpoh.data.repository.createWorkOrderListRepository
import com.example.kmpoh.ui.components.LoadingView
import com.example.kmpoh.ui.theme.AppColors
import com.example.kmpoh.utils.UiState
import com.example.kmpoh.utils.date.atSafeDay
import com.example.kmpoh.utils.date.plusWeeks
import com.example.kmpoh.utils.date.startOfWeek
import com.example.kmpoh.utils.date.toMonthTitle
import com.example.kmpoh.utils.date.todayDate
import com.example.kmpoh.utils.date.yearMonthOf
import kotlin.math.abs
import kotlinx.coroutines.launch
import kotlinx.datetime.LocalDate
import kotlinx.datetime.YearMonth
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.preview
import kmpoh.composeapp.generated.resources.str_cancel
import kmpoh.composeapp.generated.resources.str_retry
import kmpoh.composeapp.generated.resources.work_order_back_to_today
import kmpoh.composeapp.generated.resources.work_order_collapse
import kmpoh.composeapp.generated.resources.work_order_empty
import kmpoh.composeapp.generated.resources.work_order_expand_month
import kotlinx.datetime.number
import kmpoh.composeapp.generated.resources.work_order_load_failed
import kmpoh.composeapp.generated.resources.work_order_load_more
import kmpoh.composeapp.generated.resources.work_order_loading_more
import kmpoh.composeapp.generated.resources.work_order_map_open_failed
import kmpoh.composeapp.generated.resources.work_order_month_count
import kmpoh.composeapp.generated.resources.work_order_month_format
import kmpoh.composeapp.generated.resources.work_order_next_month_desc
import kmpoh.composeapp.generated.resources.work_order_no_more
import kmpoh.composeapp.generated.resources.work_order_prev_month_desc
import kmpoh.composeapp.generated.resources.work_order_progress_complete
import kmpoh.composeapp.generated.resources.work_order_progress_customer_sign
import kmpoh.composeapp.generated.resources.work_order_progress_report
import kmpoh.composeapp.generated.resources.work_order_progress_sign_in
import kmpoh.composeapp.generated.resources.work_order_progress_sign_off
import kmpoh.composeapp.generated.resources.work_order_service_time
import kmpoh.composeapp.generated.resources.work_order_year_format
import kmpoh.composeapp.generated.resources.ic_wo_arrow_back_ios_new
import kmpoh.composeapp.generated.resources.ic_wo_arrow_forward_ios
import kmpoh.composeapp.generated.resources.ic_wo_calendar_month
import kmpoh.composeapp.generated.resources.ic_wo_check_circle
import kmpoh.composeapp.generated.resources.ic_wo_close
import kmpoh.composeapp.generated.resources.ic_wo_error_outline
import kmpoh.composeapp.generated.resources.ic_wo_expand_less
import kmpoh.composeapp.generated.resources.ic_wo_expand_more
import kmpoh.composeapp.generated.resources.ic_wo_inventory2
import kmpoh.composeapp.generated.resources.ic_wo_location_on
import kmpoh.composeapp.generated.resources.ic_wo_north_east
import kmpoh.composeapp.generated.resources.ic_wo_radio_unchecked
import kmpoh.composeapp.generated.resources.ic_wo_schedule
import kmpoh.composeapp.generated.resources.ic_login_visibility
import org.jetbrains.compose.resources.painterResource
import org.jetbrains.compose.resources.stringResource

// 页面视觉 token（命名化，避免内联色值；原工程内联色照搬）
private val WoPrimary = Color(0xFF1D6F86)
private val WoPageBg = Color(0xFFF4F6FA)
private val WoCalendarBg = Color(0xFFEFF3F7)
private val WoTextPrimary = Color(0xFF20242E)
private val WoTextSub = Color(0xFF7B8494)
private val WoTextMuted = Color(0xFFA6AFBD)
private val WoIconTint = Color(0xFF8A96A8)
private val WoCircleBg = Color(0xFFEEF3F7)
private val WoMutedDay = Color(0x7720242E)

/**
 * 工单列表页（spec ui/work-order-list；原样迁原工程 WorkOrderComposeScreen 列表链路，
 * 签到流/地图导航/NFC 属未迁域）。点击接缝（design 决策 5）：[onOpenPreview] 统一上报
 * 预览/详情/签到入口点击，本期无跳转；[onToastMessage] 承接提示。
 */
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun WorkOrderPage(
    modifier: Modifier = Modifier,
    onOpenPreview: (WorkOrder) -> Unit = {},
    onToastMessage: (String) -> Unit = {}
) {
    val scope = rememberCoroutineScope()
    val viewModel = remember { WorkOrderViewModel(createWorkOrderListRepository(), scope) }
    val state by viewModel.state.collectAsState()
    val today = remember { todayDate() }
    var showMonthPicker by remember { mutableStateOf(false) }

    // 一次性提示：类型化 toast → 文案后转发（对齐修改密码页接缝）
    val toastText = state.toast?.let { toast ->
        when (toast) {
            WorkOrderListToast.LoadFailed -> stringResource(Res.string.work_order_load_failed)
            is WorkOrderListToast.ServerMessage -> toast.message
        }
    }
    LaunchedEffect(state.toast) {
        toastText?.let { text ->
            onToastMessage(text)
            viewModel.onToastShown()
        }
    }

    // 回前台自动刷新（spec「刷新」；跳过首帧 ON_RESUME，决策 7）
    var hasObservedInitialResume by remember { mutableStateOf(false) }
    LifecycleResumeEffect {
        if (hasObservedInitialResume) viewModel.refreshAfterReturn() else hasObservedInitialResume = true
    }

    val pullToRefreshState = rememberPullToRefreshState()
    PullToRefreshBox(
        isRefreshing = state.isRefreshing,
        onRefresh = viewModel::refresh,
        modifier = modifier.fillMaxSize(),
        state = pullToRefreshState
    ) {
        LazyColumn(
            modifier = Modifier.fillMaxSize().background(WoPageBg)
        ) {
            item {
                Column(
                    Modifier.fillMaxWidth().padding(start = 16.dp, top = 24.dp, end = 16.dp)
                ) {
                    WorkOrderTopBar(
                        displayedMonth = state.displayedMonth,
                        monthCount = state.monthOrderCount,
                        onPrevious = { viewModel.shiftMonth(-1) },
                        onNext = { viewModel.shiftMonth(1) },
                        onTitle = { showMonthPicker = true }
                    )
                    WorkOrderCalendar(
                        calendarMarkers = state.calendarMarkers,
                        selectedDate = state.selectedDate,
                        displayedMonth = state.displayedMonth,
                        expanded = state.expanded,
                        onDateSelected = viewModel::selectDate,
                        onSwipe = { direction ->
                            if (state.expanded) viewModel.shiftMonth(direction) else viewModel.shiftWeek(direction)
                        }
                    )
                    Row(
                        modifier = Modifier
                            .fillMaxWidth()
                            .height(38.dp)
                            .clickable(onClick = viewModel::toggleExpanded),
                        horizontalArrangement = Arrangement.Center,
                        verticalAlignment = Alignment.CenterVertically
                    ) {
                        Text(
                            if (state.expanded) stringResource(Res.string.work_order_collapse)
                            else stringResource(Res.string.work_order_expand_month),
                            color = WoPrimary,
                            fontSize = 14.sp,
                            fontWeight = FontWeight.Bold
                        )
                        Icon(
                            painter = painterResource(
                                if (state.expanded) Res.drawable.ic_wo_expand_less else Res.drawable.ic_wo_expand_more
                            ),
                            contentDescription = null,
                            tint = WoPrimary
                        )
                    }
                    StatusTabs(
                        selectedDate = state.selectedDate,
                        orders = state.orders,
                        selectedStatus = state.selectedStatus,
                        onSelected = viewModel::selectStatus
                    )
                }
            }
            when (val uiState = state.uiState) {
                is UiState.Error -> item {
                    WorkOrderErrorState(
                        message = uiState.message.ifBlank { stringResource(Res.string.work_order_load_failed) },
                        onRetry = viewModel::retry
                    )
                }

                UiState.Empty, UiState.NoPermission, UiState.Idle -> item { EmptyOrderState() }
                else -> {
                    if (state.visibleOrders.isEmpty()) {
                        item { EmptyOrderState() }
                    } else {
                        items(
                            items = state.visibleOrders,
                            key = { order -> "${order.dataType}_${order.id}_${order.status}" }
                        ) { order ->
                            val mapFailedText = stringResource(Res.string.work_order_map_open_failed)
                            OrderCard(
                                order = order,
                                modifier = Modifier
                                    .fillMaxWidth()
                                    .padding(start = 16.dp, end = 16.dp, bottom = 10.dp),
                                onCardClick = { onOpenPreview(order) },
                                onPreviewClick = { onOpenPreview(order) },
                                onRouteClick = { onToastMessage(mapFailedText) }
                            )
                        }
                        item(key = "work_order_load_more_${state.selectedDate}_${state.selectedStatus}") {
                            WorkOrderLoadMoreFooter(
                                isLoadingMore = state.isLoadingMore,
                                canLoadMore = state.canLoadMore,
                                showNoMore = state.showNoMore,
                                autoLoadKey = "${state.selectedDate}_${state.selectedStatus}_${state.visibleOrders.size}",
                                onLoadMore = viewModel::loadMore
                            )
                        }
                    }
                }
            }
        }
    }

    if (showMonthPicker) {
        MonthPickerDialog(
            displayedMonth = state.displayedMonth,
            today = today,
            onDismiss = { showMonthPicker = false },
            onMonthSelected = {
                viewModel.selectMonth(it)
                showMonthPicker = false
            },
            onToday = {
                viewModel.selectToday()
                showMonthPicker = false
            }
        )
    }
}

/** 回前台生命周期观察（决策 7；跳过首帧由调用方状态控制）。 */
@Composable
private fun LifecycleResumeEffect(onResume: () -> Unit) {
    val lifecycleOwner = androidx.compose.ui.platform.LocalLifecycleOwner.current
    DisposableEffect(lifecycleOwner) {
        val observer = androidx.lifecycle.LifecycleEventObserver { _, event ->
            if (event == androidx.lifecycle.Lifecycle.Event.ON_RESUME) onResume()
        }
        lifecycleOwner.lifecycle.addObserver(observer)
        onDispose { lifecycleOwner.lifecycle.removeObserver(observer) }
    }
}

@Composable
private fun WorkOrderTopBar(
    displayedMonth: YearMonth,
    monthCount: Int,
    onPrevious: () -> Unit,
    onNext: () -> Unit,
    onTitle: () -> Unit
) {
    Row(Modifier.fillMaxWidth().height(64.dp), verticalAlignment = Alignment.CenterVertically) {
        CircleIconButton(onClick = onPrevious) {
            Icon(
                painter = painterResource(Res.drawable.ic_wo_arrow_back_ios_new),
                contentDescription = stringResource(Res.string.work_order_prev_month_desc),
                tint = WoIconTint,
                modifier = Modifier.size(17.dp)
            )
        }
        Column(
            Modifier.weight(1f).clickable(onClick = onTitle),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Row(verticalAlignment = Alignment.CenterVertically) {
                Text(
                    displayedMonth.atSafeDay(1).toMonthTitle(),
                    color = WoTextPrimary,
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Bold
                )
                Icon(
                    painter = painterResource(Res.drawable.ic_wo_expand_more),
                    contentDescription = null,
                    tint = Color(0xFFA1AAB8),
                    modifier = Modifier.size(20.dp)
                )
            }
            Text(
                stringResource(Res.string.work_order_month_count, monthCount),
                color = WoTextSub,
                fontSize = 12.sp
            )
        }
        CircleIconButton(onClick = onNext) {
            Icon(
                painter = painterResource(Res.drawable.ic_wo_arrow_forward_ios),
                contentDescription = stringResource(Res.string.work_order_next_month_desc),
                tint = WoIconTint,
                modifier = Modifier.size(17.dp)
            )
        }
    }
}

@Composable
private fun CircleIconButton(onClick: () -> Unit, content: @Composable () -> Unit) {
    Box(
        Modifier
            .size(38.dp)
            .clip(CircleShape)
            .background(WoCircleBg)
            .clickable(onClick = onClick),
        contentAlignment = Alignment.Center
    ) { content() }
}

@Composable
private fun WorkOrderCalendar(
    calendarMarkers: Map<LocalDate, WorkOrderCalendarMarkerState>,
    selectedDate: LocalDate,
    displayedMonth: YearMonth,
    expanded: Boolean,
    onDateSelected: (LocalDate) -> Unit,
    onSwipe: (Int) -> Unit
) {
    var dragOffset by remember { mutableFloatStateOf(0f) }
    val dates = remember(selectedDate, displayedMonth, expanded) {
        if (expanded) {
            val first = displayedMonth.atSafeDay(1)
            val start = first.startOfWeek()
            List(42) { LocalDate.fromEpochDays(start.toEpochDays() + it) }
        } else {
            val start = selectedDate.startOfWeek()
            List(7) { LocalDate.fromEpochDays(start.toEpochDays() + it) }
        }
    }
    Column(
        Modifier
            .fillMaxWidth()
            .then(
                if (expanded) Modifier else Modifier
                    .clip(RoundedCornerShape(14.dp))
                    .background(WoCalendarBg)
            )
            .pointerInput(expanded, selectedDate, displayedMonth) {
                detectDragGestures(
                    onDrag = { change, dragAmount ->
                        change.consume()
                        dragOffset += dragAmount.x
                    },
                    onDragEnd = {
                        if (abs(dragOffset) > 70f) onSwipe(if (dragOffset < 0) 1 else -1)
                        dragOffset = 0f
                    },
                    onDragCancel = { dragOffset = 0f }
                )
            }
            .padding(bottom = if (expanded) 0.dp else 8.dp)
    ) {
        val weekLabels = listOf("一", "二", "三", "四", "五", "六", "日")
        if (expanded) {
            Row(Modifier.fillMaxWidth()) {
                weekLabels.forEach {
                    Text(
                        it,
                        modifier = Modifier.weight(1f),
                        textAlign = TextAlign.Center,
                        color = WoTextMuted,
                        fontSize = 13.sp,
                        fontWeight = FontWeight.Bold
                    )
                }
            }
            dates.chunked(7).forEach { week ->
                Row(Modifier.fillMaxWidth()) {
                    week.forEach { date ->
                        CalendarDay(
                            modifier = Modifier.weight(1f),
                            date = date,
                            selected = date == selectedDate,
                            muted = yearMonthOf(date) != displayedMonth,
                            markers = date.markers(calendarMarkers),
                            onClick = { onDateSelected(date) }
                        )
                    }
                }
            }
        } else {
            Row(Modifier.fillMaxWidth().padding(horizontal = 6.dp, vertical = 8.dp)) {
                dates.forEachIndexed { index, date ->
                    CollapsedCalendarDay(
                        modifier = Modifier.weight(1f),
                        weekLabel = weekLabels[index],
                        date = date,
                        selected = date == selectedDate,
                        markers = date.markers(calendarMarkers),
                        onClick = { onDateSelected(date) }
                    )
                }
            }
        }
    }
}

private enum class CalendarDateMarker(val color: Int) {
    Unfinished(AppColors.WorkOrderList.Warning.toArgb()),
    Overdue(AppColors.WorkOrderList.Danger.toArgb()),
    Completed(AppColors.WorkOrderList.Success.toArgb())
}

private fun LocalDate.markers(
    calendarMarkers: Map<LocalDate, WorkOrderCalendarMarkerState>
): List<CalendarDateMarker> {
    val marker = calendarMarkers[this] ?: return emptyList()
    return buildList {
        if (marker.hasOverdue) {
            add(CalendarDateMarker.Overdue)
        } else if (marker.hasUnfinished) {
            add(CalendarDateMarker.Unfinished)
        }
        if (marker.hasFinished) {
            add(CalendarDateMarker.Completed)
        }
    }.take(2)
}

@Composable
private fun CollapsedCalendarDay(
    modifier: Modifier,
    weekLabel: String,
    date: LocalDate,
    selected: Boolean,
    markers: List<CalendarDateMarker>,
    onClick: () -> Unit
) {
    Box(modifier.height(66.dp).clickable(onClick = onClick), contentAlignment = Alignment.Center) {
        Column(
            Modifier
                .size(width = 52.dp, height = 62.dp)
                .clip(RoundedCornerShape(12.dp))
                .background(if (selected) WoPrimary else Color.Transparent),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Text(
                weekLabel,
                color = if (selected) Color.White else WoTextMuted,
                fontSize = 13.sp,
                fontWeight = FontWeight.Bold
            )
            Text(
                date.day.toString(),
                color = if (selected) Color.White else WoTextPrimary,
                fontSize = 17.sp,
                fontWeight = if (selected) FontWeight.Bold else FontWeight.Normal
            )
            MarkerDots(markers, selected)
        }
    }
}

@Composable
private fun CalendarDay(
    modifier: Modifier,
    date: LocalDate,
    selected: Boolean,
    muted: Boolean,
    markers: List<CalendarDateMarker>,
    onClick: () -> Unit
) {
    Box(modifier.height(46.dp).clickable(onClick = onClick), contentAlignment = Alignment.Center) {
        Column(
            Modifier
                .size(width = 44.dp, height = 44.dp)
                .clip(RoundedCornerShape(10.dp))
                .background(if (selected) WoPrimary else Color.Transparent),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Text(
                date.day.toString(),
                color = when {
                    selected -> Color.White
                    muted -> WoMutedDay
                    else -> WoTextPrimary
                },
                fontSize = 16.sp,
                fontWeight = if (selected) FontWeight.Bold else FontWeight.Normal
            )
            MarkerDots(markers, selected)
        }
    }
}

@Composable
private fun MarkerDots(markers: List<CalendarDateMarker>, selected: Boolean) {
    Row(horizontalArrangement = Arrangement.spacedBy(4.dp), modifier = Modifier.height(7.dp)) {
        markers.forEach {
            Box(
                Modifier
                    .size(4.5.dp)
                    .clip(CircleShape)
                    .background(if (selected) Color.White else Color(it.color))
            )
        }
    }
}

@Composable
private fun StatusTabs(
    selectedDate: LocalDate,
    orders: List<WorkOrder>,
    selectedStatus: WorkOrderStatus,
    onSelected: (WorkOrderStatus) -> Unit
) {
    Row(Modifier.fillMaxWidth().height(50.dp)) {
        WorkOrderStatus.entries.forEach { status ->
            val active = status == selectedStatus
            val count = orders.count { it.date == selectedDate && it.status == status }
            Column(
                modifier = Modifier
                    .weight(1f)
                    .fillMaxHeight()
                    .clickable { onSelected(status) },
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalArrangement = Arrangement.Center
            ) {
                Text(
                    "${status.label}  $count",
                    color = if (active) Color(status.color) else Color(0xFF7D8494),
                    fontSize = 15.sp,
                    fontWeight = if (active) FontWeight.Bold else FontWeight.Normal
                )
                Spacer(
                    Modifier
                        .padding(top = 8.dp)
                        .height(2.dp)
                        .fillMaxWidth(0.92f)
                        .background(if (active) Color(status.color) else Color.Transparent)
                )
            }
        }
    }
}

@Composable
private fun OrderCard(
    order: WorkOrder,
    modifier: Modifier = Modifier,
    onCardClick: () -> Unit,
    onPreviewClick: () -> Unit,
    onRouteClick: () -> Unit
) {
    Column(
        modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(14.dp))
            .background(AppColors.WorkOrderList.Card)
            .padding(14.dp)
            .clickable(onClick = onCardClick)
    ) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Text(
                order.title,
                modifier = Modifier.weight(1f).clickable(onClick = onCardClick),
                color = AppColors.WorkOrderList.TextPrimary,
                fontSize = 14.sp,
                fontWeight = FontWeight.Bold
            )
            if (order.status == WorkOrderStatus.Waiting) {
                Chip(
                    icon = {
                        Icon(
                            painter = painterResource(Res.drawable.ic_login_visibility),
                            contentDescription = null,
                            tint = AppColors.WorkOrderList.Primary,
                            modifier = Modifier.size(15.dp)
                        )
                    },
                    label = stringResource(Res.string.preview),
                    bg = AppColors.WorkOrderList.PreviewBackground,
                    fg = AppColors.WorkOrderList.Primary,
                    onClick = onPreviewClick
                )
                Spacer(Modifier.width(6.dp))
            }
            Chip(
                label = order.status.label,
                bg = Color(order.status.softColor),
                fg = Color(order.status.color)
            )
        }
        Row(Modifier.padding(top = 11.dp, bottom = 10.dp), horizontalArrangement = Arrangement.spacedBy(6.dp)) {
            order.tags.forEach { tag ->
                Chip(
                    label = tag.label,
                    bg = Color(tag.backgroundColor),
                    fg = Color(tag.textColor),
                    onClick = onCardClick
                )
            }
        }
        WorkOrderProgressRow(progress = order.progress)
        Spacer(Modifier.fillMaxWidth().height(1.dp).background(AppColors.WorkOrderList.Divider))
        if (order.timeRange.isNotBlank()) {
            InfoRow(modifier = Modifier.clickable(onClick = onCardClick), icon = {
                Icon(
                    painter = painterResource(Res.drawable.ic_wo_schedule),
                    contentDescription = null,
                    tint = AppColors.WorkOrderList.TextTertiary,
                    modifier = Modifier.size(16.dp)
                )
            }, text = stringResource(Res.string.work_order_service_time, order.timeRange))
        }
        if (order.address.isNotBlank()) {
            AddressRow(address = order.address, onRouteClick = onRouteClick)
        }
    }
}

@OptIn(ExperimentalLayoutApi::class)
@Composable
private fun WorkOrderProgressRow(progress: WorkOrderProgress) {
    FlowRow(
        modifier = Modifier.fillMaxWidth().padding(bottom = 10.dp),
        horizontalArrangement = Arrangement.spacedBy(6.dp),
        verticalArrangement = Arrangement.spacedBy(6.dp)
    ) {
        WorkOrderProgressItem(stringResource(Res.string.work_order_progress_sign_in), progress.signedIn)
        WorkOrderProgressItem(stringResource(Res.string.work_order_progress_customer_sign), progress.customerSigned)
        WorkOrderProgressItem(stringResource(Res.string.work_order_progress_sign_off), progress.signedOff)
        WorkOrderProgressItem(stringResource(Res.string.work_order_progress_report), progress.reportReady)
        WorkOrderProgressItem(stringResource(Res.string.work_order_progress_complete), progress.completed)
    }
}

@Composable
private fun WorkOrderProgressItem(label: String, completed: Boolean, modifier: Modifier = Modifier) {
    val foregroundColor = if (completed) AppColors.WorkOrderList.DoneText else AppColors.TextDisabled
    val backgroundColor = if (completed) AppColors.WorkOrderList.DoneBackground else AppColors.DisabledBackground
    Row(
        modifier = modifier
            .clip(RoundedCornerShape(14.dp))
            .background(backgroundColor)
            .padding(horizontal = 6.dp, vertical = 4.dp),
        horizontalArrangement = Arrangement.Center,
        verticalAlignment = Alignment.CenterVertically
    ) {
        Icon(
            painter = painterResource(
                if (completed) Res.drawable.ic_wo_check_circle else Res.drawable.ic_wo_radio_unchecked
            ),
            contentDescription = null,
            tint = foregroundColor,
            modifier = Modifier.size(14.dp)
        )
        Spacer(Modifier.width(3.dp))
        Text(
            text = label,
            color = foregroundColor,
            fontSize = 10.sp,
            fontWeight = FontWeight.Medium,
            maxLines = 1
        )
    }
}

@Composable
private fun Chip(
    label: String,
    bg: Color,
    fg: Color,
    icon: (@Composable () -> Unit)? = null,
    onClick: (() -> Unit)? = null
) {
    val clickModifier = if (onClick != null) Modifier.clickable(onClick = onClick) else Modifier
    Row(
        Modifier
            .clip(RoundedCornerShape(14.dp))
            .background(bg)
            .then(clickModifier)
            .padding(horizontal = 8.dp, vertical = 4.dp),
        verticalAlignment = Alignment.CenterVertically
    ) {
        if (icon != null) {
            icon()
            Spacer(Modifier.width(3.dp))
        }
        Text(label, color = fg, fontSize = 12.sp, fontWeight = FontWeight.Bold)
    }
}

@Composable
private fun InfoRow(modifier: Modifier = Modifier, icon: @Composable () -> Unit, text: String) {
    Row(modifier.padding(top = 7.dp), verticalAlignment = Alignment.CenterVertically) {
        icon()
        Spacer(Modifier.width(6.dp))
        Text(text, color = AppColors.WorkOrderList.TextSecondary, fontSize = 14.sp)
    }
}

@Composable
private fun AddressRow(address: String, onRouteClick: () -> Unit) {
    Row(Modifier.padding(top = 4.dp), verticalAlignment = Alignment.CenterVertically) {
        Icon(
            painter = painterResource(Res.drawable.ic_wo_location_on),
            contentDescription = null,
            tint = AppColors.WorkOrderList.Primary,
            modifier = Modifier.size(16.dp)
        )
        Spacer(Modifier.width(6.dp))
        Text(
            address,
            modifier = Modifier.weight(1f),
            color = AppColors.WorkOrderList.TextPrimary,
            fontSize = 14.sp
        )
        Box(
            modifier = Modifier
                .size(28.dp)
                .clip(CircleShape)
                .background(AppColors.WorkOrderList.RouteIconBackground)
                .clickable(onClick = onRouteClick),
            contentAlignment = Alignment.Center
        ) {
            Icon(
                painter = painterResource(Res.drawable.ic_wo_north_east),
                contentDescription = null,
                tint = Color.White,
                modifier = Modifier.size(14.dp)
            )
        }
    }
}

@Composable
private fun WorkOrderLoadMoreFooter(
    isLoadingMore: Boolean,
    canLoadMore: Boolean,
    showNoMore: Boolean,
    autoLoadKey: String,
    onLoadMore: () -> Unit
) {
    LaunchedEffect(autoLoadKey, canLoadMore) {
        if (canLoadMore && !isLoadingMore) onLoadMore()
    }
    Box(
        modifier = Modifier.fillMaxWidth().padding(top = 4.dp, bottom = 8.dp),
        contentAlignment = Alignment.Center
    ) {
        when {
            canLoadMore || isLoadingMore -> {
                Button(
                    onClick = onLoadMore,
                    enabled = canLoadMore && !isLoadingMore,
                    colors = ButtonDefaults.buttonColors(
                        containerColor = WoCircleBg,
                        disabledContainerColor = WoCircleBg
                    )
                ) {
                    if (isLoadingMore) {
                        CircularProgressIndicator(
                            modifier = Modifier.padding(end = 8.dp).size(16.dp),
                            color = WoPrimary,
                            strokeWidth = 2.dp
                        )
                    }
                    Text(
                        text = stringResource(
                            if (isLoadingMore) Res.string.work_order_loading_more
                            else Res.string.work_order_load_more
                        ),
                        color = WoPrimary,
                        fontSize = 12.sp,
                        fontWeight = FontWeight.Bold
                    )
                }
            }

            showNoMore -> {
                Text(
                    text = stringResource(Res.string.work_order_no_more),
                    color = Color(0xFF8A96A8),
                    fontSize = 12.sp,
                    modifier = Modifier.padding(vertical = 10.dp)
                )
            }
        }
    }
}

@Composable
private fun EmptyOrderState(modifier: Modifier = Modifier) {
    Box(modifier.fillMaxWidth().height(260.dp), contentAlignment = Alignment.Center) {
        Column(horizontalAlignment = Alignment.CenterHorizontally) {
            Icon(
                painter = painterResource(Res.drawable.ic_wo_inventory2),
                contentDescription = null,
                tint = WoTextMuted,
                modifier = Modifier.size(42.dp)
            )
            Text(
                stringResource(Res.string.work_order_empty),
                modifier = Modifier.padding(top = 12.dp),
                color = Color(0xFF7D8494),
                fontSize = 16.sp,
                fontWeight = FontWeight.Bold
            )
        }
    }
}

@Composable
private fun WorkOrderErrorState(message: String, onRetry: () -> Unit) {
    Column(
        modifier = Modifier.fillMaxWidth().height(260.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Icon(
            painter = painterResource(Res.drawable.ic_wo_error_outline),
            contentDescription = null,
            tint = WoTextMuted,
            modifier = Modifier.size(42.dp)
        )
        Text(
            text = message,
            modifier = Modifier.padding(top = 12.dp),
            color = Color(0xFF7D8494),
            fontSize = 14.sp
        )
        Button(
            onClick = onRetry,
            modifier = Modifier.padding(top = 12.dp),
            colors = ButtonDefaults.buttonColors(containerColor = WoPrimary)
        ) {
            Text(text = stringResource(Res.string.str_retry))
        }
    }
}

@Composable
private fun MonthPickerDialog(
    displayedMonth: YearMonth,
    today: LocalDate,
    onDismiss: () -> Unit,
    onMonthSelected: (YearMonth) -> Unit,
    onToday: () -> Unit
) {
    var pickerYear by remember { mutableStateOf(displayedMonth.year) }
    Dialog(onDismissRequest = onDismiss) {
        Column(
            Modifier
                .fillMaxWidth()
                .clip(RoundedCornerShape(22.dp))
                .background(Color.White)
                .padding(22.dp),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Row(verticalAlignment = Alignment.CenterVertically) {
                CircleArrow("‹") { pickerYear-- }
                Text(
                    stringResource(Res.string.work_order_year_format, pickerYear),
                    modifier = Modifier.weight(1f),
                    textAlign = TextAlign.Center,
                    color = WoTextPrimary,
                    fontSize = 24.sp,
                    fontWeight = FontWeight.Bold
                )
                CircleArrow("›") { pickerYear++ }
            }
            Column(Modifier.padding(top = 18.dp)) {
                (1..12).chunked(4).forEach { rowMonths ->
                    Row(Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.spacedBy(10.dp)) {
                        rowMonths.forEach { month ->
                            val active = pickerYear == displayedMonth.year && month == displayedMonth.month.number
                            Box(
                                Modifier
                                    .weight(1f)
                                    .height(50.dp)
                                    .clip(RoundedCornerShape(10.dp))
                                    .background(if (active) WoPrimary else Color(0xFFF0F4F8))
                                    .clickable { onMonthSelected(YearMonth(pickerYear, month)) },
                                contentAlignment = Alignment.Center
                            ) {
                                Column(horizontalAlignment = Alignment.CenterHorizontally) {
                                    Text(
                                        stringResource(Res.string.work_order_month_format, month),
                                        color = if (active) Color.White else WoTextPrimary,
                                        fontSize = 16.sp,
                                        fontWeight = FontWeight.Bold
                                    )
                                    if (YearMonth(pickerYear, month) == yearMonthOf(today)) {
                                        Box(
                                            Modifier
                                                .size(5.dp)
                                                .clip(CircleShape)
                                                .background(if (active) Color.White else WoPrimary)
                                        )
                                    }
                                }
                            }
                        }
                    }
                    Spacer(Modifier.height(10.dp))
                }
            }
            Row(Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.spacedBy(10.dp)) {
                Button(
                    onClick = onToday,
                    modifier = Modifier.weight(1f).height(48.dp),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = Color(0xFFEAF1F4),
                        contentColor = WoPrimary
                    ),
                    shape = RoundedCornerShape(14.dp)
                ) {
                    Icon(
                        painter = painterResource(Res.drawable.ic_wo_calendar_month),
                        contentDescription = null,
                        modifier = Modifier.size(17.dp)
                    )
                    Spacer(Modifier.width(6.dp))
                    Text(stringResource(Res.string.work_order_back_to_today), fontWeight = FontWeight.Bold)
                }
                Button(
                    onClick = onDismiss,
                    modifier = Modifier.weight(1f).height(48.dp),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = Color(0xFFF0F4F8),
                        contentColor = Color(0xFF747D8E)
                    ),
                    shape = RoundedCornerShape(14.dp)
                ) {
                    Icon(
                        painter = painterResource(Res.drawable.ic_wo_close),
                        contentDescription = null,
                        modifier = Modifier.size(17.dp)
                    )
                    Spacer(Modifier.width(6.dp))
                    Text(stringResource(Res.string.str_cancel), fontWeight = FontWeight.Bold)
                }
            }
        }
    }
}

@Composable
private fun CircleArrow(text: String, onClick: () -> Unit) {
    Box(
        Modifier
            .size(38.dp)
            .clip(CircleShape)
            .background(Color(0xFF6FA3B4))
            .clickable(onClick = onClick),
        contentAlignment = Alignment.Center
    ) {
        Text(
            text,
            color = Color.White,
            fontSize = 28.sp,
            fontWeight = FontWeight.Bold,
            modifier = Modifier.offset(y = (-2).dp)
        )
    }
}

