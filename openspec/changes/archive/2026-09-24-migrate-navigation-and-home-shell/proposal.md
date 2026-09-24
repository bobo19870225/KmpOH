# Proposal

## Why

登录页已在三端跑通（见归档变更 `2026-09-24-migrate-login-page-ui`、`2026-09-23-migrate-network-and-login`），但 `App()` 里登录成功仍停留在空接缝注释（「下一步引入路由后，在此跳转技师工作台」），登录后哪里也去不了。原工程是单 Activity + Navigation Compose 的多页面应用（12 个页面模块、`NavGraph.kt` 1792 行类型安全路由图），后续要渐进迁移工单、消息、我的等业务——没有导航框架，每个页面都没有挂载点。

本次先搭「导航框架 + 首页壳」：建立路由骨架与登录成功跳转，让登录后的应用有去处；主框架（底部三 tab）以占位内容交付，业务内容由后续变更各自立项填充。这是渐进迁移路线的地基。

## What Changes

- **引入 CMP navigation-compose（fork 线）**：`commonMain` 新增 `org.jetbrains.androidx.navigation:navigation-compose` 依赖（nexus 已实测存在 `ohosArm64` 变体），以类型安全路由组织屏幕跳转。
- **新增路由骨架 `router/`**：`AppDestination.kt`（`@Serializable` 路由目标，本期 `Login` / `Main` 两条）与 `AppNavGraph.kt`（`NavHost` 装配），对齐原工程 `NavGraph.kt` 的 `AppDestination.*` + `toRoute<T>()` 模式。
- **登录成功跳转首页**：`App()` 中 `LoginPage(onLoginSuccess)` 空接缝接上 `navigate(Main)`，并从返回栈移除登录页（返回键不回登录页）。
- **启动自动登录**（2026-09-24 增补）：起始路由按本地会话二分——有会话令牌直进主框架（登录页不入栈），无令牌进登录页；token 失效由既有 401 登录失效接线拉回登录页。
- **新增主框架壳 `MainPage`**：`Scaffold` + 底部 `NavigationBar`（工单 / 我的 两项；消息项注释停用、暂不显示），tab 切换为壳内状态（对齐原工程 `selectedTab`，不走路由）；三个 tab 各成独立页面单元（`page/workorder|message|profile`，Page + ViewModel 空壳的 MVVM 结构），内容区为占位说明页（「xx 模块迁移中」），不取业务数据。
- **登出回流**：「我的」占位页提供临时「退出登录」入口——清除本地会话令牌并回登录页（主框架出栈）。
- **401 登录失效接线**（收口网络层遗留的「路由跳转尚未接线」）：`App()` 层订阅 `AuthSessionManager` 的登录失效事件流，收到即回登录页并清空返回栈。
- **资源与 token**：新增 `ic_tab_*` 三个自备矢量图标（本仓无 material-icons，见归档 design 实测结论）、`str_main_tab_*` / `str_main_placeholder_*` 中英两套文案，`AppColors` 补三个导航色值。

**不在本次范围内**：Splash 闪屏；工单列表 / 消息 / 我的的业务内容（后续各自立项）；强制改密弹窗与密码状态刷新；DataCenter tab（原工程已注释）；iOS 实机验证（Windows 环境阻塞）。（自动登录已由 2026-09-24 增补转正，见 What Changes。）

## Capabilities

### New Capabilities

- `ui/navigation`: 应用级导航能力——类型安全路由骨架、登录成功跳转与返回栈语义、登出回流、登录失效自动回登录页。
- `ui/home-shell`: 主框架壳能力——底部导航（工单 / 我的；消息暂不显示）的结构、切换与占位内容，以及占位期退出登录入口。

### Modified Capabilities

无。登录成功可见行为仍由 `ui/login` 的成功回调契约描述，本次只是在消费侧接上真实跳转；`data/http-client` 的登录失效事件契约不变，本次只是消费该事件。
