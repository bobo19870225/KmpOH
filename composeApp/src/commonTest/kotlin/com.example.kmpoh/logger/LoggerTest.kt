package com.example.kmpoh.logger

import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

class LoggerSanitizeTest {

    @Test
    fun sanitizesJsonLineAndQueryForms() {
        assertEquals(
            """{"password":"$LOG_MASK","token":"$LOG_MASK","staff_code":"$LOG_MASK"}""",
            Logger.sanitize("""{"password":"p@ss","token":"tok","staff_code":"S001"}""")
        )
        assertEquals("Authorization: $LOG_MASK", Logger.sanitize("Authorization: Bearer secret-abc"))
        assertEquals("https://host/x?token=$LOG_MASK&a=1", Logger.sanitize("https://host/x?token=secret-tok&a=1"))
    }
}

class JsonSplitTest {

    @Test
    fun shortTextIsNotSplit() {
        val text = """{"a":1}"""
        with(Logger) {
            assertEquals(listOf(text), text.splitAtJsonBoundaries(100))
        }
    }

    @Test
    fun longJsonSplitsAtBoundariesAndReassembles() {
        val longValue = "x".repeat(400)
        val json = """{"a":1,"b":"$longValue","c":{"d":2},"e":[1,2,3],"f":"$longValue"}"""
        val chunks = with(Logger) { json.splitAtJsonBoundaries(300) }

        assertTrue(chunks.size > 1)
        assertTrue(chunks.all { it.length <= 300 })
        // 按顺序拼接可还原原文（原工程「可复制还原」约定）
        assertEquals(json, chunks.joinToString(""))
    }
}
