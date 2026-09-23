# Proposal

## Why

本仓库是 Technician-Android（371 个 `.kt` 文件）跨端移植的宿主工程，目前 `App()` 仍是 hello world 模板，尚无任何业务代码。登录页是应用的第一道入口，也是所有后续页面的前置依赖——它同时牵出共享 UI 组件层（输入框、按钮、加载视图）与设计 token（颜色/尺寸/字号），这两者会被之后的每一个页面复用。

先把登录页跑通，可以在不引入网络层复杂度的前提下，验证整套跨端 UI 基础设施（CMP 资源、多语言、Android VectorDrawable 迁移、KMP ViewModel）是否真的能在 Android / iOS / 鸿蒙三端工作。这是移植路线上风险最集中、收益最直接的第一步。

## What Changes

- **迁移共享设计系统到 `commonMain`**：`AppColors`、`AppDimens`、`AppFontSize`、`PrimaryButton`、`PrimaryInput`、`LoadingView`、`UiState`。这些均为纯 Compose/Kotlin 实现，不含安卓专有 API，可原样复用。
- **新增登录页 `LoginPage`**：按安卓原工程的视觉与交互重建，包含 Hero 区（eyebrow / 标语 / 服务横幅）、登录卡片（账号、密码、显隐切换、登录按钮）、底部安全提示，以及 Loading 遮罩层。
- **迁移 5 个登录页矢量图标**：`ic_login_iphone`、`ic_login_lock`、`ic_login_shield`、`ic_login_sparkle`、`ic_login_checkmark` 从 Android VectorDrawable XML 迁入 `composeResources/drawable/`。
- **新增多语言字符串资源**：中文落在 `values/strings.xml`（作为默认回退），英文落在 `values-en/strings.xml`。
- **新增 `LoginViewModel`**：迁移原工程的 `phone` / `password` / `loginEnabled` / `uiState` / `toastResId` 状态结构，但状态载体改为**自写纯 Kotlin 容器**（暴露 `StateFlow`，零新依赖），且依赖替换为**本地假实现**，不发起任何网络请求。
- **BREAKING（模板）**：`App()` 由 hello world 模板**直接替换**为 `LoginPage`，移除 `Greeting.kt` 与模板示例资源。调用方 `MainActivity` / `MainViewController` / `MainArkUIViewController` 无需改动。
- **不新增任何依赖**：经实测，官方 KMP `lifecycle` 与 Nexus 中两条 fork 路线均无法同时满足 Android 与鸿蒙两端（详见 `design.md` 决策 1），故状态载体改为自写容器。`StateFlow` 所需的 `kotlinx-coroutines-core` 已由 `compose.runtime` 传递引入，无需显式声明。

**不在本次范围内**：网络请求层（Ktor / Retrofit 替代）、登录接口对接、会话持久化、密码记住功能、页面路由与导航框架、首页等其他页面。

## Capabilities

### New Capabilities

- `ui/design-system`: 跨端共享的 UI 基础层——设计 token（颜色、间距、尺寸、字号）与通用组件（主按钮、主输入框、加载视图），供所有业务页面复用。
- `ui/login`: 登录页的用户可见行为——表单输入与校验反馈、密码显隐切换、登录按钮可用性、加载态呈现、登录结果回调。

### Modified Capabilities

无（`openspec/specs/` 当前为空，本变更为首次建立能力清单）。

## Impact

**新增文件**（`composeApp/src/commonMain/`）：

| 路径 | 说明 |
|---|---|
| `kotlin/com.example.kmpoh/ui/theme/AppColors.kt` | 设计 token：颜色 |
| `kotlin/com.example.kmpoh/ui/theme/AppDimens.kt` | 设计 token：尺寸间距 |
| `kotlin/com.example.kmpoh/ui/theme/AppFontSize.kt` | 设计 token：字号 |
| `kotlin/com.example.kmpoh/ui/components/PrimaryButton.kt` | 主操作按钮 |
| `kotlin/com.example.kmpoh/ui/components/PrimaryInput.kt` | 主输入框 |
| `kotlin/com.example.kmpoh/ui/components/LoadingView.kt` | 统一加载视图 |
| `kotlin/com.example.kmpoh/utils/UiState.kt` | 统一页面状态封装 |
| `kotlin/com.example.kmpoh/page/login/LoginPage.kt` | 登录页 |
| `kotlin/com.example.kmpoh/page/login/LoginViewModel.kt` | 登录页状态 |
| `composeResources/drawable/ic_login_*.xml` | 5 个矢量图标 |
| `composeResources/values/strings.xml` | 中文字符串（默认） |
| `composeResources/values-en/strings.xml` | 英文字符串 |

**修改文件**：
- `composeApp/src/commonMain/kotlin/com.example.kmpoh/App.kt` — 渲染 `LoginPage`

**删除文件**（经检索，两者仅被 `App.kt` 引用，`ComposeAppCommonTest.kt` 与其无关）：
- `composeApp/src/commonMain/kotlin/com.example.kmpoh/Greeting.kt`
- `composeApp/src/commonMain/composeResources/drawable/compose-multiplatform.xml`

**依赖与基础设施影响**：
- **无依赖变更**。`build.gradle.kts` 与 `libs.versions.toml` 均不需改动。
- 流水线 `publishDebugBinariesToHarmonyApp` 会把 `composeResources/` 整体拷入 `harmonyApp/entry/src/main/resources/rawfile/`，新增 `values-en/` 目录会自动随之拷贝，无需改脚本。
- 新增的登录页图标在鸿蒙侧依赖 `rawfile` 资源加载路径正常，本次改动会顺带验证这条链路。
