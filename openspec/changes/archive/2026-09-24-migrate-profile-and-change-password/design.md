# Design

## Context

动机见 `proposal.md - Why`，可见行为契约见 `specs/data/profile/spec.md` 与 `specs/ui/profile/spec.md`。本节只记录影响方案的现状与约束。

**原工程 profile 域全貌**（逐文件读毕）：

- `ProfilePage.kt`(442)：资料卡（头像首字 / 姓名 / 职称·编号 / 已认证徽章）+ 系统设置菜单（偏好设置 / 帮助与反馈 / 关于 1.0.0 + 动态追加「修改密码」项）+ 可选 NFC 入口 + 退出登录按钮。统计数据区与工作功能区**已被注释停用**。菜单项图标是 **emoji 文本**（📋⏰🎓💬⚙️❓ℹ️🔒）。
- `ProfileViewModel.kt`(169)：`ProfileUiState`（展示默认值「高级技术工程师 / T-20086 / 已认证」等为**硬编码**，仅 `displayName` 来自 `DataStoreManager.userName`）+ `ProfileEffect.LoggedOut` 一次性事件 + `onLogoutClick()`（登出防重复、调 `loginRepository.logout()`）。
- `ChangePasswordPage.kt`(304) + `ChangePasswordViewModel.kt`(182)：双密码框表单（显隐切换）；校验 = 服务端规则正则逐条 + 长度区间 + 双框一致性；`submit()` 成功后 `clearLocalSession()` 并以一次性 `passwordChanged` 驱动回登录；文案经 `context.getString`（KMP 不可复制）。
- `MainViewModel.kt`(51)：`loadInitInfo()`（`Order.Order/initInfo`）取 `passStatus`（0=需改密），`MainPage` 在 ON_RESUME 刷新并弹不可 dismiss 的强制改密 `AlertDialog`。

**API 端点**（原 `ApiService`/`WorkOrderApi`）：`POST mobile/Staff.Login/logout`（`ApiResponse<JsonElement>`）、`POST mobile/Staff.Login/passwordEdit`（密码为**明文 plain-text body**）、`POST mobile/Staff.Login/getPassRules`（`PasswordRulesDto`，字段带 `minLength/minLen/passwordMin` 等多别名、规则正则内嵌 `{m,n}` 长度区间需提取，兜底 6..50）、`POST /mobile/Order.Order/initInfo`（`WorkOrderInitInfoDto`，本变更只取 `passStatus`）。

**本仓库现状**：`LoginRepository` 仅 `login()`；`StorageKeys` 只有令牌键、无用户名；`router/` 有 `Login`/`Main` 两路由目标与清栈跳转工具；`page/profile/` 当前是占位（`ProfilePage` + 空壳 `ProfileViewModel`）；AppColors 设计 token 已含 profile 用色（`PaletteFFF3F4F6` 等，实施时核对补缺）。

## Goals / Non-Goals

**Goals:**

- 「我的」tab 从占位替换为真实资料页，退出登录走服务端 + 本地清理。
- 修改密码全链路可用：新路由、服务端规则校验、成功后清会话回登录。
- 强制改密闭环：`passStatus == 0` 进主框架即提示并引导改密。
- 用户展示名以登录持久化的姓名为单一数据来源。
- 沉淀可复制的迁移配方（MVVM 页面单元 + 路由挂接 + 数据分层 + commonTest 纯逻辑），供工单/消息照此迁移。

**Non-Goals:**

- 不迁 NFC 入口行、统计区、工作功能区（原工程即停用或属未迁域）。
- 不做菜单项（偏好/帮助/关于）的实际功能（原工程即无动作）。
- 不做「关于」版本号动态化、不做自动登录。
- 不动网络层信封/签名/401 机制（复用现有 `ApiGateway`）。

## 决策

### 决策 1：数据层落位取方案 B（用户选定）——`ProfileRepository` 聚合四端点

`logout` / `changePassword` / `getPasswordRules` / `loadPasswordStatus` 全部落入新的 `ProfileRepository`，`LoginRepository` 不动。与原工程域划分（前三者在 `LoginRepository`、`loadInitInfo` 在 `WorkOrderListRepository`）的漂移是已知取舍：换来 profile 域一桶、退出登录与改密同居一处；`LoginRepository` 保持登录专责。工单迁移时 `loadPasswordStatus` 的 `initInfo` DTO 由工单域复用扩展（colorConfig 等）。

### 决策 2：ViewModel 自写容器 + 类型化文案枚举，VM 不引 Context

原工程 `ChangePasswordViewModel` 用 `context.getString` 取校验/结果文案——KMP 无 Context 且直接内联文案会破坏多语言。改为：VM 状态携带类型化消息枚举（如 `ChangePasswordToast.Required / ConfirmMismatch / MinLength / Server(message)`），**Page 侧映射 `stringResource`**；服务端 message 原样透传。两个 ViewModel 均沿用自写纯 Kotlin 状态容器（`StateFlow` + 一次性事件 `SharedFlow`），对齐 `LoginViewModel` 样板。

### 决策 3：用户名持久化为展示名单一数据源

`StorageKeys` 增用户姓名键，登录成功随令牌一并持久化（`data/login` 需求扩充）；`ProfileViewModel` 以该持久化值为 displayName 唯一来源，对齐原工程 `DataStoreManager.userName` 语义。职称/工号/已认证等沿用原工程展示默认值（原工程即硬编码，数据真实性属后续演进）。

### 决策 4：强制改密触发点简化为「进入主框架时刷新」

原工程 ON_RESUME 刷新（单 Activity 下等价于从后台回来也刷）。本变更取「进入 Main 路由时刷新一次」：覆盖登录后检查的主场景；修改密码成功本就清会话回登录，重登后必然重新检查——闭环无遗漏。记录为对齐性简化，若后续需要前后台切换时刷新再挂生命周期观察。

### 决策 5：修改密码成功 = 清会话回登录

对齐原工程 `clearLocalSession()` + `passwordChanged` 一次性事件语义：成功后本地会话必清、返回栈清空回登录页（复用 `navigateToLoginClearingStack`），必须重新登录。失败保留在表单页、错误行 + toast 提示。

### 决策 6：图标策略

返回箭头、锁等工具图标**自备矢量**（沿用 `ic_login_*` / `ic_tab_*` 迁移形态与 material icons 不可用的既定结论）；菜单项图标沿用 **emoji 文本**（原工程即 emoji 字符，CMP 文本渲染直出，无需资源）。

### 决策 7：不迁即停用/无动作的区域

统计区、工作功能区原工程已注释停用——不迁；NFC 入口行依赖未迁的 NFC 域——不迁；偏好/帮助/关于菜单项原工程点击即无动作——仅保留展示与点击波纹，无跳转。
