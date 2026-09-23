package com.example.kmpoh.network.signature

import com.example.kmpoh.network.NetworkException
import io.ktor.client.request.HttpRequestBuilder
import io.ktor.client.request.header
import io.ktor.http.Headers
import kotlin.random.Random

/**
 * 请求签名装配与响应验签（openspec/changes/migrate-network-and-login/design.md 决策 5）。
 * 签名头在认证头写入后计算（Sign 覆盖 body 参数，与头注入顺序无关，但保持原链顺序语义）。
 */

private const val NONCE_LENGTH = 32
private val NONCE_ALPHABET = ('a'..'z') + ('A'..'Z') + ('0'..'9')

/** 32 位随机字母数字（对齐原工程 Nonce 规格）。 */
fun generateNonce(length: Int = NONCE_LENGTH): String = buildString(length) {
    repeat(length) { append(NONCE_ALPHABET[Random.nextInt(NONCE_ALPHABET.size)]) }
}

/**
 * 计算并写入 Timestamp / Nonce / Sign 头。
 * 未启用、密钥缺失或免签路径时不写入（对齐 spec「签名密钥缺失」「登录请求免签」）。
 */
fun HttpRequestBuilder.applyRequestSignature(
    path: String,
    bodyText: String?,
    policy: ApiSignaturePolicy,
    nowEpochSeconds: Long = currentEpochSeconds()
) {
    if (!policy.isEnabled || policy.isUnsignedPath(path)) return
    val timestamp = nowEpochSeconds.toString()
    val nonce = generateNonce()
    val canonical = ApiSignatureEngine.canonicalParamsOf(bodyText)
    val sign = ApiSignatureEngine.sign(policy.apiSecret, timestamp, nonce, canonical)
    header("Timestamp", timestamp)
    header("Nonce", nonce)
    header("Sign", sign)
}

/**
 * 响应验签（mutual 模式）：协议与请求一致，paramsString 为原始响应正文。
 * 验签失败按传输错误失败（对齐原工程 ApiSignatureVerificationException 语义）。
 */
fun verifyResponseSignature(
    policy: ApiSignaturePolicy,
    headers: Headers,
    rawBody: String,
    nowEpochSeconds: Long = currentEpochSeconds()
) {
    if (!policy.verifiesResponses) return
    val sign = headers["Sign"]
    val timestamp = headers["Timestamp"]
    val nonce = headers["Nonce"]
    if (sign.isNullOrBlank() || timestamp.isNullOrBlank() || nonce.isNullOrBlank()) {
        throw NetworkException.Transport(SignatureVerificationException("响应缺少签名头"))
    }
    if (!ApiSignatureEngine.isTimestampValid(timestamp, nowEpochSeconds, policy.maxClockSkewSeconds)) {
        throw NetworkException.Transport(SignatureVerificationException("响应时间戳超出允许的时钟偏差"))
    }
    val expected = ApiSignatureEngine.sign(policy.apiSecret, timestamp, nonce, rawBody)
    if (!ApiSignatureEngine.signaturesMatch(expected, sign)) {
        throw NetworkException.Transport(SignatureVerificationException("响应验签不通过"))
    }
}

/** 响应验签失败原因（对齐原工程 ApiSignatureVerificationException）。 */
class SignatureVerificationException(message: String) : Exception(message)
