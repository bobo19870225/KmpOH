# Tasks

## 1. 依赖与构建基线

- [x] 1.1 修复既有 `commonTest` 缺陷（`composeApp/build.gradle.kts` 从未声明 `commonTest` 测试依赖，`kotlin-test` 别名未被引用），使 JVM 单测可运行，作为本变更各单元验证的载体；验证方式：`./gradlew :composeApp:testDebugUnitTest` 能编译并执行（用例集此时可为空壳），且该修复不引入 Nexus 之外的依赖。
- [x] 1.2 `gradle/libs.versions.toml` 与 `composeApp/build.gradle.kts` 引入 Ktor `3.3.3-0.3.0` 系列（`ktor-client-core`、`ktor-client-content-negotiation`、`ktor-client-logging`、`ktor-client-mock`、Android 引擎 `ktor-client-okhttp`、iOS 引擎 `ktor-client-darwin`）与 kotlinx-serialization 对应 `-0.3.0` 线；验证方式：`./gradlew :composeApp:assembleDebug` 依赖解析全部命中私有 Nexus，无任何 `mavenCentral()/google()` 仓库配置改动。
- [x] 1.3 鸿蒙引擎冒烟（design 决策 2 的前置证伪项）：确认 `ohosArm64` 可构造 HTTP 客户端——`./gradlew :composeApp:linkDebugSharedOhosArm64` 通过，且 `ktor-client-mock` 或最小代码可实例化客户端引擎；若 fork 未在 core 内置引擎导致失败，**停止实施**，按 design 决策 2 评估备选后再继续；验证方式：命令输出与结论记录在任务备注。

  > **备注（结论）**：引擎确为 fork 内置于 `ktor-client-core-ohosArm64`（klib 含 `CIOEngine`/`CIOEngineConfig` 与 nonJvm `Loader`，Nexus 无独立引擎 artifact；`io.ktor.client.engine.cio.CIO` 导入失败但默认引擎装载 `HttpClient(block)` 可用）。`linkDebugSharedOhosArm64` 全链通过，无需停止实施。曾出现的 `Unresolved reference 'cio'` 为显式工厂导入路径问题，非引擎缺失。
- [x] 1.4 实现构建配置注入：`composeApp/build.gradle.kts` 读取 `local.properties` 与环境变量，生成 gitignore 的 `GeneratedApiConfig.kt`（dev/uat/prod 三环境 baseUrl 与原工程逐字一致、环境名、签名模式、签名密钥）；`local.properties` 新增 `API_SIGNATURE_SECRET` 说明注释；验证方式：构建通过且生成文件被 git 忽略，全仓检索确认无任何密钥取值入库（对应 spec「环境配置」）。

## 2. 平台能力 expect/actual

- [x] 2.1 新增 `KeyValueStore` 抽象（get/put/remove）与三端 actual：Android `SharedPreferences`、iOS `UserDefaults`、鸿蒙 `Preferences`；验证方式：`assembleDebug` 与 `linkDebugSharedOhosArm64` 编译通过，且键名常量沿用 `auth.access_token` / `auth.refresh_token` / `device.id`。
- [x] 2.2 新增平台标识与设备标识 expect/actual：`platform` 常量（`android`/`ios`/`ohos`，见开放问题，联调确认后可仅调常量）与 `deviceId`（首次生成 UUID 并持久化，之后稳定读取）；验证方式：两 target 编译通过，且 JVM 单测覆盖「首次生成后稳定读取」逻辑（存储用 fake 实现）。

## 3. 网络基建（data/http-client）

- [x] 3.1 新增错误模型与信封：`ApiResponse<T>(code, msg, data)`、`BusinessApiException(businessCode, businessMessage)`、sealed `NetworkException`（Http/Timeout/Unavailable/Transport/Parsing，各带中文文案常量）；Json 五项配置与原工程一致（`ignoreUnknownKeys`、`coerceInputValues`、`explicitNulls=false`、`encodeDefaults=true`）；验证方式：编译通过 + JVM 单测覆盖五类异常文案取值（对应 spec「网络异常归一化」）。
- [x] 3.2 实现 HTTP 客户端工厂与信封处理：30s 超时；`code==200` 取 `data`、`code!=200` 时先把 `data` 归一为空再解码并抛 `BusinessApiException`；底层异常归一为 `NetworkException` 五类；Repository 出口统一 `Result<T>`；验证方式：`ktor-client-mock` JVM 单测覆盖 spec 场景——业务成功取数、业务失败携带服务端 msg、失败信封异常 data 结构不致解析错误、超时/不可达/解析失败/HTTP 状态错误的归一化（对应 spec「统一响应信封与业务码校验」「网络异常归一化」）。
- [x] 3.3 实现认证插件：注入 `Authorization: Bearer` 与公共请求头（Platform/Version/DeviceId/X-App-Version/Language/User-Agent 等，取值对齐原工程）；401（HTTP 或 body code 401）→ 刷新令牌 → 重试原请求一次；刷新用空 body POST + token 头、成功后同值保存新令牌；并发 401 经 Mutex 共享一次刷新；刷新失败清令牌并经 SharedFlow 发出「登录已失效」事件；`X-Skip-Auth-Refresh`、登录与刷新请求不触发刷新；验证方式：`ktor-client-mock` JVM 单测覆盖 spec 四个场景（注入、刷新重试成功、刷新失败清令牌发事件、登录请求不触发刷新）。
- [x] 3.4 实现签名插件：移植 `ApiSignatureEngine`（MD5 大写十六进制、`密钥+时间戳+随机串+规范化参数+密钥`、规范化参数按 key 字典序并剔除签名/时间戳/随机串/file/空值）、登录路径免签白名单、`Timestamp`/`Nonce`/`Sign` 头（在认证头写入后计算）、密钥缺失时关闭签名并在测试环境日志告警、mutual 模式响应验签（常量时间比较）；验证方式：JVM 单测用固定输入向量断言签名值与规范化结果（对应 spec「请求签名」）。
- [x] 3.5 实现日志脱敏与全局请求计数插件：仅测试环境输出网络日志（体裁剪 8KB），令牌/密码/签名等敏感字段遮蔽；请求计数（带跳过头 `X-Show-Global-Loading: false` 的请求不计入、结束必回落）；验证方式：JVM 单测覆盖「并发计数正确回落」「跳过标记不计数」，日志脱敏以单测断言遮蔽输出（对应 spec「请求日志与脱敏」「全局请求计数」）。

## 4. 登录数据层（data/login）

- [x] 4.1 新增登录 DTO 与分层模型：`LoginRequestDto(staff_code, password, deviceId, platform)`、`LoginResponseDto`（`token`/`access_token` 双字段、`refresh_token`、`user_id`、`name` 等，SerialName 对齐原工程）、`UserDto`；组装 `UserEntity` → `UserUiModel` 的显式 mapper；验证方式：编译通过 + JVM 单测覆盖 mapper 与「token 为空取 access_token、refresh_token 为空兜底 access」取值规则。
- [x] 4.2 新增真实 `LoginRepository`（接口 + 实现）：`login(staffCode, password): Result<UserUiModel>`——组包（deviceId/platform 由 expect/actual 提供，密码按现状 JSON 原样传输，见开放问题）、成功持久化令牌并返回用户模型、失败按「服务端 msg → 网络类别文案 → 通用兜底」映射文案；验证方式：`ktor-client-mock` JVM 单测覆盖 spec 场景（登录成功返回用户模型并持久化、令牌字段兼容、业务失败不写令牌且文案为服务端 msg、超时文案、未知错误兜底）。
- [x] 4.3 接线与清理：`LoginViewModel` 构造依赖替换为真实 repository、`uiState` 负载 `Unit` → `UserUiModel`；`LoginPage` 相应类型调整；**整体删除 `FakeLoginRepository.kt`**；验证方式：`assembleDebug` 编译通过，全仓检索 `FakeLoginRepository` 无残留。

## 5. 三端编译与静态检查

- [x] 5.1 编译门禁全绿：`./gradlew :composeApp:assembleDebug`、`./gradlew :composeApp:publishDebugBinariesToHarmonyApp`、`assembleHap`（entry@default）、`check_ets_files`（若涉及 ets）、`./gradlew :composeApp:testDebugUnitTest`；验证方式：各命令输出为成功（iOS 编译见 6.5，本机 Windows 不可执行）。

  > **备注**：gradle 三任务 `BUILD SUCCESSFUL`；`assembleHap` exit 0；本次变更未涉及 ets 改动，`check_ets_files` 免检。

## 6. 联调与实机验证（待用户验证，实施方不勾选）

- [ ] 6.1 【待用户验证】真实登录成功：实机以有效员工编号/密码登录 dev（或 uat）服务，得到用户模型进入后续页面；顺带确认 `platform` 字段取值是否被服务端接受（开放问题 1，不符则仅调常量）。
- [ ] 6.2 【待用户验证】登录失败文案：以错误密码登录，页面提示为服务端 `msg` 文案（对应 spec「登录失败文案映射」场景）。
- [ ] 6.3 【待用户验证】网络异常文案：断网/超时条件下登录，页面提示分别为「网络不可用」「请求超时」类别文案。
- [ ] 6.4 【待用户验证】令牌持久化：登录成功后杀进程重启，确认仍可读到令牌（本期不做自动登录跳转，仅验证持久化）。
- [ ] 6.5 【待用户验证】iOS 编译与三端冒烟：macOS 上执行 `linkDebugFrameworkIosSimulatorArm64`（或 Xcode 构建）并三端启动登录页（Windows 环境限制，本机不可执行）。
- [ ] 6.6 【待用户验证/待确认】签名联调（若目标环境强制签名）：确认 `Sign` 头通过服务端验签；与后端确认密码是否需 MD5 摘要（开放问题 2）与 dev 地址拼写/可达性（开放问题 3），结论回填 design.md 的 Open Questions。
