package com.example.kmpoh.network

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
import kotlinx.serialization.Serializable
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith

@Serializable
data class SampleData(val name: String = "", val userId: Int = 0)

/** 归一化按类名识别的平台网络异常同名假件（覆盖类名匹配分支）。 */
private class ConnectTimeoutException : Exception("connect timeout")
private class UnknownHostException : Exception("unknown host")

private class FakeIoException : Exception("io broken")

private fun mockClient(
    handler: suspend MockRequestHandleScope.(HttpRequestData) -> HttpResponseData
): HttpClient = HttpClient(MockEngine { request -> handler(request) }) {
    install(ContentNegotiation) { json(ApiJson) }
}

private fun MockRequestHandleScope.jsonResponse(
    body: String,
    status: HttpStatusCode = HttpStatusCode.OK
): HttpResponseData =
    respond(body, status, headersOf(HttpHeaders.ContentType, "application/json; charset=UTF-8"))

class ApiCallTest {

    @Test
    fun businessSuccessReturnsData() = runBlocking {
        val client = mockClient {
            jsonResponse("""{"code":200,"msg":"ok","data":{"name":"张三","userId":7}}""")
        }
        val data = client.callEnvelope<SampleData>("mobile/Staff.Login/login")
        assertEquals(SampleData(name = "张三", userId = 7), data)
    }

    @Test
    fun businessFailureThrowsWithServerMessage() = runBlocking {
        val client = mockClient {
            jsonResponse("""{"code":500,"msg":"账号或密码不正确","data":[]}""")
        }
        val e = assertFailsWith<BusinessApiException> {
            client.callEnvelope<SampleData>("mobile/Staff.Login/login")
        }
        assertEquals(500, e.businessCode)
        assertEquals("账号或密码不正确", e.businessMessage)
    }

    @Test
    fun failureEnvelopeWithWeirdDataDoesNotParseFail() = runBlocking {
        // 失败时 data 结构不稳定（数组/对象/异常结构都出现过），归一后必须仍是业务异常而非解析异常
        val client = mockClient {
            jsonResponse("""{"code":401,"msg":"登录信息已过期","data":{"unexpected":[1,2,3]}}""")
        }
        val e = assertFailsWith<BusinessApiException> {
            client.callEnvelope<SampleData>("api/v1/user/profile")
        }
        assertEquals(401, e.businessCode)
        assertEquals("登录信息已过期", e.businessMessage)
    }

    @Test
    fun nonJsonBodyBecomesParsing() = runBlocking<Unit> {
        val client = mockClient { jsonResponse("oops-not-json") }
        assertFailsWith<NetworkException.Parsing> {
            client.callEnvelope<SampleData>("mobile/Staff.Login/login")
        }
    }

    @Test
    fun successWithoutDataBecomesParsing() = runBlocking<Unit> {
        val client = mockClient { jsonResponse("""{"code":200,"msg":"ok"}""") }
        assertFailsWith<NetworkException.Parsing> {
            client.callEnvelope<SampleData>("mobile/Staff.Login/login")
        }
    }

    @Test
    fun httpStatusErrorMapsToHttpCategory() = runBlocking {
        val client = mockClient { jsonResponse("""{"message":"boom"}""", HttpStatusCode.InternalServerError) }
        val e = assertFailsWith<NetworkException.Http> {
            client.callEnvelope<SampleData>("mobile/Staff.Login/login")
        }
        assertEquals(500, e.statusCode)
    }

    @Test
    fun engineFailureMapsToTimeout() = runBlocking<Unit> {
        val client = mockClient { throw RuntimeException("wrapped", ConnectTimeoutException()) }
        assertFailsWith<NetworkException.Timeout> {
            client.callEnvelope<SampleData>("mobile/Staff.Login/login")
        }
    }

    @Test
    fun causeChainClassification() {
        assertFailsWith<NetworkException.Timeout> {
            throw mapTransportFailure(RuntimeException("w", ConnectTimeoutException()))
        }
        assertFailsWith<NetworkException.Unavailable> {
            throw mapTransportFailure(RuntimeException("w", UnknownHostException()))
        }
        assertFailsWith<NetworkException.Transport> {
            throw mapTransportFailure(FakeIoException())
        }
    }
}
