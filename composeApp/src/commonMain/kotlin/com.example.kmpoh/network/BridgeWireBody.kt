package com.example.kmpoh.network

import io.ktor.client.request.forms.FormDataContent
import io.ktor.http.content.OutgoingContent
import io.ktor.http.content.TextContent
import io.ktor.util.encodeBase64

/**
 * 鸿蒙 HTTP 桥线协议的请求体编码结果（`RcpHttpClientEngine` 把它序列化进桥接 JSON；
 * ArkTS 侧 `harmonyApp/entry/src/main/ets/network/HttpBridge.ets` 的 `buildContent` 同构消费——
 * **改一侧必改另一侧**）：
 *
 * - JSON（[TextContent]）→ `bodyJson`：ArkTS 侧 JSON.parse 成对象交 RCP（自动 application/json）；
 * - 表单（[FormDataContent]）→ `bodyForm`：ArkTS 侧 `rcp.Form`（application/x-www-form-urlencoded）；
 * - multipart 文本（[MultipartTextContent]）→ `bodyMultipart`：ArkTS 侧 `rcp.MultipartForm`（multipart/form-data）；
 * - 二进制（[ByteArrayContent]）→ `bodyBase64`：ArkTS 侧 ArrayBuffer 交 RCP（octet-stream）。
 *
 * 表单/multipart **不能**降级为 bodyBase64：RCP 对裸 string/ArrayBuffer 按 text/plain/octet-stream
 * 发出，服务端读不到参数（实测登录报「请输入账号」、dayOrder 报「请选择日期」）——必须走 RCP 的
 * Form/MultipartForm 内容形态。流式内容（ReadChannelContent）由引擎自行读字节编码，不在此处理。
 */
internal class BridgeWireBody(
    val bodyJson: String? = null,
    val bodyBase64: String? = null,
    val bodyForm: Map<String, String>? = null,
    val bodyMultipart: Map<String, String>? = null
)

/**
 * 请求体 → 线协议形态（字段表按首值映射；多值字段随上传能力迁移再扩展）。
 *
 * 注意 ktor 有**两个同名 ByteArrayContent**：`io.ktor.http.content.ByteArrayContent`（顶层具体类）
 * 与 [OutgoingContent.ByteArrayContent]（抽象基类，TextContent/FormDataContent 皆其子类）。
 * 二进制分支必须匹配后者——用前者会让 FormDataContent 等静默落入 else 丢体（「请选择日期」事故根因）。
 */
internal fun OutgoingContent.toBridgeWireBody(): BridgeWireBody = when (this) {
    is OutgoingContent.NoContent -> BridgeWireBody()
    is TextContent -> BridgeWireBody(bodyJson = text)
    is FormDataContent -> BridgeWireBody(bodyForm = formData.toSingleFieldMap())
    is MultipartTextContent -> BridgeWireBody(bodyMultipart = fields)
    is OutgoingContent.ByteArrayContent -> BridgeWireBody(bodyBase64 = bytes().encodeBase64())
    is OutgoingContent.ReadChannelContent -> throw UnsupportedOperationException(
        "ReadChannelContent 由引擎读取流后编码（toBridgeWireBody 不处理）"
    )
    is OutgoingContent.WriteChannelContent -> throw UnsupportedOperationException(
        "WriteChannelContent 不受桥接层支持（请用 Text/FormData/MultipartText/ByteArray 内容）：" +
            this::class.simpleName
    )
    else -> throw IllegalStateException("未知请求体类型：" + this::class.simpleName)
}

private fun io.ktor.http.Parameters.toSingleFieldMap(): Map<String, String> =
    entries().mapNotNull { (name, values) -> values.firstOrNull()?.let { name to it } }.toMap()
