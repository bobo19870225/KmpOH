# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

> 本文档正文使用中文。代码、命令、文件路径、标识符保持原样不翻译。

## 这个仓库是什么

一个 **Kotlin Multiplatform + Compose Multiplatform (CMP)** 应用，可运行在 Android、iOS 和 **鸿蒙 (OHOS)** 上。目前是一个可跑通的 "hello world" 模板（`com.example.kmpoh`），它的使命是成为 **Technician-Android**（虫害防制行业技师服务平台，源码位于 `C:\Users\rain1\Desktop\sop\Technician-Android`）跨端移植的宿主工程。

安卓原工程：Kotlin 2.0.21 + Jetpack Compose + Hilt + Retrofit + Room，371 个 `.kt` 文件，MVVM/MVI 架构，单 Activity + Navigation Compose。业务覆盖登录、首页、工单、SOP 执行、现场示意图画布编辑、NFC、二维码扫描、相机、高德定位、生物识别。

> `Technician-Android/MIGRATION_PLAN.md` 描述的是一条 **KuiklyUI** 迁移路线（KuiklyCompose、`@Page` 注册、`Module` 桥接、`com.tencent.kuikly.*` 包名）。该方案**已被废弃**——本仓库采用标准 KMP + CMP。**不要**照搬该文档中 KuiklyUI 相关的目录结构、命名和技术选型对照表。但它的页面清单与数据层清单作为移植 check-list 仍然有效。

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

`gradlew` 使用 Gradle **8.9**（腾讯镜像）。所有依赖与插件的解析**只走一个私有 Nexus 仓库**（`https://maven.eazytec-cloud.com/nexus/repository/maven-public/`）——没有配置 `mavenCentral()` 和 `google()`。任何新增依赖都必须在该仓库中存在。`gradle/libs.versions.toml` 里带 `-0.3.0` 后缀的版本号（如 `composeMultiplatform = "1.9.2-0.3.0"`、`kotlin = "2.2.21-0.3.0"`）是易特智联的 fork 产物，**不要**把它们"升级"成上游版本。

**做鸿蒙相关的工作时，请使用 `deveco-cli` skill 和 `deveco-mcp` 工具**（`build_project`、`start_app`、`check_ets_files`、`check_cpp_files`、`get_hilog_or_faultlog_recent`、`get_app_ui_tree`、`perform_ui_action`、`harmonyos_knowledge_search`），它们会处理 DevEco 路径、设备选择、日志抓取。`local.properties` 中的 `kmpHarmonyGradleModule`、`harmonyPublishDebugTask`、`harmonyPublishReleaseTask`、`local.deveco.path` 由 IDE / 调式流水线读取——若重命名模块或任务，需同步修改。

测试：`commonTest` 存放跨平台的 `kotlin.test` 测试，目前只有 `ComposeAppCommonTest.kt`。ArkTS 侧在 `harmonyApp/entry/src/test/`（本地单元测试）和 `src/ohosTest/`（hypium 仪器化测试）另有独立测试树。

> ⚠️ `commonTest` 目前**编译不过**：`composeApp/build.gradle.kts` 从未声明 `commonTest` 的依赖，`libs.versions.toml` 里虽有 `kotlin-test` 别名但从未被引用，因此 `ComposeAppCommonTest.kt` 的 `kotlin.test` 无法解析。这是既有缺陷，与业务改动无关。

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

平台抽象用 `expect`/`actual`：`Platform.kt` 声明 `expect fun getPlatform()`，`Platform.android.kt` / `Platform.ios.kt` / `Platform.ohos.kt` 分别 actual。安卓原工程中由 Hilt/Room/Retrofit/MMKV 提供的能力，都改用这套模式。

### 鸿蒙启动链路（Kotlin → ArkTS）

`ohosArm64` 产出的是**动态库**（`binaries.sharedLib { baseName = "kn" }`），不是 framework——所以是 `libkn.so` + `libkn_api.h`，而不是 `ComposeApp.framework`。该 block 里的 `linkerOpts` 存在的意义是：旧的 `libkn.so` 产物可能缺少渲染后端所需的 `DT_NEEDED` 条目——**不要删掉它们**。

排查鸿蒙问题时，按此链路追踪：

1. `ohosMain/.../MainArkUIViewController.kt` —— `@CName("MainArkUIViewController")`，先调 `initMainHandler(env)`，再 `ComposeArkUIViewController(env) { App() }`。导出到 `libkn_api.h`。
2. `harmonyApp/entry/src/main/cpp/napi_init.cpp` —— include `libkn_api.h`，调 `androidx_compose_ui_arkui_init`，并把 `MainArkUIViewController` 注册为 NAPI 模块 **`entry`** 的方法。若导出符号缺失（`libkn.so` 过期 / 头文件不匹配——**API 头文件是提交进仓库的，必然会过期**），错误会在这里或在 `Index.ets` 做 NAPI 查找时暴露。
3. `harmonyApp/entry/src/main/ets/pages/Index.ets` —— 调 `nativeApi.MainArkUIViewController()`，然后渲染 `Compose({ controller, libraryName: 'entry', onBackPressed })`，并把 `onPageShow`/`onPageHide`/`onBackPress` 转发给 controller。

`harmonyApp/entry/src/main/cpp/CMakeLists.txt` 的链接顺序是：先 `libs/arm64-v8a/libkn.so`，**再** `compose::skikobridge`（后者通过 `find_package(compose)` 从 `oh_modules/@cpf-kmp-cmp/compose` 找到）。**顺序不能颠倒。**

### 渲染后端

`gradle.properties` 里选择渲染后端：`rendererBackend=fusion-renderer`（另有注释掉的 `skia` 备选）。当取值为 `fusion-renderer` 时，鸿蒙链接步骤额外需要 `-lnative_drawing -limage_source -lpixelmap -lpixelmap_ndk.z -lnative_window -lace_napi.z -lhilog_ndk.z -lhitrace_ndk.z -luv -lunwind -licu`——这部分已在 `linkerOpts` 中处理。`ohosSkikoVersion` 用于锁定 Skiko fork 版本。

### 资源

CMP 资源放在 `composeApp/src/commonMain/composeResources/`。生成的资源访问包名由工程名推导：`${rootProject.name.lowercase()}.${project.name.lowercase()}.generated.resources` → **`kmpoh.composeapp.generated.resources`**。因此 Kotlin 代码中 `import kmpoh.composeapp.generated.resources.*`，并用 `painterResource(Res.drawable.…)` 引用。**重命名 rootProject 或模块会同时破坏三处**（Kotlin import、生成的 `rawfile` 目录名、以及 `assembledResources` 里的同名层级）。

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

`composeApp/src/ohosMain/cinterop/{resource.def,include/}` 声明了针对 `raw_file_manager.h` / `raw_file.h` 的 cinterop，但**没有任何 Gradle `cinterop` block 引用它**——它是一个死配置。如果确实需要从 Kotlin 访问 rawfile，你必须自己注册 cinterop 配置。

## 移植指引

从 Technician-Android 移植时，以下这些**在 CMP 中没有直接对应方案**，每一项都需要 `expect`/`actual`（或鸿蒙侧 ArkTS 桥接）——请显式规划，不要假设它们能直接搬过来：

| 安卓侧 | 跨端路径 |
|---|---|
| Hilt 依赖注入 | 手写 DI / 服务定位器；Hilt 只能在 JVM 用 |
| Retrofit + OkHttp | `commonMain` 中的 Ktor client |
| Room | SQLDelight |
| DataStore / MMKV | 平台 `expect/actual` 或 ArkTS 存储桥接 |
| Android Keystore | `expect/actual`；鸿蒙侧用 HUKS |
| Coil | CMP `Image` + `compose.components.resources` |
| Navigation Compose | CMP navigation / 自建共享路由 |
| CameraX、ML Kit 扫码、NFC、高德地图、BiometricPrompt | 通过 NAPI 桥接的鸿蒙侧 ArkTS 模块 |

原工程中的 `UiState` sealed class（`Idle`/`Loading`/`Success`/`Empty`/`Error`/`NoPermission`）以及 DTO → Entity → UIModel 的分层设计值得**原样保留**到 `commonMain`——它们是纯 Kotlin，可以无改动迁移。
