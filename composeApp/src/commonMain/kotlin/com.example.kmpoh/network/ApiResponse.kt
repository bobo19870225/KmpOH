package com.example.kmpoh.network

import kotlinx.serialization.Serializable

/**
 * 服务端统一响应信封（对齐原工程 data/model/dto/ApiResponse.kt）：
 * `code == 200` 业务成功，其余为业务失败并携带 `msg` 提示。
 */
@Serializable
data class ApiResponse<T>(
    val code: Int = 0,
    val msg: String = "",
    val data: T? = null
) {
    val message: String get() = msg
}

fun <T> ApiResponse<T>.isBusinessSuccess(): Boolean = code == 200

/**
 * 业务码非成功时抛出（对齐原工程转换层行为：`code != 200` 即异常，
 * Repository 的 else 分支因此基本不会走到）。
 */
class BusinessApiException(
    val businessCode: Int,
    val businessMessage: String
) : IllegalStateException(businessMessage)

fun <T> ApiResponse<T>.requireBusinessSuccess(defaultMessage: String): ApiResponse<T> {
    if (!isBusinessSuccess()) {
        throw BusinessApiException(code, message.ifBlank { defaultMessage })
    }
    return this
}
