package com.example.kmpoh.data.repository

import com.example.kmpoh.network.ApiGateway
import com.example.kmpoh.network.ApiJson
import com.example.kmpoh.network.AuthSessionManager
import com.example.kmpoh.network.NetworkMessages
import com.example.kmpoh.storage.FakeKeyValueStore
import com.example.kmpoh.storage.StorageKeys
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
import kotlinx.coroutines.runBlocking
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNull

/** 归一化按类名识别的超时假异常。 */
private class ConnectTimeoutException : Exception("t")

private fun loginRepoMockClient(
    handler: suspend MockRequestHandleScope.(HttpRequestData) -> HttpResponseData
): HttpClient = HttpClient(MockEngine { request -> handler(request) }) {
    install(ContentNegotiation) { json(ApiJson) }
}

private fun MockRequestHandleScope.repoJsonResponse(
    body: String,
    status: HttpStatusCode = HttpStatusCode.OK
): HttpResponseData =
    respond(body, status, headersOf(HttpHeaders.ContentType, "application/json; charset=UTF-8"))

private val LOGIN_SUCCESS_BODY = """
    {"code":200,"msg":"ok","data":{"token":"tok-1","user_id":7,"name":"张三","code":"S001",
     "phone":"13812345678","access_token":"acc-b","refresh_token":"ref-1"}}
""".trimIndent()

class LoginRepositoryTest {

    private fun repositoryWith(client: HttpClient, store: FakeKeyValueStore): NetworkLoginRepository {
        val session = AuthSessionManager(store)
        return NetworkLoginRepository(ApiGateway(client, session, deviceId = "dev-1"), session, store)
    }

    @Test
    fun loginSuccessPersistsTokensAndReturnsUserModel() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val client = loginRepoMockClient { repoJsonResponse(LOGIN_SUCCESS_BODY) }
        val repository = repositoryWith(client, store)

        val result = repository.login("S001", "pw")

        val model = result.getOrThrow()
        assertEquals("张三", model.displayName)
        assertEquals("tok-1", store.getString(StorageKeys.AUTH_ACCESS_TOKEN))
        assertEquals("ref-1", store.getString(StorageKeys.AUTH_REFRESH_TOKEN))
    }

    @Test
    fun tokenFieldCompatibilityOnLogin() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val client = loginRepoMockClient {
            repoJsonResponse(
                """{"code":200,"msg":"ok","data":{"token":"","user_id":1,"name":"n","access_token":"acc-only","refresh_token":""}}"""
            )
        }
        val repository = repositoryWith(client, store)

        repository.login("S001", "pw").getOrThrow()

        // 主字段为空取 access_token；refresh 为空兜底 access
        assertEquals("acc-only", store.getString(StorageKeys.AUTH_ACCESS_TOKEN))
        assertEquals("acc-only", store.getString(StorageKeys.AUTH_REFRESH_TOKEN))
    }

    @Test
    fun businessFailureUsesServerMessageAndWritesNoToken() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val client = loginRepoMockClient {
            repoJsonResponse("""{"code":500,"msg":"账号或密码不正确","data":[]}""")
        }
        val repository = repositoryWith(client, store)

        val result = repository.login("S001", "wrong")

        assertEquals("账号或密码不正确", result.exceptionOrNull()?.message)
        assertNull(store.getString(StorageKeys.AUTH_ACCESS_TOKEN))
        assertNull(store.getString(StorageKeys.AUTH_REFRESH_TOKEN))
    }

    @Test
    fun timeoutShowsNetworkCategoryMessage() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val client = loginRepoMockClient { throw RuntimeException("w", ConnectTimeoutException()) }
        val repository = repositoryWith(client, store)

        val result = repository.login("S001", "pw")

        assertEquals(NetworkMessages.TIMEOUT, result.exceptionOrNull()?.message)
    }

    @Test
    fun unknownEngineFailureMapsToTransportCategoryMessage() = runBlocking<Unit> {
        val store = FakeKeyValueStore()
        val client = loginRepoMockClient { throw IllegalStateException("boom") }
        val repository = repositoryWith(client, store)

        val result = repository.login("S001", "pw")

        // 引擎未知异常归一为传输失败类别 → 类别文案（spec 第二优先级）
        assertEquals(NetworkMessages.TRANSPORT, result.exceptionOrNull()?.message)
    }

    @Test
    fun unknownErrorFallsBackToGenericLoginMessage() {
        // 无类别异常（均缺失时）→ 通用登录失败兜底文案（spec 第三优先级）
        assertEquals(NetworkMessages.LOGIN_FALLBACK, IllegalStateException("x").toLoginFailureMessage())
    }
}
