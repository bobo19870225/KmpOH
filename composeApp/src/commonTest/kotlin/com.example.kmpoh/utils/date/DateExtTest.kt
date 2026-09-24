package com.example.kmpoh.utils.date

import kotlinx.datetime.LocalDate
import kotlinx.datetime.YearMonth
import kotlin.test.Test
import kotlin.test.assertEquals

class DateExtTest {

    @Test
    fun monthTitleUsesYearAndMonth() {
        assertEquals("2025年 1月", LocalDate(2025, 1, 5).toMonthTitle())
        assertEquals("2026年 12月", LocalDate(2026, 12, 31).toMonthTitle())
    }

    @Test
    fun selectedSubtitleFormatsWithWeekName() {
        assertEquals("1 月 5 日 周日", LocalDate(2025, 1, 5).toSelectedSubtitle())
        assertEquals("9 月 1 日 周一", LocalDate(2025, 9, 1).toSelectedSubtitle())
    }

    @Test
    fun startOfWeekAlwaysMonday() {
        assertEquals(LocalDate(2025, 1, 6), LocalDate(2025, 1, 8).startOfWeek()) // 周三 → 本周一
        assertEquals(LocalDate(2025, 1, 6), LocalDate(2025, 1, 6).startOfWeek()) // 周一 → 自身
        assertEquals(LocalDate(2025, 1, 6), LocalDate(2025, 1, 12).startOfWeek()) // 周日 → 本周一
    }

    @Test
    fun atSafeDayClampsToMonthBounds() {
        assertEquals(LocalDate(2025, 1, 31), YearMonth(2025, 1).atSafeDay(31))
        assertEquals(LocalDate(2025, 2, 28), YearMonth(2025, 2).atSafeDay(31))
        assertEquals(LocalDate(2024, 2, 29), YearMonth(2024, 2).atSafeDay(31)) // 闰年
        assertEquals(LocalDate(2025, 3, 1), YearMonth(2025, 3).atSafeDay(0))
    }

    @Test
    fun yearMonthEdgesAcrossYear() {
        assertEquals(YearMonth(2026, 1), YearMonth(2025, 12).plusMonths(1))
        assertEquals(YearMonth(2025, 12), YearMonth(2026, 1).plusMonths(-1))
        assertEquals(29, YearMonth(2024, 2).numberOfDays) // 闰年月长
    }
}
