# Spec Delta

## Purpose

（无变化——本文件仅承载登录数据能力的增量修订。）

## MODIFIED Requirements

### Requirement: 登录请求与结果映射

系统 SHALL 以员工编号、密码、设备标识与平台标识向真实登录接口（`mobile/Staff.Login/login`）发起登录请求。密码按与服务端既定约定传输（当前与原工程实现一致：JSON 字段原样传输）。登录成功时 MUST 持久化会话令牌与用户姓名，并返回包含用户标识与姓名的用户模型；令牌取值 MUST 兼容 `token` 与 `access_token` 双字段（主字段为空时取兼容字段），刷新令牌为空时以访问令牌兜底。

#### Scenario: 登录成功返回用户模型

- **WHEN** 以正确的员工编号与密码登录
- **THEN** 会话令牌被持久化，调用方获得含用户标识与姓名的用户模型

#### Scenario: 用户名持久化

- **WHEN** 登录成功
- **THEN** 用户姓名被持久化，供「我的」页展示名读取（见 `data/profile`「用户展示名数据源」）

#### Scenario: 令牌字段兼容

- **WHEN** 登录响应仅下发 `access_token` 而 `token` 为空
- **THEN** 系统以 `access_token` 作为会话令牌持久化

#### Scenario: 登录业务失败

- **WHEN** 服务端返回非成功业务码（如账号或密码不正确）
- **THEN** 登录失败，失败信息为服务端提示文案，不写入任何令牌
