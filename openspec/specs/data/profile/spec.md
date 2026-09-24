# data/profile

## Purpose

提供账号资料与安全数据能力：服务端登出、修改密码、密码规则获取、密码状态查询，以及用户展示名的持久化数据源。支撑「我的」页与修改密码页（契约见 `ui/profile`）。

## Requirements

### Requirement: 服务端登出与本地会话清理

登出 SHALL 调用服务端登出接口（`mobile/Staff.Login/logout`）；无论服务端调用成败，本地会话令牌与用户展示名 MUST 被清除。服务端调用失败 MUST NOT 阻断登出流程。

#### Scenario: 登出成功清理本地会话

- **WHEN** 用户触发退出登录且服务端登出成功
- **THEN** 本地会话令牌与用户展示名被清除

#### Scenario: 服务端登出失败仍清理本地会话

- **WHEN** 服务端登出接口调用失败
- **THEN** 本地会话令牌与用户展示名仍被清除，登出流程完成

### Requirement: 修改密码

系统 SHALL 以新密码向修改密码接口（`mobile/Staff.Login/passwordEdit`，密码按与原工程一致的明文约定传输）发起修改请求。成功时 MUST 返回服务端提示文案（为空时以默认成功文案呈现）并清除本地会话；失败时 MUST 返回服务端提示文案且保留本地会话。

#### Scenario: 修改密码成功

- **WHEN** 以符合规则的新密码提交修改且服务端受理成功
- **THEN** 呈现成功提示，本地会话被清除

#### Scenario: 修改密码失败

- **WHEN** 服务端拒绝修改（如原密码策略冲突）
- **THEN** 呈现服务端提示文案，本地会话保留

### Requirement: 密码规则获取

系统 SHALL 从 `mobile/Staff.Login/getPassRules` 获取密码规则（规则正则与提示文案列表、长度区间、描述）。字段映射 MUST 兼容服务端多别名（长度字段的 `minLength/minLen/passwordMin` 等）；长度区间可从规则正则的 `{m,n}` 片段提取；两者均缺失时 MUST 回落默认区间（最短 6、最长 50）。空白的规则条目 MUST 被剔除。

#### Scenario: 规则正常返回

- **WHEN** 密码规则接口返回规则列表与长度区间
- **THEN** 规则按正则逐条可用于校验，页面可展示规则说明

#### Scenario: 长度字段缺失时从正则提取

- **WHEN** 响应未提供长度字段但规则正则含 `{8,16}` 片段
- **THEN** 长度区间取 8..16

#### Scenario: 规则获取失败

- **WHEN** 密码规则接口调用失败
- **THEN** 以默认长度区间兜底，且向用户提示规则加载失败

### Requirement: 密码状态查询

系统 SHALL 从 `Order.Order/initInfo` 读取密码状态（`passStatus`）。`passStatus` 为 0 表示必须修改密码；字段缺失时 MUST 视为无需修改。查询失败 MUST NOT 阻断主框架使用。

#### Scenario: 密码需修改

- **WHEN** 接口返回 `passStatus == 0`
- **THEN** 调用方收到「需修改密码」状态

#### Scenario: 查询失败不阻断

- **WHEN** 接口调用失败
- **THEN** 按「无需修改」处理，主框架可正常使用

### Requirement: 用户展示名数据源

登录成功时系统 SHALL 持久化用户姓名（同时见 `data/login` 的对应要求）。「我的」页展示名 MUST 以该持久化值为单一数据来源；登出与修改密码清会话时 MUST 一并清除。

#### Scenario: 展示名来自登录持久化值

- **WHEN** 用户登录成功后进入「我的」页
- **THEN** 展示名为登录时持久化的用户姓名

#### Scenario: 清会话后展示名清空

- **WHEN** 用户登出或修改密码成功
- **THEN** 持久化的用户姓名被清除
