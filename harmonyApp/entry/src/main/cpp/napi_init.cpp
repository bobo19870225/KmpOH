#include "libkn_api.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include <rawfile/raw_file_manager.h>
#include <dlfcn.h>

#include <memory>
#include <string>

// 避免工程侧未定义 LOG_DOMAIN 时编译失败
#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0x0000
#endif
#ifndef LOG_TAG
#define LOG_TAG "KmpHttpBridge"
#endif

// ---------------------------------------------------------------------------
// KMP HTTP 桥（与 libkn.so 中 OhosHttpTransport.kt 的 @CName 导出对应）
//
// 背景：ktor-network-tls 的 nonJvm 无 TLS 实现，鸿蒙 HTTPS 必须桥接 ArkTS RCP。
// 协议：
//   1. ArkTS 启动时调 RegisterHttpExecutor(executor)，本文件把 executor 包成
//      threadsafe function（Kotlin 任意线程 → JS 线程），并把 KnPostHttp 函数指针
//      经 OhosHttpTransportInit 交给 Kotlin；
//   2. Kotlin 投递 (reqId, reqJson) → TSFN → ArkTS executor 跑 RCP 请求；
//   3. ArkTS 完成后调 HttpBridgeRespond(reqId, respJson) → 直转
//      OhosHttpBridgeRespond 完成挂起的 Kotlin 协程。
//
// 注意：libkn_api.h 由链接产物生成、提交进仓库后必然过期，故此处对 Kotlin 导出
// 用 extern 手工声明，不依赖该头文件的同步。签名须与生成头文件逐字一致
// （extern "C" + void* 形参），否则头文件刷新后会出现声明冲突。
// ---------------------------------------------------------------------------
extern "C" void OhosHttpTransportInit(void *postFn);
extern "C" void OhosHttpBridgeRespond(void *reqId, void *respJson);

namespace {

struct HttpPayload {
    std::string reqId;
    std::string reqJson;
};

napi_threadsafe_function gHttpTsfn = nullptr;

std::string ToUtf8(napi_env env, napi_value value) {
    size_t len = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &len);
    std::string result(len + 1, '\0');
    // 工程 C++ 标准低于 17：string::data() 是 const，可写缓冲用 &result[0]
    napi_get_value_string_utf8(env, value, &result[0], len + 1, &len);
    result.resize(len);
    return result;
}

// TSFN 的 JS 线程回调：调用注册进来的 ArkTS executor(requestId, reqJson)
void HttpTsfnCallJs(napi_env env, napi_value jsCb, void * /*context*/, void *data) {
    std::unique_ptr<HttpPayload> payload(static_cast<HttpPayload *>(data));
    if (env == nullptr || jsCb == nullptr) {
        return; // 世界正在关闭：丢弃
    }
    napi_value args[2];
    napi_create_string_utf8(env, payload->reqId.c_str(), NAPI_AUTO_LENGTH, &args[0]);
    napi_create_string_utf8(env, payload->reqJson.c_str(), NAPI_AUTO_LENGTH, &args[1]);
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    napi_status status = napi_call_function(env, undefined, jsCb, 2, args, nullptr);
    if (status != napi_ok) {
        OH_LOG_ERROR(LOG_APP, "executor call failed: %{public}d", (int)status);
    }
}

// Kotlin → ArkTS 投递入口（Kotlin 任意线程调用）：拷贝字符串后切回 JS 线程
void KnPostHttp(const char *reqId, const char *reqJson) {
    if (gHttpTsfn == nullptr) {
        OH_LOG_ERROR(LOG_APP, "post before RegisterHttpExecutor");
        return;
    }
    auto *payload = new HttpPayload{reqId ? reqId : "", reqJson ? reqJson : ""};
    napi_status status = napi_call_threadsafe_function(gHttpTsfn, payload, napi_tsfn_nonblocking);
    if (status != napi_ok) {
        delete payload;
        OH_LOG_ERROR(LOG_APP, "tsfn call failed: %{public}d", (int)status);
    }
}

// ArkTS 调：nativeApi.RegisterHttpExecutor(executor: (reqId, reqJson) => void)
napi_value RegisterHttpExecutor(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    napi_valuetype type = napi_undefined;
    if (argc >= 1 && argv[0] != nullptr) {
        napi_typeof(env, argv[0], &type);
    }
    if (argc < 1 || type != napi_function) {
        napi_throw_type_error(env, nullptr, "RegisterHttpExecutor(executor: function) expected");
        return nullptr;
    }
    if (gHttpTsfn != nullptr) {
        return nullptr; // 幂等：重复注册忽略
    }
    napi_value resourceName;
    napi_create_string_utf8(env, "kmpHttpBridge", NAPI_AUTO_LENGTH, &resourceName);
    napi_status status = napi_create_threadsafe_function(env, argv[0], nullptr, resourceName, 0, 1,
                                                         nullptr, nullptr, nullptr, HttpTsfnCallJs,
                                                         &gHttpTsfn);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "napi_create_threadsafe_function failed");
        return nullptr;
    }
    OhosHttpTransportInit(reinterpret_cast<void *>(&KnPostHttp));
    OH_LOG_INFO(LOG_APP, "http executor registered");
    return nullptr;
}

// ArkTS 调：nativeApi.HttpBridgeRespond(reqId: string, respJson: string)
napi_value HttpBridgeRespond(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value argv[2] = {nullptr, nullptr};
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 2) {
        napi_throw_type_error(env, nullptr, "HttpBridgeRespond(reqId: string, respJson: string) expected");
        return nullptr;
    }
    std::string reqId = ToUtf8(env, argv[0]);
    std::string respJson = ToUtf8(env, argv[1]);
    OhosHttpBridgeRespond(const_cast<char *>(reqId.c_str()), const_cast<char *>(respJson.c_str()));
    return nullptr;
}

} // namespace

static napi_value MainArkUIViewController(napi_env env, napi_callback_info info) {
    return reinterpret_cast<napi_value>(MainArkUIViewController(env));
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    androidx_compose_ui_arkui_init(env, exports);
    napi_property_descriptor desc[] = {
        {"MainArkUIViewController", nullptr, MainArkUIViewController, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"RegisterHttpExecutor", nullptr, RegisterHttpExecutor, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"HttpBridgeRespond", nullptr, HttpBridgeRespond, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
