# Design

## Context

动机见 `proposal.md - Why`，可见行为契约见 `specs/ui/design-system/spec.md` 与 `specs/ui/login/spec.md`。本节只记录影响方案的现状与约束。

**宿主工程现状**：`composeApp` 是唯一 Gradle 模块，`commonMain` 仅有 `App.kt`、`Greeting.kt`、`Platform.kt` 三个文件。已声明的依赖只有 `compose.runtime / foundation / material3 / ui / components.resources`，没有 icons 相关依赖，也没有任何 ViewModel / 协程依赖。

**私有 Nexus 仓库的实测结论**（本次逐个人工探测 `https://maven.eazytec-cloud.com/nexus/repository/maven-public/`，非推测）：

| 坐标 | 结论 |
|---|---|
| `material-icons-extended` | 最高仅 **1.7.3**，无 `1.9.2-0.3.0`（HTTP 404） |
| `material-icons-core` | 最高仅 **1.7.3**，无 1.8/1.9.x 任何版本 |
| `material3:1.9.2-0.3.0` 的传递依赖 | **不含** `material-icons-core` |
| `lifecycle-viewmodel-compose:2.9.6`（本仓 `androidMain` 当前所用） | 变体只有 android / desktop / js / uikit* / macos* / wasmJs，**无 `ohosArm64`** |
| `lifecycle-viewmodel-compose:2.11.0-0.1.0-03` | **有** `ohosArm64` 与 `ohosX64` 变体，同时含 `iosArm64` / `iosSimulatorArm64` / `android` |

两个直接后果：

1. `Icons.Filled.*` / `Icons.AutoMirrored.Filled.*` 在本工程**完全不可用**——不是"缺 extended"，而是连 core 都没有，且 `material3` 也不再传递引入。原安卓登录页用到的 `ArrowForward`、`Visibility`、`VisibilityOff` 三个 Material 图标都必须自备。
2. 官方 `lifecycle 2.9.6` 加进 `commonMain` 会让 `ohosArm64` 无法解析依赖、直接编译失败。鸿蒙可用的是另一条 fork 系列 `2.11.0-0.1.0-03`。

**安卓原工程形态**：`LoginPage` 是无状态的 `LoginContent` + 有状态外壳；`LoginViewModel` 用 `StateFlow` 持有 `phone` / `password` / `loginEnabled` / `uiState` / `toastResId`，并通过 `LoginRepository` 发起网络请求（本次不迁移）。原工程用 `hiltViewModel()` 获取实例，依赖 Hilt——Hilt 只在 JVM 可用，必须更换。

## Goals / Non-Goals

**Goals:**

- 让 `:composeApp` 具备可复用的跨端 UI 基础层（token + 通用组件 + 页面状态模型），供后续所有页面直接引用。
- 登录页在 Android / iOS / 鸿蒙三端都能编译、运行，且视觉与交互与安卓原工程一致。
- 用一次真实的端到端验证，确认"KMP ViewModel + CMP 资源 + 矢量图标"这条基础设施在 `ohosArm64` 上确实可用——这是后续每个页面都要依赖的前提。
- 为下一步接入网络层留出清晰接缝：把假实现隔离在一个可替换的依赖点上，而不是散落在 UI 里。

**Non-Goals:**

- 不引入网络客户端（Ktor）、序列化、协程依赖以外的数据层设施。
- 不引入导航框架，不做登录成功后的真实跳转（仅保留回调接缝）。
- 不做会话持久化、凭据记忆、"保持登录"等存储能力。
- 不做页面的响应式/多设备适配（平板、折叠屏、横屏专用布局）。
- 不重命名宿主工程包名（见 Decisions 第 5 条）。

## Decisions

### 1. 依赖：不引入任何新依赖，状态载体自写（**已由门禁实测推翻原决策**）

**原决策**：把 `androidx-lifecycle` 由 `2.9.6` 改为 fork 版 `2.11.0-0.1.0-03`，`commonMain` 引入 `lifecycle-viewmodel-compose`，沿用官方 `viewModel()` API。

**执行结果：门禁失败，方案推翻。** 第 1 组冒烟任务实测两次，两条 fork 路线在 **Android 目标**上各有一种失败模式：

| 尝试 | 鸿蒙 | Android |
|---|---|---|
| 官方 `2.9.6` | ❌ 变体无 `ohosArm64` | ✅ |
| fork `2.11.0-0.1.0-03` | ✅ | ❌ 拉到 `androidx.lifecycle:lifecycle-*-android:2.11.0`，要求 AGP 9.1.0+ / compileSdk 37；本仓 AGP 8.6.0 / compileSdk 36 → `checkDebugAarMetadata` FAILED |
| fork `2.9.4-1.1.0-24` | ✅ | ❌ `checkDebugDuplicateClasses` FAILED：fork 的 `lifecycle-common-jvm-2.9.4-1.1.0-24.jar` 与 Google 的 `androidx.lifecycle:lifecycle-common-jvm:2.9.4` 同时存在，`androidx.lifecycle.*` 类全量重复 |

**结论**：这不是"版本没选对"，而是**当前依赖组合下官方 KMP ViewModel 无法同时满足 Android 与鸿蒙两端**。官方路线在鸿蒙侧无变体；fork 路线在 Android 侧要么要求远超本仓的 AGP 版本，要么与 Google 官方 artifact 类冲突——后者是该 fork 自身的构建缺陷，非配置问题。

**现行决策**：**不引入任何新依赖**，`LoginViewModel` 改为自写纯 Kotlin 状态容器，暴露 `StateFlow`。

**理由**：`StateFlow` 所需的 `kotlinx-coroutines-core` 已经由 `compose.runtime` 传递引入 `commonMain`（实测解析为 `1.10.2-0.3.0`），因此该方案**零依赖变更**——`build.gradle.kts` 与 `libs.versions.toml` 一行都不用改。风险从"三方件的 ABI 兼容"降为"普通 Kotlin 代码能否编译"，后者不存在未知。

**代价**：失去 `viewModel()` 带来的生命周期感知与配置变更（旋转屏幕）时的实例保持。本次登录页的容器只持有表单输入与一个瞬态加载标志，旋转丢失的代价可接受。后续若确需生命周期能力，应作为独立的构建基础设施变更（升 AGP 9.1+ / compileSdk 37，或改用同代 compose 栈）再评估。

**与 spec 的关系**：`specs/ui/login/spec.md` 只规定可观察行为（按钮可用性、加载态、结果回调、一次性提示消费），不规定状态载体。因此推翻该决策**不需要改动任何 spec**。

**已确认**：该回退方案在 tasks.md 1.2 中原就作为失败预案写明，并已与用户确认执行。

### 2. 图标：全部自备矢量 Drawable，不引入任何 icons 依赖

所有图标统一放 `composeResources/drawable/`，以 Android VectorDrawable XML 形式提供，通过 `painterResource(Res.drawable.…)` 引用。

**理由**：`material-icons-core` / `-extended` 在 1.9.x 线不存在，且 `material3` 不再传递引入 `Icons` 对象；强行引入 1.7.3 会与 compose 1.9.2 fork 产生 ABI 错配。用 Drawable 则零依赖、三端一致。

**具体做法**：安卓原工程的 5 个图标（`ic_login_iphone`、`ic_login_lock`、`ic_login_shield`、`ic_login_sparkle`、`ic_login_checkmark`）经核实均为**单 path 的简单矢量**，可近乎原样迁移，只需去掉 `android:` 命名空间前缀相关的多余属性。另外 3 个原先取自 Material 的图标（`ArrowForward`、`Visibility`、`VisibilityOff`）以同样形式新增为 `ic_login_arrow_forward`、`ic_login_visibility`、`ic_login_visibility_off`，采用 Material 官方路径数据。

**替代方案**：在 Kotlin 中用 `ImageVector.Builder` 手写——同样可行，但会让图标散落在代码里，与其余 5 个 Drawable 风格不统一，故不采用。

### 3. 多语言：`values/` 放中文，`values-en/` 放英文

**理由**：CMP 的 `values/`（无语言限定符）是**默认回退**目录，未匹配到任何语言时使用。用户要求"默认中文"，因此中文占 `values/`，英文占 `values-en/`。这与安卓原工程"英文是 default、中文在 `values-zh-rCN/`"的布局**恰好相反**——这是刻意偏离，因为原工程的默认语言是英文，而本次要求默认中文。

**替代方案**：照搬原工程布局（中文放 `values-zh-rCN/`）。不采用：那样系统语言为日语时页面会回退成英文，与"默认中文"的要求冲突。

### 4. 资源键名：沿用原工程的 `str_*` 命名

直接复用安卓原工程的字符串键名（`str_login_title`、`str_login_start_service` 等），中英两套共用同一批键。

**理由**：`str_*` 前缀是该业务线既有的资源约定，沿用可让后续从 Technician-Android 批量迁移页面时，键名对得上，减少人工对照成本。

### 5. 包名：沿用宿主工程的 `com.example.kmpoh`

新增代码使用 `com.example.kmpoh.ui.theme`、`com.example.kmpoh.ui.components`、`com.example.kmpoh.page.login`、`com.example.kmpoh.utils`，目录遵循本仓"用完整包名当文件夹名"的既有约定（`src/commonMain/kotlin/com.example.kmpoh/…`），而不是原工程的 `com.lbs.technician.*`。

**理由**：宿主工程现有全部代码都在 `com.example.kmpoh` 下；迁移期混用两套包名会让 `expect/actual` 与资源引用变得混乱。全量重命名为 `com.lbs.technician` 是一次机械但横跨全仓的操作，应作为独立变更在移植收尾时统一执行，不应夹在首个页面里。

### 6. ViewModel：形态照搬，依赖替换为假实现

迁移 `LoginViewModel` 的**状态结构与对外 API**（`phone`、`password`、`loginEnabled`、`uiState`、`toastResId` 五个 `StateFlow` 及对应的 `onPhoneChanged` / `onPasswordChanged` / `onLoginClick` / `onToastShown`），但把 `LoginRepository` 替换为一个仅存在于本次变更中的**本地假实现**，不发起任何网络请求。

**理由**：保留原工程的状态形状，下一步接入 Ktor 时只需替换 Repository 实现，UI 与 ViewModel 不动。假实现单独成文件，删除即净。

**与 spec 的关系**：`specs/ui/login/spec.md` 只规定"失败时触发一次提示、成功时触发成功回调"这类**可观察行为**，不规定失败原因从哪来。因此替换假实现不改变 spec。

**Hilt 的替代**：原 `hiltViewModel()` **不再对应任何官方 API**。按决策 1 的结论，该类既不继承 `androidx.lifecycle.ViewModel`，也不用 `viewModel()` / `hiltViewModel()` 获取。它就是一个普通 Kotlin 类：

- 内部用 `MutableStateFlow` 持有五个状态，对外暴露只读 `StateFlow`（与原工程 API 形状一致）。
- 由页面用 `remember { LoginViewModel(...) }` 持有实例，作用域跟随组合。
- 需要协程时（假实现的延迟）用一个由页面 `rememberCoroutineScope()` 提供的 `CoroutineScope`，或直接做成挂起函数由页面启动 —— 实现细节留到任务 4.2 决定。

**代价**：没有生命周期作用域，页面离屏后协程不会被自动取消。本次假实现无真实挂起等待，影响可忽略；接入网络层时需要显式处理取消（属于下一步的范围）。

### 7. 入口：`App()` 直接渲染登录页，不引入路由

**理由**：本次仅交付登录页，引入导航框架属于额外复杂度。登录成功回调先落在 `App()` 内，暂不产生跳转。

**代价**：`App()` 会短暂成为一个"知道登录页"的宿主。下一步引入导航时，这个接缝正好是替换点。

### 8. 共享层按原样全量迁移

`AppColors` / `AppDimens` / `AppFontSize` 三个 token 对象整体搬迁，不裁剪未使用条目。

**理由**：它们是纯常量声明，裁剪需要逐条比对后续页面用量，成本高于收益；整体搬运可保证后续页面迁移时 token 必然齐备。`AppColors` 中体量最大的是 `Palette*` 系列色值，构成本次唯一的"明显冗余"，接受之。

## Risks / Trade-offs

**[已发生的风险，已处置] fork lifecycle 在 Android 目标上不可用**
→ 实际发生了，且比预案更严重（两条 fork 路线两种失败模式，见决策 1）。缓解措施**按预案生效**：冒烟门禁前置执行，失败即回退自写容器，工作区已完整还原，回退面未扩散。**该风险已关闭**——方案不再引入该依赖。

**[已关闭的风险] `viewModel()` 在非 Android 端需要 `ViewModelStoreOwner`**
→ 因决策 1 改为自写容器，该 API 及其 owner 依赖已完全移除，风险随之消失，无需再验证。**该风险已关闭**。

**[风险] CMP 对 Android VectorDrawable XML 的支持可能是路径指令子集，某些指令（如 `arcTo`）不被支持**
→ 缓解：5 个原图标经核实都是单 path 简单图形，先迁移并三端验证；若某图标渲染异常，把不支持的指令改写为等价的三次贝塞尔或使用 `ImageVector.Builder` 手写该单个图标。

**[风险] 鸿蒙侧资源需经 `publishDebugBinariesToHarmonyApp` 拷入 `rawfile/`，新增的 `values-en/` 与 8 个 drawable 可能未按预期生效**
→ 缓解：新增目录会被现有 `from("src/commonMain/composeResources")` 整目录拷贝覆盖，无需改脚本；但需在鸿蒙真机上实际确认中文文案与图标均正常渲染（而非空白/占位框）。

**[已关闭的风险] Android 端 lifecycle 版本变更带来的既有行为差异**
→ 因决策 1 改为不引入任何依赖，`androidMain` 的 lifecycle `2.9.6` 保持不变，本仓依赖图与改动前完全一致。**该风险已关闭**。

**[取舍] 引入的假实现是一次性脚手架代码**
→ 后果：下一步接网络时会删除。已通过"单独成文件 + 不侵入 UI"把它限制为可整体删除的单元。

## Migration Plan

实施顺序如下。原方案第 1 步的依赖冒烟门禁**已执行并失败**，故实际起点从第 2 步开始。

1. ~~**依赖冒烟验证**（可失败门禁）~~ —— **已执行，门禁失败，方案已改为自写容器（见决策 1）**。该步骤现已无剩余工作：不引入任何依赖，无需验证依赖解析。
2. **迁移共享层**：token 三件套 + `PrimaryButton` / `PrimaryInput` / `LoadingView` + `UiState`。
3. **迁移资源**：8 个矢量 Drawable + 中英两套 `strings.xml`。
4. **迁移登录页**：假 Repository → 自写状态容器 → `LoginPage`。
5. **替换入口**：`App()` 渲染 `LoginPage`，删除 `Greeting.kt` 与 `compose-multiplatform.xml`。
6. **三端验证**：Android APK、iOS framework、鸿蒙 HAP 均需实际运行并比对视觉。

**回滚策略**：本次不再触碰依赖配置，唯一的全局影响点消失。第 2–6 步均为新增文件，删除即回滚；唯一的破坏性改动是 `App.kt` 与两个模板文件的删除，可用 `git checkout` 还原。第 1 步已执行的 revert 已完成并验证（工作区与改动前一致）。
