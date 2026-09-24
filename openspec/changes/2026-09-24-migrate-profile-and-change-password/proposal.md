# Proposal

## Why

首页壳（`2026-09-24-migrate-navigation-and-home-shell`）已交付三 tab 页面单元与导航骨架，「我的」当前是迁移占位。按渐进迁移路线，本轮全量迁移「我的」域（原工程 `page/profile` 共 ~1150 行）：资料页、修改密码页、强制改密提示，以及支撑它们的账号安全数据能力（服务端登出、修改密码、密码规则、密码状态）。这是登录之后第一个真实业务页——验证「MVVM 页面单元 + 类型安全路由 + DTO/Entity/UIModel 分层」的完整迁移配方，后续工单/消息照此复制。

## What Changes

- **新增 `ProfileRepository` 聚合账号安全数据能力**（方案 B，用户选定）：`logout()`（`Staff.Login/logout`，服务端尽力而为、本地会话必清）、`changePassword()`（`Staff.Login/passwordEdit`，明文 body）、`getPasswordRules()`（`Staff.Login/getPassRules`，防御式字段别名 + 正则长度区间提取）、`loadPasswordStatus()`（`Order.Order/initInfo` 的 `passStatus`，0=需改密）。DTO → Entity → UIModel 分层原样迁（`PasswordRulesDto`/`PasswordRulesEntity` + mapper）。
- **新增用户名持久化**：登录成功持久化用户姓名（`StorageKeys` 新键），作为「我的」页展示名的单一数据来源（对齐原工程 DataStore 语义）。
- **迁移「我的」页**（替换 tab 占位）：`ProfileViewModel`（自写状态容器 + `ProfileEffect.LoggedOut` 一次性事件）+ `ProfilePage`（资料卡、系统设置菜单含动态「修改密码」项、退出登录按钮）。
- **迁移修改密码页并挂新路由** `AppDestination.ChangePassword`：`ChangePasswordViewModel`（服务端密码规则正则校验、双框一致性、防重复提交）+ 表单页；**校验/结果文案以类型化枚举入 state、Page 映射 `stringResource`**（VM 不引 Context，保证多语言）。
- **迁移强制改密提示**：新 `page/main/MainViewModel` 查询密码状态（进入主框架时刷新），`passStatus == 0` 弹出不可关闭提示 →「去修改」导航修改密码页；改密成功清会话回登录。
- **资源**：`profile_*` / `change_password_*` 键族沿用原工程键名，中文默认回退 + 英文两套；`ic_back_arrow`、`ic_password_lock` 自备矢量（material icons 不可用），其余图标沿用 emoji 文本（原工程即 emoji）。

**不在本次范围内**：NFC 入口行（NFC 域未迁）；统计数据区与工作功能区（原工程已注释停用）；偏好设置/帮助与反馈/关于 的点击动作（原工程即无）；「关于」版本号动态化（沿用静态 1.0.0）；自动登录。

## Capabilities

### New Capabilities

- `data/profile`: 账号资料与安全数据能力——服务端登出、修改密码、密码规则获取、密码状态查询，以及用户展示名的持久化数据源。
- `ui/profile`: 「我的」页与修改密码页的用户可见行为——资料卡、系统设置菜单、退出登录、修改密码表单与校验反馈、强制修改密码提示。

### Modified Capabilities

- `data/login`: 登录成功在持久化会话令牌之外，增加持久化用户姓名（供「我的」页展示名读取）。
- `ui/home-shell`: 「我的」tab 内容区由迁移占位替换为「我的」页实际内容；占位期临时退出登录入口由 `ui/profile` 的退出登录能力接替。
