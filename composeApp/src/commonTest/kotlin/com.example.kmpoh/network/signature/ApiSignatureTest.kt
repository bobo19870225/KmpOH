package com.example.kmpoh.network.signature

import com.example.kmpoh.network.ApiGateway
import com.example.kmpoh.network.ApiJson
import com.example.kmpoh.network.AuthSessionManager
import com.example.kmpoh.network.NetworkException
import com.example.kmpoh.network.SampleData
import com.example.kmpoh.network.postJson
import com.example.kmpoh.storage.FakeKeyValueStore
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
import kotlin.test.assertFailsWith
import kotlin.test.assertFalse
import kotlin.test.assertNull
import kotlin.test.assertTrue

class ApiSignatureEngineTest {

    @Test
    fun md5MatchesKnownVectors() {
        assertEquals("D41D8CD98F00B204E9800998ECF8427E", md5UpperHex(""))
        assertEquals("900150983CD24FB0D6963F7D28E17F72", md5UpperHex("abc"))
        assertEquals("F96B697D7CB7938D525A2F31AAF161D0", md5UpperHex("message digest"))
    }

    @Test
    fun signAssemblesProtocolInOrder() {
        // 协议：MD5(secret + timestamp + nonce + params + secret) 大写十六进制
        val expected = md5UpperHex("SECRET" + "1700000000" + "ABC" + "staff_code=S001&password=pw" + "SECRET")
        assertEquals(
            expected,
            ApiSignatureEngine.sign("SECRET", "1700000000", "ABC", "staff_code=S001&password=pw")
        )
    }

    @Test
    fun canonicalParamsSortsFiltersAndFlattens() {
        val body = """
            {"password":"pw","staff_code":"S001","sign":"X","timestamp":"1","nonce":"n",
             "file":"f","empty":"","nil":null,"nested":{"a":1},"num":42,"flag":true}
        """.trimIndent()
        // 数字/布尔按原文；嵌套对象不展开；排除 sign/timestamp/nonce/file/空值；按 key 字典序
        assertEquals("flag=true&num=42&password=pw&staff_code=S001", ApiSignatureEngine.canonicalParamsOf(body))
    }

    @Test
    fun canonicalParamsFallsBackToRawText() {
        assertEquals("not-json", ApiSignatureEngine.canonicalParamsOf("not-json"))
        assertEquals("", ApiSignatureEngine.canonicalParamsOf(null))
        assertEquals("", ApiSignatureEngine.canonicalParamsOf("   "))
    }

    @Test
    fun timestampSkewValidation() {
        assertTrue(ApiSignatureEngine.isTimestampValid("1000", nowEpochSeconds = 1000, maxClockSkewSeconds = 300))
        assertTrue(ApiSignatureEngine.isTimestampValid("1300", nowEpochSeconds = 1000, maxClockSkewSeconds = 300))
        assertFalse(ApiSignatureEngine.isTimestampValid("1301", nowEpochSeconds = 1000, maxClockSkewSeconds = 300))
        assertFalse(ApiSignatureEngine.isTimestampValid("abc", nowEpochSeconds = 1000, maxClockSkewSeconds = 300))
    }

    @Test
    fun signaturesMatchIsCaseInsensitive() {
        assertTrue(ApiSignatureEngine.signaturesMatch("ABCDEF", "abcdef"))
        assertFalse(ApiSignatureEngine.signaturesMatch("ABCDEF", "ABCDE0"))
    }

    @Test
    fun policyTreatsMissingSecretAsDisabled() {
        val policy = ApiSignaturePolicy(ApiSignatureMode.RequestOnly, apiSecret = "", maxClockSkewSeconds = 300)
        assertFalse(policy.isEnabled)
        assertFalse(policy.verifiesResponses)
    }

    @Test
    fun policyExemptsLoginPath() {
        val policy = ApiSignaturePolicy(ApiSignatureMode.RequestOnly, apiSecret = "S", maxClockSkewSeconds = 300)
        assertTrue(policy.isUnsignedPath("mobile/Staff.Login/login"))
        assertFalse(policy.isUnsignedPath("api/v1/user/profile"))
    }
}

private fun sigMockClient(
    handler: suspend MockRequestHandleScope.(HttpRequestData) -> HttpResponseData
): HttpClient = HttpClient(MockEngine { request -> handler(request) }) {
    install(ContentNegotiation) { json(ApiJson) }
}

private fun MockRequestHandleScope.sigJsonResponse(body: String): HttpResponseData =
    respond(body, HttpStatusCode.OK, headersOf(HttpHeaders.ContentType, "application/json; charset=UTF-8"))

class ApiSignatureWiringTest {

    private fun gatewayWith(policy: ApiSignaturePolicy, onCapture: (HttpRequestData) -> Unit): ApiGateway {
        val session = AuthSessionManager(FakeKeyValueStore())
        val client = sigMockClient { request ->
            onCapture(request)
            sigJsonResponse("""{"code":200,"msg":"ok","data":{"name":"张三","userId":7}}""")
        }
        return ApiGateway(client, session, deviceId = "dev-1", signature = policy)
    }

    @Test
    fun businessRequestCarriesSignatureHeaders() = runBlocking<Unit> {
        var captured: HttpRequestData? = null
        val policy = ApiSignaturePolicy(ApiSignatureMode.RequestOnly, apiSecret = "SECRET", maxClockSkewSeconds = 300)
        val gateway = gatewayWith(policy) { captured = it }

        gateway.postJson<SampleData, SampleData>("api/v1/user/profile", SampleData(name = "张三", userId = 7))

        val headers = captured!!.headers
        val timestamp = headers["Timestamp"]
        val nonce = headers["Nonce"]
        val sign = headers["Sign"]
        assertTrue(timestamp != null && nonce != null && sign != null)
        val canonical = ApiSignatureEngine.canonicalParamsOf(ApiJson.encodeToString(SampleData(name = "张三", userId = 7)))
        assertEquals(
            ApiSignatureEngine.sign("SECRET", timestamp!!, nonce!!, canonical),
            sign
        )
    }

    @Test
    fun loginRequestIsUnsigned() = runBlocking<Unit> {
        var captured: HttpRequestData? = null
        val policy = ApiSignaturePolicy(ApiSignatureMode.RequestOnly, apiSecret = "SECRET", maxClockSkewSeconds = 300)
        val gateway = gatewayWith(policy) { captured = it }

        gateway.postJson<SampleData, SampleData>("mobile/Staff.Login/login", SampleData())

        assertNull(captured!!.headers["Sign"])
        assertNull(captured!!.headers["Timestamp"])
        assertNull(captured!!.headers["Nonce"])
    }

    @Test
    fun missingSecretDisablesSigning() = runBlocking<Unit> {
        var captured: HttpRequestData? = null
        val policy = ApiSignaturePolicy(ApiSignatureMode.RequestOnly, apiSecret = "", maxClockSkewSeconds = 300)
        val gateway = gatewayWith(policy) { captured = it }

        gateway.postJson<SampleData, SampleData>("api/v1/user/profile", SampleData())

        assertNull(captured!!.headers["Sign"])
    }

    @Test
    fun mutualModeFailsTransportOnBadResponseSignature() = runBlocking<Unit> {
        val policy = ApiSignaturePolicy(ApiSignatureMode.Mutual, apiSecret = "SECRET", maxClockSkewSeconds = 300)
        val session = AuthSessionManager(FakeKeyValueStore())
        val client = sigMockClient {
            sigJsonResponse("""{"code":200,"msg":"ok","data":{"name":"x","userId":1}}""")
        }
        val gateway = ApiGateway(client, session, deviceId = "dev-1", signature = policy)

        // 响应没有 Sign/Timestamp/Nonce 头 → 验签失败按传输错误
        assertFailsWith<NetworkException.Transport> {
            gateway.postJson<SampleData, SampleData>("api/v1/user/profile", SampleData())
        }
    }
}
