# Tasks

## 1. 日期基础：kotlinx-datetime（design 决策 1）

- [x] 1.1 引入 `org.jetbrains.kotlinx:kotlinx-datetime:0.7.1-1.0.0`（文档推荐线；仅 core 模块，不引 `zoneinfo`）：`gradle/libs.versions.toml` + `commonMain.dependencies`；验证方式：`--configuration commonMainResolvableDependencies` 解析含 `kotlinx-datetime` 且取到 `ohosArm64` 变体，`assembleDebug` / `linkDebugSharedOhosArm64` 编译通过。

  > **结果**：解析 `kotlinx-datetime:0.7.1-1.0.0` ✓（传递约束 0.7.1-0.3.0 → 0.7.1-1.0.0）；`linkDebugSharedOhosArm64` ✅（5m46s，ohos 变体实证）。

- [x] 1.2 迁移日期扩展（`toMonthTitle`/`toSelectedSubtitle`/`startOfWeek`/`atSafeDay`，基于 `kotlinx.datetime.LocalDate/YearMonth`）；（TDD）纯逻辑测试：月末加减（1/31 ±1 月）、闰年 2/29、跨年翻月/翻年、周起始、月长、`atSafeDay` 夹取；验证方式：先写失败用例再实现，`testDebugUnitTest` 全绿。

  > **结果**：TDD 红绿闭环（Unresolved reference → GREEN），`DateExtTest` 5 条全绿。实施注记：0.7.1 无 `atDay/atEndOfMonth/plusMonths`，`isoDayNumber`/`Month.number` 为扩展属性需显式 import——已按源码真实 API 落地（`utils/date/DateExt.kt`）。

## 2. 数据层（data/work-order-list）

- [x] 2.1 `InitInfoDto` 扩展 `color_config.risk_title`（`WorkOrderColorConfigDto` 形态照搬，颜色值非法安全忽略）；新增日工单/月计数 DTO 与 Entity（`WorkOrderDto.kt` 原样迁，防御式字段映射）；验证方式：编译通过，DTO/Entity 分层与 mapper 文件齐备。

- [x] 2.2 （TDD）mapper 纯逻辑测试：DTO→Entity 字段映射、风险色值非法忽略、`WorkOrderStatus`↔服务端状态类型映射（`toDayOrderType`）、Entity→UIModel（进度/标签/风险级）；验证方式：先写失败用例再实现，全绿。

- [x] 2.3 新增 `data/repository/WorkOrderListRepository.kt`：`loadDayOrders`（日期+状态类型+分页）、`loadDayCounts(month)`、`loadUnfinishedJobDates(jobDate)`、`loadRiskColors()`（决策 3，独立于 profile 的密码状态查询）；验证方式：编译通过，走 `ApiGateway`（信封/签名/401 复用），`AppGraph` 装配接入。

## 3. 列表页 ViewModel

- [x] 3.1 `WorkOrderViewModel`（空壳→实现，沿用页面单元命名）：迁 `WorkOrderListState`/日历标记状态（剔除签到三件套）与 `selectDate/shiftMonth/selectMonth/selectToday/shiftWeek/toggleExpanded/selectStatus/retry/refresh/loadMore/onToastShown`；缓存合并语义原样迁（决策 2）；验证方式：编译通过，不含 `androidx.lifecycle` import。

- [x] 3.2 （TDD）VM 纯逻辑测试：分页合并去重、缓存命中切回免重载、状态筛选后重载、`WorkOrderStatus` 筛选映射正确性；验证方式：先写失败用例再实现，全绿。

- [x] 3.3 回前台自动刷新（决策 7）：生命周期观察触发 `refreshAfterReturn` 语义；验证方式：编译通过，触发点为应用回前台（代码审阅）。

## 4. 列表页 UI（替换 tab0 占位）

- [x] 4.1 迁移页面骨架：`WorkOrderPage`（替换占位）+ 顶栏（年月标题/选中日副标题/回到今天）；验证方式：编译通过，结构顺序与 spec「日历交互」一致。

- [x] 4.2 迁移日历区：周/月两视图（展开/收起）、选日、翻周/翻月、数量与未完结标记渲染；验证方式：编译通过，自绘 Compose（无三方日历库，决策 1 边界）。

- [x] 4.3 迁移状态筛选条 + 工单卡片列表（进度行/风险标签按配置着色/状态徽章）；卡片点击走 `onOpenPreview` 接缝（决策 5，本期不跳转）；验证方式：编译通过，回调串联正确（代码审阅）。

- [x] 4.4 迁移分页尾（加载指示/没有更多）、空态、错误态（重试）；验证方式：编译通过，与 spec「分页加载」「空态与错误态」一致。


## 5. 资源与壳接线

- [x] 5.1 文案键族（`work_order_*` 沿用原工程键名）迁入 `values/strings.xml` 与 `values-en/strings.xml`；验证方式：两套键名差集为空（脚本比对）。

- [x] 5.2 自备矢量图标（原工程 Material 图标处）迁入 `composeResources/drawable/`；风险/状态色值补入 `AppColors`；验证方式：编译通过且 `Res.drawable.*` 可引用，页面引用 token 无内联色值。

  > **待用户验证**（图标渲染部分）。

- [x] 5.3 tab0 接线：`MainPage` 工单分支由占位换为 `WorkOrderPage`（消息分支保持注释停用）；同步修订变更内 `ui/home-shell` delta（已随提案成稿）；验证方式：编译通过，代码审阅。

## 6. 验证与交付

- [x] 6.1 全量单测回归：`./gradlew :composeApp:testDebugUnitTest` 全绿（含 1.2/2.2/3.2 新增用例）。

- [x] 6.2 `assembleDebug` + `linkDebugSharedOhosArm64` + `publishDebugBinariesToHarmonyApp` + `devecocli build` 全部成功；验证方式：各命令 BUILD SUCCESSFUL。

- [ ] 6.3 实机验证日历与列表；验证方式：选日切换列表、展开月视图、翻月、回到今天、标记渲染、状态筛选。

  > **待用户验证**。

- [ ] 6.4 实机验证卡片/分页/空错态；验证方式：卡片信息完整、滚动加载更多、无更多提示、空态与错误重试。

  > **待用户验证**。

## 用户验证清单（汇总，均待用户验证）

1. 工单 tab 显示真实列表：卡片含时间/门店/风险标签/进度/状态。
2. 日历：选日切换列表、周-月展开收起、翻周/翻月、回到今天、数量与未完结标记正确。
3. 状态筛选切换即时生效、选中态可见。
4. 分页：滚动到底自动加载、尾部加载指示、无更多提示、重复条目不出现。
5. 空态（无工单日）与错误态（断网）+ 重试恢复。
7. 手动刷新与回前台自动刷新生效。
8. 中/英语言文案正确；图标与风险色渲染正常（Android / 鸿蒙实机；iOS 需 macOS 环境补验）。
