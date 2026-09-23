import { ArkUIViewController } from "compose/src/main/cpp/types/libcompose_arkui_utils";

export const MainArkUIViewController: () => ArkUIViewController

/** 注册 KMP HTTP 传输执行器（Index.ets 启动时调用，幂等）。executor 在 JS 线程收到 (reqId, reqJson)。 */
export const RegisterHttpExecutor: (executor: (requestId: string, reqJson: string) => void) => void

/** ArkTS 完成 RCP 请求后把响应回传给 Kotlin（HttpBridge.ets 调用）。 */
export const HttpBridgeRespond: (requestId: string, respJson: string) => void
