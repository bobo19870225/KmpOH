# Spec Delta

## Purpose

（无变化——本文件仅承载主框架壳能力的增量修订：「我的」tab 由占位转为实际内容。）

## MODIFIED Requirements

### Requirement: tab 迁移占位内容

工单与消息 tab 的内容区 SHALL 呈现迁移占位说明（所属模块名与「迁移中」提示），MUST NOT 呈现业务数据或发起业务请求。「我的」tab 的内容区 SHALL 呈现「我的」页实际内容（契约见 `ui/profile`），MUST NOT 再呈现迁移占位。

#### Scenario: 工单占位可见

- **WHEN** 用户切换到工单 tab
- **THEN** 内容区显示工单模块的迁移占位说明

#### Scenario: 我的页实际内容可见

- **WHEN** 用户切换到「我的」tab
- **THEN** 内容区显示「我的」页（资料卡、系统设置菜单与退出登录入口）

## REMOVED Requirements

### Requirement: 占位期退出登录入口

**移除原因**：由 `ui/profile` 的「退出登录」能力接替（本就是该需求约定的演进路径），「我的」tab 不再渲染 `MainTabPlaceholder` 占位。
