# Design

## Context

原工程网络层事实（已逐文件核实，详见调研结论）：Retrofit 2.9 + OkHttp 4.12 + kotlinx.serialization 1.7.3，六级拦截器链（网络可达性 → 响应异常归一 → 全局 Loading 计数 → 认证/公共头/401 刷新 → 请求签名 → 脱敏日志）；统一信封 `ApiResponse<T>(code, msg, data)`，`code == 200` 成功，转换层在 `code != 200` 时先把 `data` 归一为空再解码、随后抛 `BusinessApiException(code, msg)`；网络异常为 sealed `NetworkException`（Http/Timeout/Unavailable/Transport/Parsing）；Repository 出口一律 `Result<T>`；Json 配置 `ignoreUnknownKeys + coerceInputValues + explicitNulls=false + encodeDefaults=true`；三环境 baseUrl 经 productFlavors 注入（dev/uat/prod），签名密钥不入库。登录为 `POST mobile/Staff.Login/login`（`staff_code`/`password`/`deviceId`/`platform`），响应兼容 `token`/`access_token` 双字段，token 经 AndroidKeyStore 加密落 DataStore。

本工程现状：三平台 target（android/iosX64|Arm64|SimulatorArm64/ohosArm64），`commonMain` 已有自写 `LoginViewModel`（纯 Kotlin + StateFlow，`uiState: UiState<Unit>` 占位）与 `FakeLoginRepository`（标注待删）；零网络依赖；构建只走私有 Nexus；Windows 环境无法编译 iOS。Kotlin/coroutines/atomicfu 为 `-0.3.0` fork 版本线。动机与范围见 proposal.md。

## Goals / Non-Goals

**Goals:**

- 一套 `commonMain` 网络基建，外部行为契约与原工程对齐（spec 见 `specs/data/http-client/spec.md`），后续业务接口迁移只需新增 API 声明与 DTO。
- 登录真实接通并持久化会话令牌（spec 见 `specs/data/login/spec.md`），整体删除假实现。
- 数据分层（DTO → Entity → UiModel、显式 mapper）与协程/StateFlow 习惯原样延续，为后续页面迁移提供模板。

**Non-Goals:**

- 自动登录、记住密码、退出登录（后续变更）；登录失效后的路由跳转接线（当前无导航框架，仅发事件）。
- 令牌加密存储升级（Keystore/Keychain/HUKS）、Room/SQLDelight、离线队列、七牛上传、HTTP 缓存。
- 其余业务接口（工单、SOP、定位上报、七牛配置等）。

## Decisions

1. **Ktor 版本线取 `io.ktor:*:3.3.3-0.3.0`**。其 POM 依赖 `kotlin-stdlib 2.2.21-0.3.0`、`kotlinx-coroutines-core 1.10.2-0.3.0`、`atomicfu 0.31.0-0.3.0`，与本工程 fork 版本线逐一吻合。备选：`3.3.3-1.1.0-0x` 新线（工具链家族不明，风险大）；上游 `3.6.0`（无 `ohosArm64` 变体，不可用）。
2. **引擎按平台选择，鸿蒙端前置冒烟确认**。Android 用 `ktor-client-okhttp`、iOS 用 `ktor-client-darwin`（均为对应平台惯用引擎）。鸿蒙端 `ktor-client-core-ohosarm64` 的 POM 未声明独立引擎依赖，且 Nexus 中查无 `ktor-client-*-ohosarm64` 引擎 artifact，推测 fork 将引擎实现内置在 core 中；实施第一个任务即为依赖解析 + 引擎冒烟请求，失败则停下来评估备选（等价 CIO fork、或向 fork 维护方提需求）。备选：三端统一纯 Kotlin CIO（Nexus 无 ohos 变体，暂不可行）。
3. **序列化沿用 kotlinx.serialization + ContentNegotiation**，Json 五项配置与原工程逐项一致；信封「失败时 `data` 归一为空再解码」的行为由自定义响应处理实现。备选 Gson/Moshi：原工程未用，且无 ohos 变体。
4. **错误模型原样迁移**：sealed `NetworkException`（五类，各带中文文案）+ `BusinessApiException(businessCode, businessMessage)`；映射集中在响应校验/调用包装一处；Repository 出口 `Result<T>`。备选 Either 或页面级 sealed 出口：偏离原工程调用方习惯，无收益。
5. **拦截器 → 插件映射**（对齐原链顺序与语义）：
   - 网络可达性前置拦截 → **简化不做**（无 NetworkMonitor 的 expect/actual）；离线表现由异常归一化覆盖（连接失败 → Unavailable，带「网络不可用」文案）。行为差异：原工程在请求发出前短断，本实现在传输失败后归一，spec 场景均满足。
   - 响应异常归一（NetworkResponseInterceptor）→ 响应校验 + 调用包装；豁免路径清单（如 PDF 预览）留常量位，本期不实现下载接口。
   - 全局 Loading 计数 → 发送/收尾钩子计数插件；`X-Show-Global-Loading: false` 等价跳过头，发请求前删除。
   - AuthInterceptor → 认证插件：注入 Bearer + 公共头（Platform/Version/DeviceId/X-App-Version/Language/User-Agent 等，取值对齐原工程）；401（HTTP 或 body code）→ 刷新 → 重试一次；`X-Skip-Auth-Refresh` 跳过；并发 401 共享一次刷新（Mutex，对齐原 `@Synchronized`）；刷新成功后同值保存新令牌（对齐原工程 `saveTokens(accessToken = new, refreshToken = new)` 行为）；刷新失败清令牌 + 发出登录失效事件（SharedFlow）。
   - ApiSignatureInterceptor → 签名插件（在认证头写入后计算）：`ApiSignatureEngine` 为纯 Kotlin（MessageDigest MD5 + 参数规范化），原样移植；登录路径免签白名单一致；响应验签（mutual 模式）一并移植。备选：不移植签名（dev 环境若强制签名将联调受阻）。
   - NetworkLoggingInterceptor → `Logging` 插件 + 脱敏过滤（仅 uat/测试环境启用）；脱敏字段集合显式包含令牌/密码/签名（比原工程当前配置更严——原工程只遮蔽 `device-id`，属已知疏漏）。
6. **令牌/设备标识存储：expect/actual 轻量 KV**（用户决策）——`KeyValueStore` 抽象（get/put/remove String），actual 为 Android `SharedPreferences`、iOS `UserDefaults`、鸿蒙 `Preferences`；键名沿用 `auth.access_token` / `auth.refresh_token` / `device.id`。`deviceId` 首次生成 UUID 后持久化。备选：multiplatform-settings 新库（多一个依赖，收益低）；仅内存（不满足重启保持）。安全弱于原工程加密存储，升级列入后续变更。
7. **配置注入**：`composeApp/build.gradle.kts` 读取 `local.properties` 与环境变量，生成 gitignore 的 `GeneratedApiConfig.kt`（含 baseUrl、环境名、签名模式、签名密钥），所有 target 共用；三环境 baseUrl 作为非密常量随仓库提交（与原工程 BuildConfig 取值逐字一致，含 dev 的拼写）。备选：Android `buildConfigField`（iOS/ohos 无 BuildConfig）；密钥入库（违规）。
8. **登录出口分层**：`LoginRequestDto`/`LoginResponseDto`/`UserDto` → 手工组装 `UserEntity` → `UserUiModel`，mapper 显式函数，与原工程一致；`UserUiModel` 的占位字段行为保持（不在本期修正）。`platform` 字段三端分别上报 `android`/`ios`/`ohos`（见 Open Questions）。
9. **接线方式**：`LoginViewModel` 构造参数由 `FakeLoginRepository` 换为真实 `LoginRepository` 接口（`login(): Result<UserUiModel>` 签名不变），`uiState` 负载 `Unit` → `UserUiModel`；页面仅改类型推断处。假实现文件整体删除。

## Risks / Trade-offs

- [鸿蒙引擎 artifact 未定位] → 实施前置冒烟任务立即证伪/证实；失败则停下评估，不带病推进。
- [真实 dev 服务可达性（`tchnician.mobile.local.cn` 疑似内网/拼写保留）] → 联调阶段由用户提供可达地址，uat 为备选；地址可通过配置注入切换，不改代码。
- [后端 `platform` 字段对 ios/ohos 取值可能有白名单校验] → 联调确认；spec 不锁死取值，必要时仅改常量。
- [密码明文 JSON 传输（原工程注释称 MD5、实现为明文）] → 本期对齐实现；与后端确认后如需哈希，仅改登录请求组装一处。
- [令牌明文存平台 KV，弱于原工程加密存储（用户决策）] → 记录在案；加密存储升级为独立后续变更。
- [脱敏比原工程更严，测试环境日志可读性略降] → 接受；原配置未遮蔽令牌/密码属疏漏而非意图。
- [Windows 无法编译 iOS] → 编译验证限 Android/鸿蒙两端；iOS 编译与三端实机联调标注「待用户验证」。

## Migration Plan

1. 依赖与版本线落地（含鸿蒙引擎冒烟）→ 2. 配置注入与 KV/平台 expect-actual → 3. 网络基建（信封、异常、插件）→ 4. 登录数据层（DTO/mapper/repository、token 持久化）→ 5. ViewModel/页面接线并删除假实现 → 6. 三端编译 + 实机联调。

回滚策略：纯代码变更、无数据迁移；新增 KV 键无历史兼容问题，回滚即 git revert。假实现删除后如需回退演示能力，从 git 历史恢复该单文件即可。

## Open Questions

- 后端对 `platform` 字段的取值约定（ios/ohos 是否需映射为既有枚举值）——联调时确认，必要时仅调整常量。
- 登录密码是否需要 MD5 摘要传输（原工程注释与实现不一致）——与后端确认，必要时仅改请求组装。
- dev 环境地址 `https://tchnician.mobile.local.cn/` 的拼写与可达性（照抄原工程）——联调用 uat 兜底。
  > **2026-09-23 联调实测结论**：该地址 DNS 可解析但 TLS 握手被服务端以 `TLSV1_ALERT_UNRECOGNIZED_NAME`（SNI 主机名不识别）拒绝（`SSLHandshakeException <- SSLProtocolException`），即**不存在为该主机名签发的证书/站点**——技术上坐实不可用（拼写是否为笔误仍待与后端确认）。联调已切 uat（`API_ENVIRONMENT=uat`，TLS 正常、curl 200 OK）。
