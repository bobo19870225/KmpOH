package com.example.kmpoh.network

import io.ktor.client.HttpClient
import io.ktor.client.engine.mock.MockEngine
import io.ktor.client.engine.mock.MockRequestHandleScope
import io.ktor.client.engine.mock.respond
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.client.request.HttpRequestData
import io.ktor.client.request.HttpResponseData
import io.ktor.client.request.header
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpStatusCode
import io.ktor.http.headersOf
import io.ktor.serialization.kotlinx.json.json
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertTrue

class MaskingTest {

    @Test
    fun masksJsonCredentialFields() {
        val input = """{"staff_code":"S001","password":"p@ss","token":"tok-123","sign":"AB","access_token":"at","refresh_token":"rt"}"""
        val masked = maskSensitiveText(input)
        assertFalse(masked.contains("p@ss"))
        assertFalse(masked.contains("tok-123"))
        assertFalse(masked.contains("\"AB\""))
        assertFalse(masked.contains("\"at\""))
        assertFalse(masked.contains("\"rt\""))
        assertTrue(masked.contains("\"password\":\"$LOG_MASK\""))
        assertTrue(masked.contains("\"staff_code\":\"S001\""))
    }

    @Test
    fun masksHeaderValueUpToLineEnd() {
        val masked = maskSensitiveText("Authorization: Bearer secret-token-value")
        assertFalse(masked.contains("secret-token-value"))
        assertTrue(masked.contains(LOG_MASK))
    }

    @Test
    fun masksKeyValueForms() {
        val masked = maskSensitiveText("password=p@ss&staff_code=S001")
        assertFalse(masked.contains("p@ss"))
    }

    @Test
    fun truncatesLongBodies() {
        val long = "x".repeat(LOG_BODY_MAX_CHARS + 100)
        val truncated = truncateForLog(long)
        assertTrue(truncated.length < long.length)
        assertTrue(truncated.contains("truncated"))
        assertEquals("short", truncateForLog("short"))
    }
}

class NetworkRequestTrackerTest {

    @Test
    fun concurrentCountsFallBackCorrectly() {
        val tracker = NetworkRequestTracker()
        assertEquals(0, tracker.activeRequests.value)
        tracker.onRequestStarted()
        tracker.onRequestStarted()
        assertEquals(2, tracker.activeRequests.value)
        tracker.onRequestFinished()
        assertEquals(1, tracker.activeRequests.value)
        tracker.onRequestFinished()
        assertEquals(0, tracker.activeRequests.value)
        tracker.onRequestFinished() // 超额回落不允许为负
        assertEquals(0, tracker.activeRequests.value)
    }
}

private fun counterMockClient(
    handler: suspend MockRequestHandleScope.(HttpRequestData) -> HttpResponseData
): HttpClient = HttpClient(MockEngine { request -> handler(request) }) {
    install(ContentNegotiation) { json(ApiJson) }
}

private fun MockRequestHandleScope.counterJsonResponse(): HttpResponseData =
    respond(
        """{"code":200,"msg":"ok","data":{"name":"x","userId":1}}""",
        HttpStatusCode.OK,
        headersOf(HttpHeaders.ContentType, "application/json; charset=UTF-8")
    )

class GlobalLoadingCountTest {

    @Test
    fun concurrentRequestsKeepBusyUntilAllFinish() = runBlocking<Unit> {
        val tracker = NetworkRequestTracker()
        var maxSeen = 0
        val client = counterMockClient {
            maxSeen = maxOf(maxSeen, tracker.activeRequests.value)
            delay(50)
            counterJsonResponse()
        }

        val a = launch {
            client.callEnvelopeWith("a", SampleData.serializer(), loadingTracker = tracker)
        }
        val b = launch {
            client.callEnvelopeWith("b", SampleData.serializer(), loadingTracker = tracker)
        }
        a.join()
        b.join()

        assertEquals(2, maxSeen) // 并发期间忙碌
        assertEquals(0, tracker.activeRequests.value) // 全部结束后回落
    }

    @Test
    fun skipMarkerRequestIsNotCountedAndHeaderStripped() = runBlocking<Unit> {
        val tracker = NetworkRequestTracker()
        var captured: HttpRequestData? = null
        var seenDuring = -1
        val client = counterMockClient { request ->
            captured = request
            seenDuring = tracker.activeRequests.value
            counterJsonResponse()
        }

        client.callEnvelopeWith(
            path = "a",
            deserializer = SampleData.serializer(),
            requestExtras = { header(HEADER_SHOW_GLOBAL_LOADING, "false") },
            loadingTracker = tracker
        )

        assertEquals(0, seenDuring)
        assertEquals(0, tracker.activeRequests.value)
        assertFalse(captured!!.headers.contains(HEADER_SHOW_GLOBAL_LOADING)) // 控制头发送前剥掉
    }

    @Test
    fun failedRequestStillFallsBack() = runBlocking<Unit> {
        val tracker = NetworkRequestTracker()
        val client = counterMockClient { throw RuntimeException("boom") }
        runCatching {
            client.callEnvelopeWith("a", SampleData.serializer(), loadingTracker = tracker)
        }
        assertEquals(0, tracker.activeRequests.value)
    }
}
