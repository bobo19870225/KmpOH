package com.example.kmpoh.network.signature

import kotlin.math.abs
import kotlin.math.floor
import kotlin.math.sin

/**
 * 纯 Kotlin MD5（RFC 1321）。KMP 公共代码没有 java.security.MessageDigest，
 * 三端共用同一实现（已知向量见单测）。仅用于 API 请求签名，不承担安全哈希职责。
 */
internal fun md5UpperHex(input: String): String =
    md5Digest(input.encodeToByteArray()).joinToString("") { b ->
        (b.toInt() and 0xff).toString(16).padStart(2, '0').uppercase()
    }

internal fun md5Digest(message: ByteArray): ByteArray {
    val k = IntArray(64) { i -> floor(abs(sin(i + 1.0)) * 4294967296.0).toLong().toInt() }
    val s = intArrayOf(
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    )

    var a0 = 0x67452301
    var b0 = 0xefcdab89.toInt()
    var c0 = 0x98badcfe.toInt()
    var d0 = 0x10325476

    val paddedSize = ((message.size + 8) / 64 + 1) * 64
    val padded = ByteArray(paddedSize)
    message.copyInto(padded)
    padded[message.size] = 0x80.toByte()
    var lengthBits = message.size.toLong() * 8
    for (i in 0 until 8) {
        padded[paddedSize - 8 + i] = (lengthBits and 0xff).toByte()
        lengthBits = lengthBits ushr 8
    }

    var offset = 0
    while (offset < paddedSize) {
        val m = IntArray(16)
        for (j in 0 until 16) {
            val i = offset + j * 4
            m[j] = (padded[i].toInt() and 0xff) or
                ((padded[i + 1].toInt() and 0xff) shl 8) or
                ((padded[i + 2].toInt() and 0xff) shl 16) or
                ((padded[i + 3].toInt() and 0xff) shl 24)
        }
        var a = a0
        var b = b0
        var c = c0
        var d = d0
        for (i in 0 until 64) {
            val f: Int
            val g: Int
            when {
                i < 16 -> {
                    f = (b and c) or (b.inv() and d)
                    g = i
                }

                i < 32 -> {
                    f = (d and b) or (d.inv() and c)
                    g = (5 * i + 1) % 16
                }

                i < 48 -> {
                    f = b xor c xor d
                    g = (3 * i + 5) % 16
                }

                else -> {
                    f = c xor (b or d.inv())
                    g = (7 * i) % 16
                }
            }
            val tmp = d
            d = c
            c = b
            val sum = a + f + k[i] + m[g]
            b = b + ((sum shl s[i]) or (sum ushr (32 - s[i])))
            a = tmp
        }
        a0 += a
        b0 += b
        c0 += c
        d0 += d
        offset += 64
    }

    return byteArrayOf(
        (a0 and 0xff).toByte(), ((a0 ushr 8) and 0xff).toByte(),
        ((a0 ushr 16) and 0xff).toByte(), ((a0 ushr 24) and 0xff).toByte(),
        (b0 and 0xff).toByte(), ((b0 ushr 8) and 0xff).toByte(),
        ((b0 ushr 16) and 0xff).toByte(), ((b0 ushr 24) and 0xff).toByte(),
        (c0 and 0xff).toByte(), ((c0 ushr 8) and 0xff).toByte(),
        ((c0 ushr 16) and 0xff).toByte(), ((c0 ushr 24) and 0xff).toByte(),
        (d0 and 0xff).toByte(), ((d0 ushr 8) and 0xff).toByte(),
        ((d0 ushr 16) and 0xff).toByte(), ((d0 ushr 24) and 0xff).toByte()
    )
}

/** 常量时间比较（对齐原工程 MessageDigest.isEqual 语义；大小写不敏感）。 */
internal fun constantTimeEqualsIgnoreCase(expected: String, actual: String): Boolean {
    val x = expected.uppercase().encodeToByteArray()
    val y = actual.uppercase().encodeToByteArray()
    if (x.size != y.size) return false
    var diff = 0
    for (i in x.indices) {
        diff = diff or (x[i].toInt() xor y[i].toInt())
    }
    return diff == 0
}
