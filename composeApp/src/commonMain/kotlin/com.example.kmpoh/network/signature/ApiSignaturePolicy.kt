package com.example.kmpoh.network.signature

import com.example.kmpoh.network.GeneratedApiConfig

/** 签名模式（对齐原工程 AppConstant.ApiSignatureMode）。 */
enum class ApiSignatureMode {
    /** 不签名、不验签。 */
    Off,

    /** 仅请求签名。 */
    RequestOnly,

    /** 请求签名 + 响应验签。 */
    Mutual;

    companion object {
        fun fromConfigValue(value: String): ApiSignatureMode = when (value) {
            "request" -> RequestOnly
            "mutual" -> Mutual
            else -> Off
        }
    }
}

/**
 * 签名策略（对齐原工程 network/signature/ApiSignaturePolicy.kt）：
 * 登录路径免签；PDF 预览路径不验响应签；HTTP 401 不验签；密钥缺失视为整体关闭。
 */
class ApiSignaturePolicy(
    val mode: ApiSignatureMode,
    val apiSecret: String,
    val maxClockSkewSeconds: Long
) {
    val isEnabled: Boolean = mode != ApiSignatureMode.Off && apiSecret.isNotBlank()

    val verifiesResponses: Boolean = isEnabled && mode == ApiSignatureMode.Mutual

    fun isUnsignedPath(path: String): Boolean = path in unsignedPaths

    fun isUnverifiedResponsePath(path: String): Boolean = path in unverifiedResponsePaths

    companion object {
        /** 免签路径（与原工程 API_LOGIN_PATH 对应）。 */
        val unsignedPaths = setOf("mobile/Staff.Login/login")

        /** 不验响应签路径（PDF 预览等流式接口，随接口迁移补充）。 */
        val unverifiedResponsePaths = setOf<String>()

        fun fromConfig(): ApiSignaturePolicy = ApiSignaturePolicy(
            mode = ApiSignatureMode.fromConfigValue(GeneratedApiConfig.SIGNATURE_MODE),
            apiSecret = GeneratedApiConfig.API_SIGNATURE_SECRET,
            maxClockSkewSeconds = GeneratedApiConfig.SIGNATURE_MAX_CLOCK_SKEW_SECONDS.toLong()
        )
    }
}

/** 当前秒级 Unix 时间戳（平台 actual 见 CurrentTime.*.kt）。 */
expect fun currentEpochSeconds(): Long
