package com.example.kmpoh.network

import io.ktor.client.request.forms.FormDataContent
import io.ktor.http.ContentType
import io.ktor.http.Parameters
import io.ktor.http.content.ByteArrayContent
import io.ktor.http.content.OutgoingContent
import io.ktor.http.content.TextContent
import io.ktor.utils.io.ByteChannel
import io.ktor.utils.io.ByteWriteChannel
import io.ktor.utils.io.readRemaining
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlinx.io.readByteArray
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertNull
import kotlin.test.assertTrue

/**
 * 鸿蒙 HTTP 桥线协议的请求体编码（与 HttpBridge.ets 的 buildContent 两侧同构）。
 * 回归钉：FormDataContent/MultipartTextContent 必须映射为 bodyForm/bodyMultipart（RCP Form/MultipartForm），
 * 不得落入 bodyBase64 裸 ArrayBuffer 路径（RCP 按 octet-stream 发出、服务端读不到参数——「请选择日期」事故）。
 */
class BridgeWireBodyTest {

    @Test
    fun formDataContentMapsToBodyFormNotRawBytes() {
        val content = FormDataContent(
            Parameters.build {
                append("job_date", "2026-09-24")
                append("day_order_type", "all")
                append("page", "1")
                append("limit", "20")
            }
        )
        val body = content.toBridgeWireBody()
        assertEquals(
            mapOf(
                "job_date" to "2026-09-24",
                "day_order_type" to "all",
                "page" to "1",
                "limit" to "20"
            ),
            body.bodyForm
        )
        assertNull(body.bodyBase64)
        assertNull(body.bodyJson)
        assertNull(body.bodyMultipart)
    }

    @Test
    fun multipartTextContentMapsToBodyMultipart() {
        val content = MultipartTextContent(mapOf("month" to "2026-09"))
        val body = content.toBridgeWireBody()
        assertEquals(mapOf("month" to "2026-09"), body.bodyMultipart)
        assertNull(body.bodyBase64)
        assertNull(body.bodyJson)
        assertNull(body.bodyForm)
    }

    @Test
    fun textContentMapsToBodyJson() {
        val body = TextContent("""{"a":1}""", ContentType.Application.Json).toBridgeWireBody()
        assertEquals("""{"a":1}""", body.bodyJson)
        assertNull(body.bodyBase64)
        assertNull(body.bodyForm)
        assertNull(body.bodyMultipart)
    }

    @Test
    fun byteArrayContentMapsToBodyBase64() {
        val content = object : OutgoingContent.ByteArrayContent() {
            override fun bytes(): ByteArray = byteArrayOf(1, 2, 3)
        }
        val body = content.toBridgeWireBody()
        assertEquals("AQID", body.bodyBase64)
        assertNull(body.bodyJson)
        assertNull(body.bodyForm)
        assertNull(body.bodyMultipart)
    }

    @Test
    fun noContentProducesEmptyBody() {
        val body = object : OutgoingContent.NoContent() {}.toBridgeWireBody()
        assertNull(body.bodyJson)
        assertNull(body.bodyBase64)
        assertNull(body.bodyForm)
        assertNull(body.bodyMultipart)
    }

    @Test
    fun unknownWriteChannelContentIsRejectedLoudly() {
        val content = object : OutgoingContent.WriteChannelContent() {
            override suspend fun writeTo(channel: ByteWriteChannel) {}
        }
        val error = assertFailsWith<UnsupportedOperationException> { content.toBridgeWireBody() }
        assertTrue(error.message.orEmpty().contains("WriteChannelContent"))
    }
}

class MultipartTextContentTest {

    @Test
    fun exposesFieldMapForBridgeAndKeepsMultipartContentType() {
        val content = MultipartTextContent(mapOf("month" to "2026-09"))
        assertEquals(mapOf("month" to "2026-09"), content.fields)
        assertEquals(ContentType.MultiPart.FormData, content.contentType?.withoutParameters())
        assertTrue(content.contentType?.parameter("boundary").orEmpty().isNotBlank())
    }

    @Test
    fun writeToEmitsFormFieldsInMultipartFraming() {
        val content = MultipartTextContent(mapOf("month" to "2026-09"))
        val channel = ByteChannel(autoFlush = true)
        runBlocking {
            launch { content.writeTo(channel) }
            val text = channel.readRemaining().readByteArray().decodeToString()
            // ktor 的 escapeIfNeeded 对普通键名不加引号（name=month），特殊字符才加引号——两种形态都合法
            assertTrue(text.contains("name=month") || text.contains("name=\"month\""))
            assertTrue(text.contains("2026-09"))
            val boundary = content.contentType?.parameter("boundary").orEmpty()
            assertTrue(text.contains("--$boundary"))
            assertTrue(text.contains("--$boundary--"))
        }
    }
}
