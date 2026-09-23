package com.example.kmpoh.network

import com.example.kmpoh.storage.FakeKeyValueStore
import com.example.kmpoh.storage.PLATFORM_NAME
import io.ktor.client.HttpClient
import io.ktor.client.engine.mock.MockEngine
import io.ktor.client.engine.mock.MockRequestHandleScope
import io.ktor.client.engine.mock.respond
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.client.request.HttpRequestData
import io.ktor.client.request.HttpResponseData
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpStatusCode
import io.ktor.http.headersOf
import io.ktor.serialization.kotlinx.json.json
import kotlinx.coroutines.flow.onSubscription
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertNull

private fun gatewayMockClient(
    handler: suspend MockRequestHandleScope.(HttpRequestData) -> HttpResponseData
): HttpClient = HttpClient(MockEngine { request -> handler(request) }) {
    install(ContentNegotiation) { json(ApiJson) }
}

private fun MockRequestHandleScope.gatewayJsonResponse(
    body: String,
    status: HttpStatusCode = HttpStatusCode.OK
): HttpResponseData =
    respond(body, status, headersOf(HttpHeaders.ContentType, "application/json; charset=UTF-8"))

private const val SUCCESS_SAMPLE = """{"code":200,"msg":"ok","data":{"name":"张三","userId":7}}"""
private const val EXPIRED_ENVELOPE = """{"code":401,"msg":"登录信息已过期","data":[]}"""
private const val REFRESH_OK = """{"code":200,"msg":"ok","data":{"token":"tok-NEW","access_token":""}}"""

class ApiGatewayTest {

    @Test
    fun authenticatedRequestCarriesAuthAndCommonHeaders() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val session = AuthSessionManager(store).apply { saveTokens("tok-1", "ref-1") }
        var captured: HttpRequestData? = null
        val client = gatewayMockClient { request ->
            captured = request
            gatewayJsonResponse(SUCCESS_SAMPLE)
        }
        val gateway = ApiGateway(client, session, deviceId = "dev-1")

        gateway.postJson<com.example.kmpoh.network.SampleData>("api/v1/user/profile")

        val headers = captured!!.headers
        assertEquals("Bearer tok-1", headers[HttpHeaders.Authorization])
        assertEquals("tok-1", headers["ApiToken"])
        assertEquals(PLATFORM_NAME, headers["Platform"])
        assertEquals("dev-1", headers["DeviceId"])
        assertEquals("dev-1", headers["X-Device-Id"])
        assertEquals("zh-CN", headers["Language"])
        assertEquals("Technician-$PLATFORM_NAME/1.0", headers[HttpHeaders.UserAgent])
    }

    @Test
    fun loginExpiredRefreshesTokenAndRetriesOnce() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val session = AuthSessionManager(store).apply { saveTokens("tok-OLD", "ref-OLD") }
        val paths = mutableListOf<String>()
        val client = gatewayMockClient { request ->
            paths += request.url.encodedPath
            when {
                request.url.encodedPath.contains("refreshToken") -> gatewayJsonResponse(REFRESH_OK)
                paths.size == 1 -> gatewayJsonResponse(EXPIRED_ENVELOPE)
                else -> gatewayJsonResponse(SUCCESS_SAMPLE)
            }
        }
        val gateway = ApiGateway(client, session, deviceId = "dev-1")

        val data = gateway.postJson<SampleData>("api/v1/user/profile")

        assertEquals(SampleData(name = "张三", userId = 7), data)
        assertEquals(3, paths.size) // 原请求 → 刷新 → 重试一次
        assertEquals("tok-NEW", store.getString(com.example.kmpoh.storage.StorageKeys.AUTH_ACCESS_TOKEN))
        assertEquals("tok-NEW", store.getString(com.example.kmpoh.storage.StorageKeys.AUTH_REFRESH_TOKEN))
    }

    @Test
    fun refreshFailureClearsSessionAndEmitsLoginExpired() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val session = AuthSessionManager(store).apply { saveTokens("tok-OLD", "ref-OLD") }
        var expiredEvent: AuthSessionEvent? = null
        val subscribed = kotlinx.coroutines.CompletableDeferred<Unit>()
        val collectJob = launch {
            session.events
                .onSubscription { subscribed.complete(Unit) }
                .collect { expiredEvent = it }
        }
        subscribed.await() // 确保收集器已订阅，避免事件在订阅前被丢弃
        val paths = mutableListOf<String>()
        val client = gatewayMockClient { request ->
            paths += request.url.encodedPath
            when {
                request.url.encodedPath.contains("refreshToken") ->
                    gatewayJsonResponse("""{"code":500,"msg":"刷新失败","data":[]}""")

                else -> gatewayJsonResponse(EXPIRED_ENVELOPE)
            }
        }
        val gateway = ApiGateway(client, session, deviceId = "dev-1")

        val failure = assertFailsWith<BusinessApiException> {
            gateway.postJson<SampleData>("api/v1/user/profile")
        }
        kotlinx.coroutines.yield() // 让收集协程处理已投递的事件（单线程 runBlocking 下需主动让出）
        collectJob.cancel()

        assertEquals(401, failure.businessCode) // 上抛的是原始登录失效错误
        assertEquals(2, paths.size) // 原请求 + 刷新（失败后不重试）
        assertNull(store.getString(com.example.kmpoh.storage.StorageKeys.AUTH_ACCESS_TOKEN))
        assertNull(store.getString(com.example.kmpoh.storage.StorageKeys.AUTH_REFRESH_TOKEN))
        assertEquals(true, expiredEvent is AuthSessionEvent.LoginExpired)
    }

    @Test
    fun loginPathDoesNotTriggerRefresh() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val session = AuthSessionManager(store).apply { saveTokens("tok-1", "ref-1") }
        var count = 0
        val client = gatewayMockClient {
            count++
            gatewayJsonResponse(EXPIRED_ENVELOPE)
        }
        val gateway = ApiGateway(client, session, deviceId = "dev-1")

        assertFailsWith<BusinessApiException> {
            gateway.postJson<SampleData>("mobile/Staff.Login/login")
        }
        assertEquals(1, count)
    }

    @Test
    fun skipAuthRefreshDoesNotTriggerRefresh() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val session = AuthSessionManager(store).apply { saveTokens("tok-1", "ref-1") }
        var count = 0
        val client = gatewayMockClient {
            count++
            gatewayJsonResponse(EXPIRED_ENVELOPE)
        }
        val gateway = ApiGateway(client, session, deviceId = "dev-1")

        assertFailsWith<BusinessApiException> {
            gateway.postJson<SampleData>("api/v1/user/profile", skipAuthRefresh = true)
        }
        assertEquals(1, count)
    }
}
