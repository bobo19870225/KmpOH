package com.example.kmpoh.network

import io.ktor.client.request.forms.MultiPartFormDataContent
import io.ktor.client.request.forms.formData
import io.ktor.http.ContentType
import io.ktor.http.content.OutgoingContent
import io.ktor.utils.io.ByteWriteChannel

/**
 * multipart/form-data 文本字段请求体（design 决策 8 的「multipart-text」形态）。
 *
 * 不直接用 ktor 的 [MultiPartFormDataContent] 的原因：其 parts 为私有，鸿蒙桥接层读不到字段表、
 * 无法映射 RCP `MultipartForm`（线协议 `bodyMultipart`，见 [BridgeWireBody]）。本类公开字段表，
 * 序列化仍委托 ktor 标准 multipart 编码（Android/iOS 引擎线上形态不变）。文件字段随上传能力迁移再扩展。
 */
class MultipartTextContent(
    fields: Map<String, String>
) : OutgoingContent.WriteChannelContent() {

    val fields: Map<String, String> = fields.toMap()

    private val delegate = MultiPartFormDataContent(formData {
        this@MultipartTextContent.fields.forEach { (name, value) -> append(name, value) }
    })

    override val contentType: ContentType get() = delegate.contentType

    override val contentLength: Long? get() = delegate.contentLength

    override suspend fun writeTo(channel: ByteWriteChannel) = delegate.writeTo(channel)
}
