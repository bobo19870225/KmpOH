package com.example.kmpoh.utils.date

import kotlinx.datetime.Clock
import kotlinx.datetime.LocalDate
import kotlinx.datetime.TimeZone
import kotlinx.datetime.YearMonth
import kotlinx.datetime.isoDayNumber
import kotlinx.datetime.number
import kotlinx.datetime.todayIn

/**
 * 日期展示与日历辅助（照搬原工程 `WorkOrderModels` 的 java.time 扩展语义，
 * 基于 kotlinx.datetime——openspec migrate-work-order-page 决策 1）。
 */

fun LocalDate.toMonthTitle(): String = "${year}年 ${monthNumber}月"

fun LocalDate.toSelectedSubtitle(): String {
    val week = arrayOf("一", "二", "三", "四", "五", "六", "日")[dayOfWeek.isoDayNumber - 1]
    return "${monthNumber} 月 ${day} 日 周$week"
}

/** 本周周一（周起始=周一，对齐原工程）。 */
fun LocalDate.startOfWeek(): LocalDate =
    LocalDate.fromEpochDays(toEpochDays() - (dayOfWeek.isoDayNumber - 1))

/** 取当月安全日：越界夹取到月界（原工程 `atSafeDay`；0.7.1 无 atDay/atEndOfMonth，用构造 + numberOfDays）。 */
fun YearMonth.atSafeDay(day: Int): LocalDate = LocalDate(year, month.number, day.coerceIn(1, numberOfDays))

/** 翻月（总月数算术，跨年正确；成员同名时以成员为准）。 */
fun YearMonth.plusMonths(months: Int): YearMonth {
    val total = year * 12 + (month.number - 1) + months
    return YearMonth(total.floorDiv(12), total.mod(12) + 1)
}

/** 翻周（epoch 日算术）。 */
fun LocalDate.plusWeeks(weeks: Int): LocalDate =
    LocalDate.fromEpochDays(toEpochDays() + weeks * 7)

/** 系统时区今天。 */
fun todayDate(): LocalDate = Clock.System.todayIn(TimeZone.currentSystemDefault())

/** 取日期所在年月（0.7.1 无 YearMonth.from，用构造）。 */
fun yearMonthOf(date: LocalDate): YearMonth = YearMonth(date.year, date.monthNumber)
