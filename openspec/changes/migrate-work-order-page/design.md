# Design

## Context

动机见 `proposal.md - Why`，可见行为契约见 `specs/data/work-order-list/spec.md` 与 `specs/ui/work-order-list/spec.md`。本节只记录影响方案的现状与约束。

**原工程工单列表域**（逐文件读毕）：

- `page/workorder/WorkOrderListPage.kt`（1728 行）：`WorkOrderComposeScreen` 主入口 + `WorkOrderTopBar`、可展开/收起 `WorkOrderCalendar`（`CollapsedCalendarDay`/`CalendarDay`，自绘 Compose、无三方日历库）、`StatusTabs`、`OrderList`+`OrderCard`+`WorkOrderProgressRow`、`WorkOrderLoadMoreFooter`、`EmptyOrderState`、`WorkOrderErrorState`、`WorkOrderPageIntroDialog`（首次引导）。
- `WorkOrderListViewModel.kt`（508 行）：`WorkOrderListState`（日历状态 + 列表 + 分页 + 加载/刷新标志）、`WorkOrderCalendarMarkerState`（计数/未完结标记）、`WorkOrderSignInUiPayload`/`WorkOrderSignInMode` 与 `submitSignIn()`（**签到流，本期不迁**）；其余交互：`selectDate/shiftMonth/selectMonth/selectToday/shiftWeek/toggleExpanded/selectStatus/retry/refresh/refreshAfterReturn/loadMore/onToastShown`；内部含按日期+筛选的**缓存合并**（`publishCachedOrders`/`mergeOrders`）与 `WorkOrderStatus↔服务端状态类型` 映射。
- `WorkOrderModels.kt`（127 行）：`WorkOrderStatus` 枚举、`WorkOrder`/`WorkOrderTag`/`WorkOrderProgress` UI 模型、`LocalDate/YearMonth` 辅助扩展，以及 `orders()/orderById()` **demo fixtures**（不迁）。
- `data/repository/WorkOrderListRepository.kt`（135 行）：`loadDayOrders`（日期+状态类型+分页）、`loadDayCounts(month)`、`loadUnfinishedJobDates(jobDate)`、`loadInitInfo()`（`color_config.risk_title` 风险色 + `pass_status`）、`riskColor(label)`。
- `data/model/dto/WorkOrderDto.kt`（203 行）：日工单/月计数/initInfo（含 `WorkOrderColorConfigDto.riskTitle: Map<String,String>`，颜色值含非法串需安全忽略）。

**本仓库现状**：tab0 为 `WorkOrderPage` 占位（`WorkOrderViewModel` 空壳）；`InitInfoDto` 已有 `passStatus`（设计注释预留 `color_config` 扩展）；`data/profile` 的 `loadPasswordStatus()` 已消费 `initInfo`；导航骨架/我的域/会话与 401 接线均就位；`AppColors`/资源键族惯例、自写状态容器样板（`LoginViewModel`）established。

**依赖约束**（2026-09-24 复核修正）：`org.jetbrains.kotlinx:kotlinx-datetime` **已适配鸿蒙**——三方库文档表 5 明列（fork 线 `0.7.1-1.0.0`，core + zoneinfo 模块均「已适配」），nexus 实证 `0.7.1-1.0.0`（及 `0.7.1-1.1.0-xx` 更新线）存在；`java.time` 不可跨端。初稿曾按猜测构件名盲探 nexus 得 404 误判为未适配——已按文档（适配权威）纠正。

## Goals / Non-Goals

**Goals:**

- tab0 从占位替换为真实工单列表页（日历交互、状态筛选、卡片列表、分页、空/错态、首次引导）。
- 数据层三接口 + 风险色映射落地，分页/缓存合并语义对齐原工程。
- 沉淀零依赖日期模型与列表域迁移产物，供详情/签到流后续变更复用。

**Non-Goals:**

- 不迁详情预览（`WorkOrderPreview`/`page/preview` 域）与详情路由——卡片点击仅回调接缝。
- 不迁签到流（`submitSignIn`、`WorkOrderSignInUiPayload`/`WorkOrderSignInMode`）与照片采集。
- 不迁 demo fixtures（`orders()/orderById()`）；不迁遗留 `page/home/HomePage.kt`（主链路未引用，实施时核实后定案）。

## 决策

### 决策 1：引入 `kotlinx-datetime`（文档推荐线 `0.7.1-1.0.0`）

三方库文档确认已适配（见 Context），`java.time` 不可跨端 → 引入 `org.jetbrains.kotlinx:kotlinx-datetime:0.7.1-1.0.0`（core 模块即可，`zoneinfo` 时区模块本页不需要、不引入）。`kotlinx.datetime.LocalDate`/`YearMonth` 直接对应原工程 `java.time` 同名类型的用法；`WorkOrderModels` 的日期扩展（`toMonthTitle`/`toSelectedSubtitle`/`startOfWeek`/`atSafeDay`）照搬为扩展函数，TDD 覆盖其纯逻辑边界（月末、闰年、跨年）。

### 决策 2：VM 自写状态容器 + 缓存合并语义原样迁

`WorkOrderListViewModel` 改造为纯 Kotlin 状态容器（对齐 `LoginViewModel` 样板，不引 androidx.lifecycle）；`WorkOrderListState`/日历标记状态原样迁（剔除签到三件套）。**按日期+筛选缓存与合并去重**（`publishCachedOrders`/`mergeOrders`）语义原样保留：切回已加载日期免重载、下一页追加去重。

### 决策 3：风险色经 `InitInfoDto` 扩展读取

`InitInfoDto` 增 `color_config.risk_title`（注释已预留），`data/work-order-list` 新增 `loadRiskColors()`（同一 `Order.Order/initInfo` 端点）。与 `data/profile` 的 `loadPasswordStatus()` 各自调用同一端点、各取所需字段——接受轻微重复调用，换取两域能力独立（后续可提升为共享基础信息仓储，不在本期）。

### 决策 4：状态筛选映射收敛在 mapper

`WorkOrderStatus ↔ 服务端状态类型` 映射（`toDayOrderType`）迁入 mapper 层纯函数（TDD 落点），VM 只传枚举。

### 决策 5：卡片点击仅接缝

`WorkOrderComposeScreen` 回调收敛为 `onOpenPreview: (WorkOrder) -> Unit` + `onToastMessage: (String) -> Unit`；原签名中的 `onLogout/onNavigateToUpdateCustomerLocation/onSignInSuccessPreview` 属未迁域，随详情/签到变更回接。本期接缝指向日志空实现（对齐登录页 toast 接缝模式）。

### 决策 6：不引入首次进入引导（用户裁定，2026-09-24 修订）

~~首次引导以 KV 标志去重~~ → **用户裁定整体移除且今后不再引入**：任何「首次进入引导/onboarding 弹窗 + 已读标志」类机制不做（曾短暂实现的 `WorkOrderPageIntroDialog` 已删），后续变更亦不得引入。

### 决策 7：回前台自动刷新挂生命周期

`refreshAfterReturn()` 语义保留；本期触发点为「应用回前台」（生命周期观察，Compose 跨端 API），从详情页返回的触发随详情变更接线。

### 决策 8：网关扩展 form / multipart 传输形态（实施中浮现，2026-09-24 补记）

工单列表三端点与 JSON 信封不同形：`dayOrder`/`unfinishJobs` 为 **FormUrlEncoded**（字段 `job_date`/`day_order_type`/`page`/`limit`），`dayCount` 为 **Multipart**（part `month`，text/plain）。网关（`ApiCall`/`ApiGateway`）按既有 `bodyText` 约定**增量扩展** form-urlencoded 与 multipart-text 两种发送形态：实际请求体按端点形态发送，`bodyText` 传**字段映射的 JSON 文本**供签名规范化复用（`canonicalParamsOf` 解析 JSON 后排序/剔除，与原工程「参数规范化」一致）；信封解析、401 刷新编排、签名头照旧复用。

鸿蒙端落地补记（2026-09-24，实机踩坑后修订）：RCP 对**裸 string/ArrayBuffer 按 text/plain/octet-stream 发出**，服务端读不到表单参数（实测 `dayOrder` 报「请选择日期」）；且 ktor 存在两个同名 `ByteArrayContent`（顶层具体类 vs `OutgoingContent.ByteArrayContent` 抽象基类），按前者匹配会让 `FormDataContent` 静默落入 else **丢弃整个请求体**。故桥接线协议扩展 `bodyForm`/`bodyMultipart` 字段表，ArkTS 侧用 RCP 原生 **`rcp.Form`/`rcp.MultipartForm`** 承载（application/x-www-form-urlencoded / multipart/form-data，与端点形态一致）；`dayCount` 用公共 `MultipartTextContent`（公开字段表 + 委托 ktor multipart 序列化，供桥接层读字段）。请求体形态编码收敛在 commonMain `BridgeWireBody.kt`（有单测钉回归）。
