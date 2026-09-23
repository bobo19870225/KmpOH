# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

> 本文档正文使用中文。代码、命令、文件路径、标识符保持原样不翻译。

## 写代码前先查 CPF-KMP-CMP 开发文档

本工程基于 **CPF-KMP-CMP**（KMP + CMP 的鸿蒙适配框架）。**动手写代码前务必先弄清开发文档**，可以避免不必要的弯路：

- 文档目录：<https://atomgit.com/CPF-KMP-CMP/docs/blob/main-2.2/zh-cn/%E7%9B%AE%E5%BD%95.md>（分支 `main-2.2`，与本工程 Kotlin 2.2.21 / CMP 1.9.2 对应）
- 与本工程最相关的章节：
  - **深入开发/三方库** —— 鸿蒙可用三方库清单与推荐版本（接新库前必查，只有"已适配"库能用）
  - **深入开发/三方库示例** —— 常用库集成示例（CPF-KMP-CMP/kmp-thirdlibdemo 仓库）
  - **深入开发/跨语言调用用户手册** —— ArkTS ↔ Kotlin/Native 互操作（FFI）
  - **UI开发/CMP 自渲染 / 统一渲染用户手册** —— 渲染后端行为差异
  - **faqs/** —— 编译构建、渲染、FFI、三方库的官方排障
- 抓取方式：atomgit 页面是 SPA，WebFetch 会取不到正文。用 raw API 按路径取原文：
  ```
  curl -sL "https://atomgit.com/api/v5/repos/CPF-KMP-CMP/docs/raw/zh-cn/<路径>?ref=main-2.2"
  # 例：zh-cn/深入开发/三方库.md
  ```

三方库版本号形如 `3.3.3-1.0.0`、`1.9.1-0.3.0` 的后缀是**鸿蒙化适配版本**（上游版本-适配版本），不是上游版本。接库前查文档"推荐使用"列取版本；`gradle/libs.versions.toml` 里 kotlin = `2.2.21-0.3.0`、composeMultiplatform = `1.9.2-0.3.0` 是易特智联的 fork 产物，**不要**把它们"升级"成上游版本。

## 这个仓库是什么

一个 **Kotlin Multiplatform + Compose Multiplatform (CMP)** 应用，可运行在 Android、iOS 和 **鸿蒙 (OHOS)** 上。它是 **Technician-Android**（虫害防制行业技师服务平台，源码位于 `C:\Users\rain1\Desktop\sop\Technician-Android`）跨端移植的宿主工程。当前进度：登录页与网络请求封装已迁移完毕（`App()` 直接呈现 `LoginPage`）；后续按 openspec 变更继续移植工单、SOP 等业务。

安卓原工程：Kotlin 2.0.21 + Jetpack Compose + Hilt + Retrofit + Room，371 个 `.kt` 文件，MVVM/MVI 架构，单 Activity + Navigation Compose。业务覆盖登录、首页、工单、SOP 执行、现场示意图画布编辑、NFC、二维码扫描、相机、高德定位、生物识别。

变更管理用 **OpenSpec**（`openspec/`，spec-driven，工件一律简体中文）：`openspec/specs/data/` 存能力规格（已有 `http-client`、`login`），`openspec/changes/` 存进行中变更，归档在 `changes/archive/`。设计决策记录在各变更的 `design.md`（网络层与登录接口的关键决策见 `openspec/changes/archive/2026-09-23-migrate-network-and-login/design.md`）。

## 两套构建系统，同一个仓库

这是本仓库结构上最重要的事实：

- **`:composeApp`** —— 唯一的 Gradle 模块（`settings.gradle.kts` 只 include 了它）。所有 Kotlin/CMP 代码在这里，产出 Android APK、iOS framework，以及鸿蒙用的 `libkn.so`。
- **`harmonyApp/`** —— 一个**独立的 hvigor/ohpm 工程**（DevEco Studio），**不在** Gradle settings 中，Gradle 永远不会构建它。Gradle 只负责把产物**拷贝进去**。

两者之间的桥梁是 `composeApp/build.gradle.kts` 里的拷贝任务：

```
./gradlew :composeApp:publishDebugBinariesToHarmonyApp   # 或 publishReleaseBinariesToHarmonyApp
```

它依赖 `linkDebugSharedOhosArm64`，并拷贝：

- `build/bin/ohosArm64/debugShared/libkn.so` → `harmonyApp/entry/libs/arm64-v8a/`
- `.../libkn_api.h` → `harmonyApp/entry/src/main/cpp/include/arm64-v8a/`
- `build/generated/compose/resourceGenerator/assembledResources/ohosArm64Main/composeResources/` → `harmonyApp/entry/src/main/resources/rawfile/composeResources/`（**已装配**产物，含编译后的 `.cvr`；不要改成拷 `src/commonMain/composeResources` 源码，原因见「资源」一节）

目标目录可用 `-PharmonyAppPath=<path>` 覆盖。

## 常用命令

```bash
# Android
./gradlew :composeApp:assembleDebug          # 打 APK
./gradlew :composeApp:testDebugUnitTest      # 在 JVM 上跑 commonTest + android 单元测试
./gradlew :composeApp:testDebugUnitTest --tests "com.example.kmpoh.network.ApiCallTest"   # 跑单个测试类

# 鸿蒙：交叉编译 Kotlin → libkn.so 并发布到 harmonyApp/
./gradlew :composeApp:publishDebugBinariesToHarmonyApp

# 鸿蒙：完整流水线（Gradle 发布 → ohpm install → hvigor assembleHap → hdc 安装 → aa start）
./runscript/runOhosApp-Win.bat            # Windows；macOS 用 runOhosApp-Mac.sh
./runscript/runOhosApp-Win.bat -m release            # release 构建
./runscript/runOhosApp-Win.bat -b com.example.harmonyapp -a EntryAbility
./runscript/runOhosApp-Win.bat -p D:\path\to\other\harmonyApp   # 指向外部 OHOS 工程

# 直接调 hvigor（在 harmonyApp/ 目录下执行）
ohpm install --all
node "%DEVECO_PATH%\tools\hvigor\bin\hvigorw.js" --mode module -p module=entry@default \
  -p product=default -p buildMode=debug -p requiredDeviceType=phone assembleHap
```

`gradlew` 使用 Gradle **8.9**（腾讯镜像）。所有依赖与插件的解析**只走一个私有 Nexus 仓库**（`https://maven.eazytec-cloud.com/nexus/repository/maven-public/`）——没有配置 `mavenCentral()` 和 `google()`。任何新增依赖都必须在该仓库中存在。

**做鸿蒙相关的工作时，请使用 `deveco-cli` skill 和 `deveco-mcp` 工具**（`build_project`、`start_app`、`check_ets_files`、`check_cpp_files`、`get_hilog_or_faultlog_recent`、`get_app_ui_tree`、`perform_ui_action`、`harmonyos_knowledge_search`），它们会处理 DevEco 路径、设备选择、日志抓取。`local.properties` 中的 `kmpHarmonyGradleModule`、`harmonyPublishDebugTask`、`harmonyPublishReleaseTask`、`local.deveco.path` 由 IDE / 调式流水线读取——若重命名模块或任务，需同步修改。

测试：`commonTest` 存放跨平台的 `kotlin.test` 测试（网络信封、签名、映射、存储、日志脱敏等），依赖 `kotlin-test` 与 `ktor-client-mock`，经 `testDebugUnitTest` 在 JVM 执行。ArkTS 侧在 `harmonyApp/entry/src/test/`（本地单元测试）和 `src/ohosTest/`（hypium 仪器化测试）另有独立测试树。

## 验证由用户负责，不要自己跑设备

**运行期验证一律由用户本人执行**——这是用户的明确要求。代码写完、编译通过后就停下，把「待用户验证」清单交出去，不要自己动手去设备上确认。

- **可以做**：编译与构建（`assembleDebug`、`linkDebugSharedOhosArm64`、`publish*BinariesToHarmonyApp`、`assembleHap` 等）、静态检查（`check_ets_files`、`check_cpp_files`）、依赖解析查询。这些是确认代码可编译的必要步骤，属于实现的一部分。
- **不要做**：启动模拟器或真机（`emulator.exe -start`、`deveco-mcp` 的 `start_app`）、截图与模拟输入（`perform_ui_action`、`adb input tap/text`、`screencap`）、抓设备日志（`get_hilog_or_faultlog_recent`、`logcat`）、读取设备 UI 树（`get_app_ui_tree`），以及为跑通上述动作而临时改代码或写一次性脚本。
- 上面「做鸿蒙相关的工作时用 `deveco-cli` / `deveco-mcp`」那条，**仅限于构建、静态检查与文档检索**这类不接触设备的用法；其中列出的 `start_app`、`get_hilog_or_faultlog_recent`、`get_app_ui_tree`、`perform_ui_action` 属于运行期验证，不要用。
- 写 OpenSpec 变更的 `tasks.md` 时，运行期验证类任务（实机运行、视觉比对、多语言实机确认等）**不要自己勾选完成**，标注为「待用户验证」交出去。
- 顺带：若环境本身就是障碍（如 Windows 无法编译 iOS、x86_64 鸿蒙模拟器跑不了只构建 arm64 的工程），如实说明并标注为阻塞即可，不要为了绕过环境限制去改构建配置。

## 架构

### 目标平台与 source set

`composeApp/build.gradle.kts` 中声明的 target：`androidTarget`、`iosX64`/`iosArm64`/`iosSimulatorArm64`（framework 名 `ComposeApp`，static）、以及 `ohosArm64`。

`iosMain` 和 `ohosMain` 是**手工创建**的 source set（`sourceSets.create(...)`），`dependsOn(commonMain)` 也是手工接的——iOS 还需要把 `iosX64Main`/`iosArm64Main`/`iosSimulatorArm64Main` 分别重新指向 `iosMain`。新增平台意味着要复制这一整套接线。

Kotlin 源码目录**直接用完整包名做文件夹名**——`src/commonMain/kotlin/com.example.kmpoh/`（带点，**不是**嵌套的 `com/example/kmpoh/`），代码里 `package com.example.kmpoh`。新增文件时请沿用这个约定。

平台抽象用 `expect`/`actual`：`Platform.kt`、`HttpEngine.kt`、`storage/KeyValueStore.kt`、`storage/DeviceIdentity.kt`、`logger/Logger.kt`（`platformLogLine`）、`network/signature/CurrentTime` 等均按此模式。安卓原工程中由 Hilt/Room/Retrofit/MMKV 提供的能力，都改用这套模式。

### 分层结构（登录链路为样板，后续页面照此扩展）

自上而下（`openspec/specs/data/` 有对应能力规格）：

- **UI 层** `page/login/` + `ui/` —— `LoginPage`（纯 Compose）+ `LoginViewModel`（纯 Kotlin + `StateFlow`，自写状态容器，**不引入** lifecycle-viewmodel 多平台库——实测 fork 路线无法两端兼顾，见 archive 变更 design.md 决策 1）。`ui/theme/` 是设计 token（`AppColors`/`AppDimens`/`AppFontSize`），`ui/components/` 是复用组件（`PrimaryButton`/`PrimaryInput`/`LoadingView`）。页面状态统一走 `utils/UiState.kt` 的六态：`Idle`/`Loading`/`Success`/`Empty`/`Error`/`NoPermission`，**严禁页面自定义状态枚举**。
- **数据层** `data/` —— DTO → Entity → UIModel 分层 + mapper（`data/model/{dto,entity,ui,mapper}`），`data/repository/LoginRepository` 调网络层。这套分层自原工程**原样保留**，新业务照此建模。
- **网络层** `network/` —— Ktor 封装（详见下节）。
- **存储** `storage/` —— `KeyValueStore` 接口 + `expect fun createKeyValueStore()`：Android = SharedPreferences、iOS = NSUserDefaults、鸿蒙 = Native Preferences（cinterop `platform.ArkData.Preferences` 直调 libohpreferences）。本期为普通 KV，弱于原工程 AndroidKeyStore 加密（升级列入后续变更）。`getOrCreateDeviceId` 首次生成 UUID 并持久化。
- **日志** `logger/` —— `Logger`（迁移自原工程）：`debugSingleLine` 分片、`debugJson` 按 JSON 边界分片、`sanitize` 敏感脱敏；**仅非 prod 环境输出**（`GeneratedApiConfig.ENVIRONMENT != "prod"`），平台出口 `platformLogLine`（Android=logcat、iOS/鸿蒙=stdout）。

### 网络层（Ktor）

引擎按平台拆分（`network/HttpEngine.kt` 的 `expect fun createPlatformHttpClient`）：

| 平台 | 引擎 | 依赖位置 |
|---|---|---|
| Android | OkHttp | `androidMain.dependencies` |
| iOS | Darwin | `iosMain.dependencies` |
| 鸿蒙 | **ktor-client-cio** 的 `io.ktor.client.engine.cio.CIO` | `ohosMain.dependencies` |

两个实测踩过的坑（**不要退回**）：

1. 鸿蒙端**不能**用无参 `HttpClient()`——引擎服务发现不可用，抛 `Failed to find HTTP client engine implementation`。必须显式传引擎工厂。
2. 鸿蒙端引擎必须是独立工件 `io.ktor:ktor-client-cio`（官方三方库文档"已适配"，含 `ohosarm64` 变体）。**不要**用 `ktor-client-core` 内置的 `io.ktor.client.utils.CIO` 替代品（功能不完整，请求异常），也不要信"引擎内置、无需依赖"的旧注释。

Ktor 全家取 `3.3.3-1.0.0` 适配线（三方库文档对 KMP 2.2.21 & CMP 1.9.2 的推荐版本）；其 POM 对齐 `kotlinx-coroutines 1.10.2-0.3.0` / `kotlinx-serialization 1.9.1-0.3.0`，这两项保持 `-0.3.0` 不动。

调用链（对齐原工程语义，关键决策见 archive 变更 design.md）：

1. `HttpClientFactory.createApiClient()` —— 装配 ContentNegotiation(`ApiJson`) + HttpTimeout(30s) + 脱敏网络日志。
2. `network/ApiCall.kt` 的 `callEnvelope` —— **信封解析与异常归一的唯一出口**：`code == 200` 返回 `data`；`code != 200` 抛 `BusinessApiException`；非 2xx 抛 `NetworkException.Http`；传输/解析失败归一为 `NetworkException`。
3. `network/ApiGateway.kt` —— 认证头写入、`postJson` 便捷入口、**401/业务码 401 的刷新令牌重试编排**（`PATH_LOGIN`/`PATH_REFRESH_TOKEN` 免重试），登录失效发 `AuthSessionEvent.LoginExpired`。
4. `network/signature/` —— 请求签名/响应验签（Timestamp/Nonce/Sign 头，MD5）：模式 `off|request|mutual`，登录路径免签、PDF 预览路径免验响应签、密钥缺失视为整体关闭。`currentEpochSeconds` 为 expect/actual。
5. `network/AuthSessionManager.kt` —— 令牌读写（存 `KeyValueStore`，键名见 `StorageKeys`）+ 登录失效事件流。路由跳转尚未接线。
6. `network/NetworkRequestTracker.kt` / `NetworkLogging.kt` —— 全局 loading 计数与脱敏日志插件。

**API 配置是构建期注入的**：`generateApiConfig` 任务把 `GeneratedApiConfig`（`ENVIRONMENT`/`BASE_URL`/`SIGNATURE_MODE`/`API_SIGNATURE_SECRET`/`SIGNATURE_MAX_CLOCK_SKEW_SECONDS`）生成到 `build/generated/apiConfig/`（不入库）并挂进 `commonMain` 源集。取值优先级：环境变量 > `local.properties` > 默认值；密钥只经 `API_SIGNATURE_SECRET` 注入，**不入库**。三环境地址与原工程 productFlavors 逐字一致（dev 拼写 `tchnician.mobile.local.cn` 是原样保留的）。新增配置项要同步改 `generateApiConfig` 与各读取点。

### 鸿蒙启动链路（Kotlin → ArkTS）

`ohosArm64` 产出的是**动态库**（`binaries.sharedLib { baseName = "kn" }`），不是 framework——所以是 `libkn.so` + `libkn_api.h`，而不是 `ComposeApp.framework`。该 block 里的 `linkerOpts` 存在的意义是：旧的 `libkn.so` 产物可能缺少渲染后端所需的 `DT_NEEDED` 条目——**不要删掉它们**（含存储用的 `--no-as-needed -lohpreferences --as-needed`，弱导入不触发 as-needed 保留，缺了会在库初始化抛 `FileFailedToInitializeException` 启动即崩）。

排查鸿蒙问题时，按此链路追踪：

1. `ohosMain/.../MainArkUIViewController.kt` —— `@CName("MainArkUIViewController")`，先调 `initMainHandler(env)`，再 `ComposeArkUIViewController(env) { App() }`。导出到 `libkn_api.h`。
2. `harmonyApp/entry/src/main/cpp/napi_init.cpp` —— include `libkn_api.h`，调 `androidx_compose_ui_arkui_init`，并把 `MainArkUIViewController` 注册为 NAPI 模块 **`entry`** 的方法。若导出符号缺失（`libkn.so` 过期 / 头文件不匹配——**API 头文件是提交进仓库的，必然会过期**），错误会在这里或在 `Index.ets` 做 NAPI 查找时暴露。
3. `harmonyApp/entry/src/main/ets/pages/Index.ets` —— 调 `nativeApi.MainArkUIViewController()`，然后渲染 `Compose({ controller, libraryName: 'entry', onBackPressed })`，并把 `onPageShow`/`onPageHide`/`onBackPress` 转发给 controller。

`harmonyApp/entry/src/main/cpp/CMakeLists.txt` 的链接顺序是：先 `libs/arm64-v8a/libkn.so`，**再** `compose::skikobridge`（后者通过 `find_package(compose)` 从 `oh_modules/@cpf-kmp-cmp/compose` 找到）。**顺序不能颠倒。**

### 渲染后端

`gradle.properties` 里选择渲染后端：`rendererBackend=fusion-renderer`（另有注释掉的 `skia` 备选）。当取值为 `fusion-renderer` 时，鸿蒙链接步骤额外需要 `-lnative_drawing -limage_source -lpixelmap -lpixelmap_ndk.z -lnative_window -lace_napi.z -lhilog_ndk.z -lhitrace_ndk.z -luv -lunwind -licu`——这部分已在 `linkerOpts` 中处理。`ohosSkikoVersion` 用于锁定 Skiko fork 版本。

### 资源

CMP 资源放在 `composeApp/src/commonMain/composeResources/`。生成的资源访问包名由工程名推导：`${rootProject.name.lowercase()}.${project.name.lowercase()}.generated.resources` → **`kmpoh.composeapp.generated.resources`**。因此 Kotlin 代码中 `import kmpoh.composeapp.generated.resources.*`，并用 `painterResource(Res.drawable.…)` 引用。**重命名 rootProject 或模块会同时破坏三处**（Kotlin import、生成的 `rawfile` 目录名、以及 `assembledResources` 里的同名层级）。

多语言：中文落 `values/strings.xml`（**默认回退**）、英文落 `values-en/strings.xml`，键名沿用原工程 `str_*`；新增字符串两套都要加且键名集合一致。

**鸿蒙端必须拷贝「已装配」产物，不能拷源码目录**（这条踩过坑）：

```
✅ composeApp/build/generated/compose/resourceGenerator/assembledResources/ohosArm64Main/composeResources/
❌ composeApp/src/commonMain/composeResources/          ← 只拷源码会启动即崩
```

原因：**drawable 的源码 XML 可以直接用，但字符串资源必须先由 Compose 插件编译成 `.cvr`**。运行时读的是 `values/strings.commonMain.cvr`，源码目录里只有 `values/strings.xml`。只拷源码会让鸿蒙端启动即抛：

```
kotlin.IllegalArgumentException: Failed to open raw file:
composeResources/kmpoh.composeapp.generated.resources/values/strings.commonMain.cvr
```

`assembledResources/ohosArm64Main/composeResources/` 由 `assembleOhosArm64MainResources` 产出，其**内部已自带 `kmpoh.composeapp.generated.resources` 这一层**，所以 `publish*BinariesToHarmonyApp` 直接落到 `rawfile/composeResources/` 即可，不要再手工拼包名。该拷贝任务已声明对 `assembleOhosArm64MainResources` 的依赖。

注意拷贝用的是 `DuplicatesStrategy.INCLUDE` 且**从不清理目标目录**：删掉某个资源后，旧的副本会一直留在 `harmonyApp/entry/src/main/resources/rawfile/` 里，需要手工删除。

### 一处未被启用的配置

`composeApp/src/ohosMain/cinterop/{resource.def,include/}` 声明了针对 `raw_file_manager.h` / `raw_file.h` 的 cinterop，但**没有任何 Gradle `cinterop` block 引用它**——它是一个死配置。如果确实需要从 Kotlin 访问 rawfile，你必须自己注册 cinterop 配置。（`platform.ArkData.Preferences` 的 cinterop 是工具链内置的，与此无关。）

## 移植指引

从 Technician-Android 移植时，以下这些**在 CMP 中没有直接对应方案**，每一项都需要 `expect`/`actual`（或鸿蒙侧 ArkTS 桥接）——请显式规划，不要假设它们能直接搬过来：

| 安卓侧 | 跨端路径 |
|---|---|
| Hilt 依赖注入 | 手写 DI / 服务定位器；Hilt 只能在 JVM 用 |
| Retrofit + OkHttp | `commonMain` 中的 Ktor client（已有封装，见「网络层」） |
| Room | SQLDelight |
| DataStore / MMKV | `KeyValueStore`（已有）或 ArkTS 存储桥接 |
| Android Keystore | `expect`/`actual`；鸿蒙侧用 HUKS |
| Coil | CMP `Image` + `compose.components.resources` |
| Navigation Compose | CMP navigation / 自建共享路由 |
| CameraX、ML Kit 扫码、NFC、高德地图、BiometricPrompt | 通过 NAPI 桥接的鸿蒙侧 ArkTS 模块 |

原工程中的 `UiState` sealed class 以及 DTO → Entity → UIModel 的分层设计**原样保留**在 `commonMain`——它们是纯 Kotlin，可无改动迁移。接入新三方库前先查「三方库」文档确认鸿蒙已适配，并按其推荐版本线取号。
