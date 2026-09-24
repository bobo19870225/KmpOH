# Proposal

## Why

首页 tab0 是工单列表（技师的核心业务入口）：按日浏览工单、月历标记未完结日期、状态筛选与分页加载，当前仍是「模块迁移中」占位。我的域迁移已验证完整配方（数据分层 + MVVM 页面单元 + 资源键族 + TDD 纯逻辑），本轮把 tab0 占位替换为真实工单列表页（原工程 `page/workorder` 约 2360 行 + 数据层约 340 行）。详情预览、签到、拍照等流程按渐进路线另立变更。

## What Changes

- **新增 `WorkOrderListRepository` 工单列表数据能力**：日工单加载（`loadDayOrders`）、当月日历计数（`loadDayCounts`）、未完结日期标记（`loadUnfinishedJobDates`）、风险标签色配置（`initInfo` 的 `color_config.risk_title`——扩展现有 `InitInfoDto`，与 `data/profile` 共用接口）；DTO → Entity → UIModel 分层原样迁（含服务端字段防御式映射）。
- **迁移工单列表页 `WorkOrderListPage`**（替换 tab0 占位）：顶栏、可展开/收起的周-月日历（选日/切周/切月/回到今天）、状态筛选 tab、工单卡片列表（进度行、风险标签、状态徽章）、加载更多分页、空态与错误态（可重试）、首次进入引导弹窗；`WorkOrderListViewModel` 自写状态容器迁移（日期选择/月切换/状态筛选/分页/刷新/回流刷新/toast）。
- **修改 `ui/home-shell`**：「tab 迁移占位内容」需求中工单 tab 由占位转为实际内容（消息 tab 仍占位）。
- **点击接缝**：工单卡片「预览/项点击」保留回调接缝（详情路由与详情页由后续变更挂接）；本期点击无跳转。
- **资源**：工单页文案键族（`work_order_*` 沿用原工程键名）中英两套；自备矢量图标（原工程用 Material 图标处）；风险/状态色值补入 `AppColors`。

**不在本次范围内**：工单详情预览（`WorkOrderPreview` 及 `page/preview` 域）与新增详情路由；PreCheckIn 签到流与照片采集（含 `submitSignIn`、`WorkOrderSignInUiPayload`/`WorkOrderSignInMode` 一并不迁）；NFC；原工程 `WorkOrderModels.kt` 内的 demo 数据 fixtures（`orders()`/`orderById()`）；遗留 `page/home/HomePage.kt`（主链路未引用，实施时核实后不迁）。

## Capabilities

### New Capabilities

- `data/work-order-list`: 工单列表数据能力——日工单、日历计数、未完结日期标记、风险标签色配置的获取与映射。
- `ui/work-order-list`: 工单列表页的用户可见行为——日历交互、状态筛选、工单卡片列表、分页加载、空态/错误态与首次引导。

### Modified Capabilities

- `ui/home-shell`: 「tab 迁移占位内容」需求——工单 tab 内容区由迁移占位替换为工单列表页实际内容（消息 tab 保持占位）。
