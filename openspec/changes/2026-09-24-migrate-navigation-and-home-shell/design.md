# Design

## Context

动机见 `proposal.md - Why`，可见行为契约见 `specs/ui/navigation/spec.md` 与 `specs/ui/home-shell/spec.md`。本节只记录影响方案的现状与约束。

**安卓原工程形态**（`C:\Users\rain1\Desktop\sop\Technician-Android`，迁移参照）：

- `router/NavGraph.kt`（1792 行）：androidx.navigation **类型安全** API——`AppDestination.*` 路由目标 + `backStackEntry.toRoute<T>()` 参数解析 + `SavedStateHandle` 结果回传（`photo_uris`、`qr_code_result` 等）。起始路由 `AppDestination.Splash`，登录后进主框架。
- `page/main/MainPage.kt`：主框架壳 = `Scaffold` + `NavigationBar` 三项（工单 / 消息 / 我的；DataCenter 项已注释停用），tab 切换是 `remember { mutableIntStateOf(0) }` **壳内状态、不走路由**；内容区分别是 `WorkOrderComposeScreen` / `MessageCenterPage` / `ProfilePage`（`ProfilePage` 提供 `onLogout`、`onNavigateToNfc` 等回调）。另有强制改密 `AlertDialog` 与密码状态刷新逻辑。TopAppBar 已被注释停用。
- `page/home/HomePage.kt` 在主链路中疑似已被 `WorkOrderComposeScreen` 取代（`MainPage` 未引用它），实施时核实；不影响本期占位交付。

**本仓库现状**：`App()` 直接呈现 `LoginPage`，`onLoginSuccess` 是空接缝注释；`AuthSessionManager` 已有登录失效事件流，CLAUDE.md 注明「路由跳转尚未接线」；`LoginViewModel` 等业务容器就位。

**依赖可用性（nexus 实测，2026-09-24）**：`org.jetbrains.androidx.navigation:navigation-compose` 存在 **`ohosArm64` / `ohosX64` 变体**（探测 HTTP 200），fork 适配版本线 `2.10.0-0.1.0-xx`（最新 `-04`），上游线 2.9.x / 2.10.0-alpha/beta 亦在。导航为纯 Compose 状态管理、不触平台 API，无 ktor-TLS 类适配风险。另沿用归档变更实测结论：本仓 **没有** material-icons（core/extended 均无 1.9.x 号），`Icons.Filled.*` 不可用，图标一律自备矢量资源。

## Goals / Non-Goals

**Goals:**

- 建立类型安全路由骨架（`Login` / `Main` 两目标起步），后续业务页面以新增路由目标的方式挂接。
- 登录成功真实跳转主框架，返回栈语义正确（不回登录页）。
- 主框架壳（底部三 tab + 占位内容）可在三端编译、在鸿蒙实机运行，作为业务 tab 的挂载位。
- 登出回流与 401 登录失效回登录页接线闭环。

**Non-Goals:**

- 不迁移任何业务页面内容（工单列表 / 消息 / 我的）。
- 不迁 Splash，不实现自动登录。
- 不做路由深链、多窗口、平行视界适配。
- 不引入 Koin / Hilt 等 DI（壳无业务态，不需要）。

## 决策

### 决策 1：导航选型 CMP navigation-compose（fork 线），否决自建路由

备选「自建轻量路由（sealed class + 自管返回栈）」被否：原工程 1792 行 NavGraph 大量使用 `toRoute<T>()` 参数解析与 `SavedStateHandle` 结果回传，自建意味着把返回栈/参数/回传全部 DIY 并在 12 个页面的迁移期长期维护。CMP navigation 在 nexus 有鸿蒙变体、语义与原工程 1:1 对齐，迁移成本按批次摊薄。版本取 fork 线 `2.10.0-0.1.0-xx`，与 CMP `1.9.2-0.3.0` 的兼容性以 Gradle 解析 + 编译验证为准，不兼容则在该线降号重试并记录。

### 决策 2：路由目标类型安全化，本期只建两条

`AppDestination` 用 `@Serializable` 路由目标（`Login` / `Main` 两条无参目标），对齐原工程命名与 `toRoute<T>()` 使用习惯。后续业务路由逐条新增，本期不预埋空路由。`startDestination = Login`（Splash 未迁；自动登录落地时再评估改起点）。

### 决策 3：tab 切换不进路由

对齐原工程 `MainPage` 的 `selectedTab` 壳内状态。理由：tab 是壳内内容切换而非屏幕导航，进路由会让返回键语义复杂化（tab 切换不应产生返回栈条目），且原工程两侧行为一致。

### 决策 4：401 接线在 `App()` 层消费事件流

`AuthSessionManager` 的登录失效事件已在网络层发出（契约见 `data/http-client`），本次在 `App()` 订阅并导航回 `Login`（清空返回栈）。不把 `NavController` 传入网络层——网络层保持纯传输/信封语义，路由副作用留在 UI 装配层。

### 决策 5：图标自备矢量，色值落 token

底部导航三图标用 `composeResources/drawable/` 自备矢量（`ic_tab_workorder` / `ic_tab_message` / `ic_tab_profile`，命名对齐 `ic_login_*` 惯例），理由见 Context 的 material-icons 实测结论。导航色值（选中 `#1D6F86`、未选 `#AEB6C3`、指示条 `#EAF1F4`）补进 `AppColors`，取自原工程 `MainPage` 常量。

### 决策 6：占位页零状态机

三个 tab 占位内容是静态文案（「xx 模块迁移中」），不建 ViewModel、不引入 `UiState`（六态是为有数据流的页面准备的）。占位专用一个无状态 `MainTabPlaceholder` 组件，业务迁移时整块替换。
