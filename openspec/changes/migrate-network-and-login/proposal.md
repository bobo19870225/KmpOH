# Proposal

## Why

登录页至今由本地假实现 `FakeLoginRepository` 驱动（文件头注释即写明「接入网络层时整体删除本文件」），网络请求能力是登录接通与后续全部业务迁移（工单、SOP 等）的共同前置条件。原工程网络层已完成逐文件盘点（Retrofit + OkHttp 六拦截器链、`ApiResponse` 信封约定、登录全流程与 token 刷新），且私有 Nexus 已提供与本工程 Kotlin/coroutines 版本线完全对齐的 Ktor 鸿蒙 fork（`io.ktor:*:3.3.3-0.3.0`，其 POM 依赖 `kotlin-stdlib 2.2.21-0.3.0`、`kotlinx-coroutines-core 1.10.2-0.3.0`），迁移条件成熟。

## What Changes

- 新增 `commonMain` Ktor 网络基建：`HttpClient`（30s 超时，对齐原工程）、`ApiResponse` 信封解析与业务码校验（`code != 200` 抛 `BusinessApiException`）、网络异常归一化（`NetworkException`：Http / Timeout / Unavailable / Transport / Parsing）、Repository 出口统一 `Result<T>`。
- 拦截器链 → Ktor 插件映射：认证注入（`Authorization: Bearer` + 公共 Header）与 401 登录失效判定及刷新重试（含 `X-Skip-Auth-Refresh` 跳过机制）、API 请求签名（登录路径免签）、脱敏日志（仅测试环境启用）、全局请求 Loading 计数。
- 登录接通真实接口 `POST mobile/Staff.Login/login`（`staff_code` / `password` / `deviceId` / `platform`），响应兼容 `token` 与 `access_token` 双字段，出口映射 `UserUiModel`。
- token 持久化：`expect`/`actual` 平台 KV（Android `SharedPreferences` / iOS `UserDefaults` / 鸿蒙 `Preferences`），应用重启后登录态保持。
- 环境配置注入：baseUrl（dev / uat / prod 三环境，对齐原工程）、签名模式与签名密钥经 Gradle 从 `local.properties` / 环境变量注入，**密钥不入库**。
- **BREAKING**（工程内部）：删除 `FakeLoginRepository`；`LoginViewModel.uiState` 的负载由 `Unit` 占位替换为真实用户模型 `UserUiModel`。
- 明确不做（后续变更承接）：自动登录 / 记住密码 / 退出登录、token 加密存储升级（Android Keystore / iOS Keychain / 鸿蒙 HUKS）、全局登录失效跳转的路由接线、其余业务接口（工单、SOP、定位上报等）。

## Capabilities

### New Capabilities

- `data/http-client`: 跨端 HTTP API 客户端基建——响应信封与业务码校验、网络异常归一化、认证注入与 401 刷新重试、请求签名、脱敏日志、全局请求计数、环境配置注入。
- `data/login`: 登录数据能力——真实登录请求与结果映射、会话令牌持久化、登录失败文案映射。

### Modified Capabilities

（无。`openspec list --specs` 当前为空；既有变更 `migrate-login-page-ui` 的 `ui/login` 仅覆盖登录页 UI 行为，与本次数据层能力不重叠，无需修改其需求。）

## Impact

- **依赖**（全部须在私有 Nexus 解析验证）：`io.ktor` `3.3.3-0.3.0` 系列（`ktor-client-core`、`ktor-client-content-negotiation`、`ktor-client-logging`、`ktor-client-mock`（测试）及各平台引擎）、`org.jetbrains.kotlinx:kotlinx-serialization-*-0.3.0` 系列。风险：鸿蒙端引擎 artifact 尚未定位（`ktor-client-core-ohosarm64` 的 POM 未声明独立引擎依赖，推测 fork 在 core 内置实现），实施前置任务须做依赖解析 + 引擎冒烟。
- **新增 expect/actual**：平台 KV 存储、平台标识（登录请求 `platform` 字段）、设备标识 `deviceId` 的获取或生成。
- **代码**：删除 `FakeLoginRepository`；`LoginViewModel` / `LoginPage` 小幅接线改动；新增 `network/`、`data/` 相关包（沿用「完整包名做文件夹名」约定）。
- **构建**：`composeApp/build.gradle.kts` 增加配置注入（baseUrl、签名密钥）；`local.properties` 新增未入库配置项。
- **安全注记**：本期 token 与后续「记住密码」落在平台普通 KV（用户决策），弱于原工程 AndroidKeyStore 加密存储；加密升级列入后续变更。
- **环境限制**：iOS 编译验证需 macOS（Windows 不可执行，既有环境限制）；真实 dev 服务联调与实机验证由用户执行。
