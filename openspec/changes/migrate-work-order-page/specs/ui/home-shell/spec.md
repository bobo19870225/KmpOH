# Spec Delta

## Purpose

（无变化——本文件仅承载主框架壳能力的增量修订：工单 tab 由占位转为实际内容。）

## MODIFIED Requirements

### Requirement: tab 迁移占位内容

「我的」tab 的内容区 SHALL 呈现「我的」页实际内容（契约见 `ui/profile`）；「工单」tab 的内容区 SHALL 呈现工单列表页实际内容（契约见 `ui/work-order-list`）；两者 MUST NOT 呈现迁移占位。「消息」tab 的内容区 SHALL 呈现迁移占位说明（模块名与「迁移中」提示），MUST NOT 呈现业务数据或发起业务请求。

#### Scenario: 工单列表实际内容可见

- **WHEN** 用户切换到工单 tab
- **THEN** 内容区显示工单列表页（日历、状态筛选与工单卡片列表）

#### Scenario: 我的页实际内容可见

- **WHEN** 用户切换到「我的」tab
- **THEN** 内容区显示「我的」页（资料卡、系统设置菜单与退出登录入口）

#### Scenario: 消息占位可见

- **WHEN** 用户切换到消息 tab（恢复显示后）
- **THEN** 内容区显示消息模块的迁移占位说明
