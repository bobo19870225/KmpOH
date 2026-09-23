@file:OptIn(kotlinx.cinterop.ExperimentalForeignApi::class)

package com.example.kmpoh.network.bridge

import kotlinx.cinterop.*
import kotlinx.coroutines.CompletableDeferred
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.launch
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock
import kotlin.experimental.ExperimentalNativeApi

/** C 函数指针形态：void (*)(const char* reqId, const char* reqJson)。 */
private typealias PostFn = CFunction<(CPointer<ByteVar>?, CPointer<ByteVar>?) -> Unit>

/** 在 MemScope 上分配 NUL 结尾的 C 字符串（投递函数同步拷贝，作用域结束即释放）。 */
private fun MemScope.cString(text: String): CPointer<ByteVar> {
    val bytes = text.encodeToByteArray()
    val pointer = allocArray<ByteVar>(bytes.size + 1)
    for (index in bytes.indices) {
        pointer[index] = bytes[index]
    }
    pointer[bytes.size] = 0
    return pointer
}

/**
 * 鸿蒙 HTTP 传输桥（Kotlin ↔ ArkTS，手写 NAPI 桥接）。
 *
 * 背景：ktor-network-tls 的 nonJvm 端是 error() 桩（openTLSSession 抛
 * "TLS sessions are not supported on Native platform"），CIO 引擎无法完成 TLS 握手，
 * HTTPS 在 Native 上不可用。故网络请求经 NAPI 桥接到 ArkTS RCP
 * （RemoteCommunicationKit，系统 TLS 栈；对齐 Technician-Harmony 的 RcpSession 方案）。
 *
 * 握手协议（与 harmonyApp/entry/src/main/cpp/napi_init.cpp 对应）：
 * 1. ArkTS 启动时调 `RegisterHttpExecutor(executor)`，C++ 侧把 executor 包成
 *    threadsafe function（Kotlin 任意线程 → JS 线程），并把投递函数指针经
 *    [ohosHttpTransportInit] 交给本对象；
 * 2. [execute] 把请求 JSON 经该函数指针投递给 ArkTS executor（requestId, reqJson）；
 * 3. ArkTS 完成 RCP 请求后调 `nativeApi.HttpBridgeRespond(reqId, respJson)`，
 *    C++ 直接调 [ohosHttpBridgeRespond]，按 requestId 完成挂起的协程。
 *
 * 线程约定：投递函数指针可从任意线程调用（内部走 napi_threadsafe_function）；
 * [ohosHttpBridgeRespond] 在 JS 线程执行，只做 map 摘除 + complete，不做重活。
 */
internal object OhosHttpTransport {

    private val scope = CoroutineScope(SupervisorJob() + Dispatchers.Default)
    private val mutex = Mutex()
    private val pending = mutableMapOf<String, CompletableDeferred<String>>()
    private var nextId = 0L

    // 由 installPostFn 写入一次（启动期，JS 线程），此后只读。
    // 请求发生在登录等用户操作之后，此处的跨线程可见性依赖"启动期写入先于业务读取"。
    private var postFnRaw: COpaquePointer? = null

    val isReady: Boolean get() = postFnRaw != null

    /** 注册投递函数指针（由 [ohosHttpTransportInit] 调用）。 */
    fun installPostFn(postFn: COpaquePointer?) {
        if (postFn != null) {
            postFnRaw = postFn
        }
    }

    /** 投递请求 JSON 给 ArkTS 并挂起等待响应 JSON。 */
    suspend fun execute(requestJson: String): String {
        val post = postFnRaw
            ?: throw IllegalStateException("ArkTS HTTP 桥未注册：Index.ets 需先调 RegisterHttpExecutor")
        val deferred = CompletableDeferred<String>()
        val id = mutex.withLock {
            val mine = nextId++
            val key = mine.toString()
            pending[key] = deferred
            key
        }
        try {
            memScoped {
                post.reinterpret<PostFn>().invoke(cString(id), cString(requestJson))
            }
            return deferred.await()
        } finally {
            mutex.withLock { pending.remove(id) }
        }
    }

    /** ArkTS 侧完成请求后的回传入口（JS 线程）。 */
    fun complete(requestId: String, responseJson: String) {
        scope.launch {
            val deferred = mutex.withLock { pending.remove(requestId) }
            if (deferred == null) {
                // 迟到的响应（协程已取消/超时）：安静丢弃
                return@launch
            }
            deferred.complete(responseJson)
        }
    }
}

/** C++ 侧 RegisterHttpExecutor 时调用：接收投递函数指针（void* → CFunction）。 */
@OptIn(ExperimentalNativeApi::class)
@CName("OhosHttpTransportInit")
fun ohosHttpTransportInit(postFn: COpaquePointer?) {
    OhosHttpTransport.installPostFn(postFn)
}

/** C++ 侧 HttpBridgeRespond 时调用：按 requestId 完成挂起请求。 */
@OptIn(ExperimentalNativeApi::class)
@CName("OhosHttpBridgeRespond")
fun ohosHttpBridgeRespond(requestId: CPointer<ByteVar>?, responseJson: CPointer<ByteVar>?) {
    if (requestId == null || responseJson == null) return
    OhosHttpTransport.complete(requestId.toKString(), responseJson.toKString())
}
