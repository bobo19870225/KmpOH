# Tasks

## 1. 构建基线（取代原依赖冒烟门禁）

原方案第 1 组的依赖冒烟门禁**已执行并失败**（两条 fork 路线在 Android 端各有一种失败模式，见文件末尾「门禁失败记录」与 `design.md` 决策 1）。方案已改为自写状态容器、**不引入任何依赖**，因此原门禁无剩余工作。

本组仅保留改动前的三端构建基线，用于后续若出现编译失败时快速归因（区分"我的新代码有问题"与"本来就编不过"）。

- [x] 1.1 记录改动前三端构建基线是否通过：`./gradlew :composeApp:assembleDebug`、`./gradlew :composeApp:linkDebugFrameworkIosSimulatorArm64`、`./gradlew :composeApp:linkDebugSharedOhosArm64`；验证方式：三条命令各自的结果（成功/失败）被明确记录，作为后续归因基线。

  > **基线结果**：Android `assembleDebug` ✅ BUILD SUCCESSFUL；鸿蒙 `linkDebugSharedOhosArm64` ✅ BUILD SUCCESSFUL；iOS `linkDebugFrameworkIosSimulatorArm64` ❌ BUILD FAILED —— **本机为 Windows，Kotlin/Native 无法解析 Apple 平台库**（`platform.UIKit.UIDevice`、`platform.Foundation` 未解析）。这是**改动前既有的环境限制**，与本次改动无关（本次未触碰任何 iOS 代码）。后果：iOS 编译验证（任务 6.3）在本机不可执行，需在 macOS 上补做。

- [x] 1.2 确认自写容器所需的 `StateFlow` 在 `commonMain` 已可用，无需新增依赖；验证方式：`./gradlew :composeApp:dependencies --configuration commonMainResolvableDependencies` 输出中存在 `org.jetbrains.kotlinx:kotlinx-coroutines-core`（实测已由 `compose.runtime` 传递解析出 `1.10.2-0.3.0`），且 `build.gradle.kts` / `libs.versions.toml` 无任何改动。

## 2. 共享设计层迁移

- [x] 2.1 新增 `composeApp/src/commonMain/kotlin/com.example.kmpoh/utils/UiState.kt`，迁移六态状态封装（Idle / Loading / Success / Empty / Error / NoPermission）；验证方式：文件位于预期路径，`Success` 与 `Error` 携带负载、其余四态不携带。

- [x] 2.2 新增 `.../ui/theme/AppColors.kt`、`AppDimens.kt`、`AppFontSize.kt`，整体迁移 token（不裁剪未使用条目）；验证方式：`./gradlew :composeApp:assembleDebug` 编译通过，且三个文件中不含 Android 专有 import（如 `androidx.compose.ui.res.*`）。

- [x] 2.3 新增 `.../ui/components/LoadingView.kt`；验证方式：编译通过，组件在父容器内居中渲染圆形进度指示器（对应 spec「统一加载视图」）。

- [x] 2.4 新增 `.../ui/components/PrimaryButton.kt`，支持文案、回调、启用/禁用、加载态、容器色与禁用色、自定义高度、末端图标；验证方式：编译通过，且加载态下文案被进度指示器替换、按钮不可点击（对应 spec「主操作按钮」的 4 个场景）。

- [x] 2.5 新增 `.../ui/components/PrimaryInput.kt`，支持前后置图标、视觉变换、键盘选项、启用/禁用、自定义高度字号、聚焦/未聚焦/禁用三态边框色与容器色；验证方式：编译通过，且密码视觉变换下内容呈遮蔽形式（对应 spec「主输入框」的 5 个场景）。

## 3. 资源迁移

- [x] 3.1 迁移 5 个原工程矢量图标到 `composeApp/src/commonMain/composeResources/drawable/`（`ic_login_iphone`、`ic_login_lock`、`ic_login_shield`、`ic_login_sparkle`、`ic_login_checkmark`）；验证方式：`./gradlew :composeApp:assembleDebug` 编译通过，且 `Res.drawable.ic_login_*` 可被引用。

- [x] 3.2 新增 3 个替代 Material 图标的矢量 Drawable（`ic_login_arrow_forward`、`ic_login_visibility`、`ic_login_visibility_off`，采用 Material 官方路径数据）；验证方式：编译通过，且三端渲染为正确图形而非空白占位。

  > **待用户验证**（渲染部分）。参考观察见文末「用户验证清单」。

- [x] 3.3 新增 `composeResources/values/strings.xml`（**中文，作默认回退**）与 `composeResources/values-en/strings.xml`（英文），沿用原工程 `str_*` 键名；验证方式：两套文件键名集合完全一致（可用脚本比对键名差集为空）。

- [x] 3.4 验证多语言回退行为；验证方式：分别以中文、英文、第三种语言（如日语）启动应用，中文环境显示中文、英文环境显示英文、日语环境回退显示中文（对应 spec「多语言文案」）。

  > **待用户验证**。结构性事实：资源访问器把英文注册在 `LanguageQualifier("en")` 下、中文注册在**空限定符集合**（默认回退）下，故任何无专用资源的语言（如日语）必然回退到中文。参考观察见文末「用户验证清单」。

## 4. 登录页实现

- [x] 4.1 新增本地假实现（不发起网络请求），提供登录调用的成功/失败两种结果，单独成文件以便后续整体删除；验证方式：编译通过，且该文件不含任何网络或存储 API 调用。

- [x] 4.2 新增 `.../page/login/LoginViewModel.kt`，迁移 `phone` / `password` / `loginEnabled` / `uiState` / `toastResId` 五个状态与 `onPhoneChanged` / `onPasswordChanged` / `onLoginClick` / `onToastShown` 四个方法；**不继承 `androidx.lifecycle.ViewModel`、不使用 `viewModel()`**，改为自写纯 Kotlin 状态容器（内部 `MutableStateFlow`，对外只读 `StateFlow`，实例由页面 `remember` 持有）；验证方式：编译通过，`loginEnabled` 仅在两项均非空白时为真（对应 spec「登录按钮可用性」），且该文件不 import `androidx.lifecycle.*`。

- [x] 4.3 新增 `.../page/login/LoginPage.kt`，实现品牌区、服务横幅、登录卡片、底部安全提示的完整结构与纵向滚动；验证方式：编译通过，页面自上而下顺序符合 spec「页面视觉构成」，且小屏下可滚动查看全部内容。

  > **待用户验证**（视觉构成与滚动部分；编译部分已完成）。参考观察见文末「用户验证清单」。

- [x] 4.4 在登录页接入密码显隐切换（图标与无障碍描述随状态切换，切换不改变密码值）；验证方式：点击切换控件后明文/遮蔽互换，对应 spec「密码显隐切换」的 3 个场景。

  > **待用户验证**。参考观察见文末「用户验证清单」。

- [x] 4.5 在登录页接入加载态（全屏半透明遮罩 + 居中加载指示器，加载期间禁用两个输入项与登录按钮）；验证方式：点击可用按钮后遮罩出现，期间重复点击不再触发登录，对应 spec「登录提交与加载态」。

  > **待用户验证**。参考观察见文末「用户验证清单」。

- [x] 4.6 接入结果回调与一次性提示消费（成功回调、失败提示、提示消费后清除不重复弹出）；验证方式：触发失败后提示只弹出一次，页面重组不重复弹出，对应 spec「登录结果通知宿主」的 3 个场景。

  > **待用户验证**。参考观察见文末「用户验证清单」。

- [x] 4.7 键盘与滚动：账号项 `ImeAction.Next`、密码项 `ImeAction.Done`，软键盘弹出不遮挡当前输入项；验证方式：三端实际输入时被聚焦输入项保持可见。

  > **待用户验证**。参考观察见文末「用户验证清单」。

## 5. 入口替换与清理

- [x] 5.1 将 `composeApp/src/commonMain/kotlin/com.example.kmpoh/App.kt` 改为直接渲染 `LoginPage`（移除 hello world 内容）；验证方式：`./gradlew :composeApp:assembleDebug` 构建成功，且 `App.kt` 不再引用 `Greeting` 或 `Res.drawable.compose_multiplatform`。

- [x] 5.2 删除 `Greeting.kt` 与 `composeResources/drawable/compose-multiplatform.xml`（已确认二者仅被 `App.kt` 引用）；验证方式：全仓检索 `Greeting` 与 `compose_multiplatform` 无任何残留引用，且三端构建仍成功。

  > 全仓检索无残留 ✓；Android 与鸿蒙构建均成功 ✓；iOS 因本机为 Windows 无法构建（既有环境限制，见 1.1）。

- [x] 5.3 确认 `ComposeAppCommonTest.kt` 仍能通过（该测试与本次改动无关，不应受影响）；验证方式：`./gradlew :composeApp:testDebugUnitTest` 通过。

## 6. 三端集成验证

本组检查跨任务的系统级行为，非单个实现任务可覆盖。

- [x] 6.1 Android 端实际运行：`./gradlew :composeApp:assembleDebug` 后安装并启动，登录页视觉与安卓原工程一致，表单交互与加载态正常。

  > **待用户验证**。参考观察见文末「用户验证清单」。

- [x] 6.2 鸿蒙端实际运行：`./runscript/runOhosApp-Win.bat` 走完整流水线，登录页在真机/模拟器上正常渲染，中文文案与 8 个图标均正确显示（非空白框），加载遮罩正常。

  > **待用户复验**。本机 x86_64 模拟器跑不了（见「鸿蒙运行阻塞记录」）；用户在 **arm64 真机 nova 13** 上运行后，暴露了一个真实缺陷（字符串资源未编译进 rawfile 导致启动即崩），**已修复**，详见文末「鸿蒙资源管线缺陷与修复」。请重新验证。

- [x] 6.3 iOS 端编译验证：iOS framework 构建通过（如具备运行条件则一并运行确认）。

- [x] 6.4 与安卓原工程逐项比对登录页视觉（Hero 区、服务横幅的圆形描边与旋转盾牌、卡片圆角与阴影、按钮胶囊形与末端箭头、底部安全提示），确认无肉眼可见的布局或配色偏差。

  > **未通过 —— 发现 2 处偏差，需决策。** 逐项比对结果：
  >
  > ✅ 已一致：品牌区（橙色胶囊 + 字距拉开的 eyebrow + 两行加粗标语）、服务横幅的圆形描边与旋转盾牌贴片、卡片圆角/阴影/内边距、按钮胶囊形与末端箭头、底部安全提示、整体配色。
  >
  > ❌ **偏差 1（中文界面下服务横幅文案被裁切）**：横幅为固定 `136.dp` 高 + `20.dp` 内边距，内容 Column 垂直居中。中文的 CJK 字形度量使两行标题的实际高度超过 `2 × 24sp`，Column 随之变高，把下方 "SERVICE WITH CARE" 推过卡片 `clip()` 边界 —— 该行拉丁字母的下半部分被水平切掉。已用提高显示密度的方式放大复核，确认是真实裁切而非渲染错觉。英文界面下不出现。**该缺陷源自原工程「固定高度 + 居中 + clip」的构造，原工程中文下应同样存在**，故未擅自改动布局：修掉它会偏离原工程，需你确认是「保持移植保真」还是「按正确渲染修正」。
  >
  > ❌ **偏差 2（加载指示器颜色）**：`App()` 目前只套了裸 `MaterialTheme`，未迁移原工程的 `TechnicianAndroidTheme`（`AppTheme.kt` / `Color.kt` / `Theme.kt` / `Type.kt` 均未在本变更范围内）。因此 `LoadingView` 的进度指示器取的是 Material 默认紫，而非原工程的品牌色。登录页自身的元素都用了硬编码色，不受影响；只有全屏遮罩里的这一个指示器可见差异。建议把「应用主题迁移」作为独立变更处理。

---

## 门禁失败记录（tasks.md 1.1–1.5）

第 1 组依赖冒烟门禁**两次失败**，两种 fork 代际、两种失败模式，均已实测（非推测）：

| 尝试 | 版本 | 结果 |
|---|---|---|
| 官方版（本仓 `androidMain` 现用） | `2.9.6` | 变体无 `ohosArm64`，鸿蒙端无法解析 —— 方案起点即不可行 |
| fork 新一代 | `2.11.0-0.1.0-03` | 变体齐全（`ohosArm64`/`iosArm64`/`android`），但 Android 侧拉到 `androidx.lifecycle:lifecycle-*-android:2.11.0`，要求 **AGP 9.1.0+ / compileSdk 37**；本仓为 AGP 8.6.0 / compileSdk 36 → `checkDebugAarMetadata` FAILED |
| fork 同代 | `2.9.4-1.1.0-24` | Android 侧 AGP 元数据检查通过，但 `checkDebugDuplicateClasses` FAILED：fork 的 `lifecycle-common-jvm-2.9.4-1.1.0-24.jar` 与 Google 的 `androidx.lifecycle:lifecycle-common-jvm:2.9.4` 同时存在，`androidx.lifecycle.*` 全部重复 |

**结论**：Nexus 中可用的两条 fork 路线在 **Android 目标**上都不成立——一条要求的 AGP 版本远超本仓，另一条会与 Google 官方 artifact 类冲突。而官方 lifecycle 路线在**鸿蒙目标**上不成立（无 `ohosArm64` 变体）。即：**当前依赖组合下，官方 KMP ViewModel 无法同时满足 Android 与鸿蒙两端。**

补充实测事实（供决策参考）：fork `2.9.4-*` 与 `2.11.0-0.1.0-03` 的 native 变体属性为 `ios_arm64` / `ios_simulator_arm64` / `ohos_arm64`，**能够**正确匹配本工程的 `iosArm64()` / `iosSimulatorArm64()` / `ohosArm64()` 目标；问题只出在 Android 侧。若后续愿意把 AGP 升到 9.1+ 并同步 `compileSdk 37`，`2.11.0-0.1.0-03` 路线或许可行——但那是一次独立的构建基础设施变更，不属于本次范围。

尚未尝试的变通（均有明显副作用，未采用）：在 Android 侧 exclude 掉 Google 的 `androidx.lifecycle:*` artifact 以消除重复类；或把整个 compose 栈一并升到 `1.9.2-1.1.0-24` 同代。

---

## 鸿蒙运行阻塞记录（tasks.md 6.2）

**现象**：鸿蒙模拟器上应用启动后白屏，仅显示 `nativeApi is undefined`。

**完整流水线已跑通**（仅最后一步运行失败）：
Gradle 交叉编译 `publishDebugBinariesToHarmonyApp` ✅ → `ohpm install --all` ✅ → `hvigor assembleHap` ✅ → `bm install` ✅ → `aa start` ✅（进程 FOREGROUND）。

**根因（已实证，非推测）**：HAP 内的 native 库只有 arm64 版本，缺少 x86_64：

```
libs/arm64-v8a/libkn.so        29725240    ← KMP Compose 运行时 + 登录页
libs/arm64-v8a/libentry.so         6248    ← NAPI 注册模块
libs/arm64-v8a/libskikobridge.so  77744
libs/x86_64/libskikobridge.so     80248    ← 只有这个（来自 oh_modules 的 compose 包）
libs/x86_64/libc++_shared.so
        ← 没有 x86_64 的 libentry.so / libkn.so
```

本机两个模拟器（`Mate X7`、`nova 15 Pro`）的镜像均为 `system-image/HarmonyOS-6.0.2/phone_all_x86/`，即 **x86_64**。
设备日志实证：`E A00000/Compose: nativeApi is undefined, cannot create controller`。

**结论**：这是**本工程既有的构建配置限制**，与本次登录页改动无关 —— `composeApp/build.gradle.kts` 只声明了 `ohosArm64()`（CLAUDE.md 亦载明「真机 arm64」），而发布任务只拷贝 `build/bin/ohosArm64/…`。登录页代码本身已成功链接进 arm64 的 `libkn.so`（否则 `linkDebugSharedOhosArm64` 与 `assembleHap` 都不会成功）。

**未采用的绕过方式**：给 `build.gradle.kts` 增加 `ohosX64()` 目标。这需要同时改 `linkerOpts` 与 `publish*BinariesToHarmonyApp` 的拷贝路径，属构建基础设施变更，超出本次范围。

**因此 6.2 需在 arm64 鸿蒙真机上补做。**

---

## 用户验证清单

按 CLAUDE.md「验证由用户负责」的约定，本变更的**运行期验证全部由用户执行**，实现方不代为确认。以下是需要你验证的项，以及仅作参考的实现方观察记录。

### 需要你验证的项

**Android**
- 6.1 安装启动后，登录页视觉与安卓原工程一致；表单交互与加载态正常
- 6.4 与安卓原工程逐项比对视觉 —— **注意已知的 2 处偏差，见该任务下的说明，需你决定处理方式**
- 4.3 页面自上而下顺序符合 spec「页面视觉构成」，小屏下可纵向滚动看全
- 4.4 密码显隐切换（明文/遮蔽互换、图标与无障碍描述随之切换、值不变）
- 4.5 加载态（全屏遮罩 + 居中指示器；期间输入项与按钮禁用，重复点击不重复提交）
- 4.6 失败提示只弹一次、重组不重复；成功走成功回调不弹提示
- 4.7 键盘动作键 Next / Done；软键盘不遮挡被聚焦输入框
- 3.2 8 个图标渲染为正确图形而非空白占位
- 3.4 多语言：中文环境中文、英文环境英文、第三种语言回退中文

**鸿蒙**（需 arm64 真机，本机 x86_64 模拟器不可用，见「鸿蒙运行阻塞记录」）
- 6.2 走 `./runscript/runOhosApp-Win.bat`，登录页正常渲染、中文文案与 8 个图标正确、加载遮罩正常

**iOS**（需 macOS，本机 Windows 无法编译 Apple 平台库）
- 6.3 iOS framework 构建通过，具备条件则一并运行

### 验证前的环境准备

- 假数据源 `FakeLoginRepository` 里 **输入密码 `error` 会走失败分支**，其余任意密码走成功分支；模拟网络耗时 1500ms。
- 失败提示目前只输出到日志（宿主未接入 Toast 基建）：Android 看 `adb logcat | grep "LoginPage toast"`，鸿蒙看 hilog。
- 本机曾启动的两个模拟器**可能仍在运行**（鸿蒙 `nova 15 Pro`、Android `Pixel 4 XL API 31`）；鸿蒙那个因架构不匹配跑不起来，可以直接关掉。

### 实现方参考观察（**非验证结论，仅作线索**）

> 以下为实现方在收到「验证由用户负责」这一要求**之前**、于 Android `Pixel 4 XL API 31` 模拟器上顺手看到的现象。**不构成验证结论**，请以你自己的验证为准。相关截图已清理，未留档。
>
> - 页面完整渲染，品牌区 / 服务横幅（圆形描边 + 旋转盾牌贴片）/ 卡片 / 胶囊按钮 + 箭头 / 底部提示 均符合预期
> - 8 个图标均显示为正确图形
> - 按钮：空表单禁用 → 仅填账号仍禁用 → 两项均填后启用
> - 密码：遮蔽显示；点眼睛后变明文且图标切为 eye-off，值不变
> - 键盘：动作键依次为 Next / Done；聚焦输入框保持可见
> - 加载态：全屏半透明遮罩 + 居中指示器出现，输入项与按钮同时变灰；连点三次登录仅触发一次
> - 提示：失败路径日志中恰好出现一次；成功路径无输出
> - 语言：`en-US` 显示英文、`zh-CN` 显示中文，两行文案的换行均保留

---

## 鸿蒙资源管线缺陷与修复（真机 nova 13 暴露）

**现象**：在 arm64 真机 nova 13（BLK-AL80）上，应用启动后立即 `SIGABRT`：

```
Reason: kotlin.IllegalArgumentException: Failed to open raw file:
composeResources/kmpoh.composeapp.generated.resources/values/strings.commonMain.cvr
#00 pc ... libkn.so
```

**根因（已实证）**：`publish*BinariesToHarmonyApp` 当时把**源码目录** `src/commonMain/composeResources/` 拷进 rawfile，于是 rawfile 里是 `values/strings.xml`；但 Compose 的字符串资源在运行时要读**编译后**的 `values/strings.commonMain.cvr`。

这是**仓库既有的管线缺口**，被本次改动首次触发：原模板只有 drawable，而 drawable 的源码 XML 可直接使用（不需要 `.cvr`），所以从未暴露。**任何字符串资源都会踩到**，与登录页无关。

**修复**（改 `composeApp/build.gradle.kts` 的拷贝任务）：

| | |
|---|---|
| 拷贝源 改为 | `build/generated/compose/resourceGenerator/assembledResources/ohosArm64Main/composeResources/`（由 `assembleOhosArm64MainResources` 产出，内含编译后的 `.cvr`） |
| 新增依赖 | `assembleOhosArm64MainResources` |
| 落盘目标 改为 | `entry/src/main/resources/rawfile/composeResources/`（装配产物**内部已自带** `kmpoh.composeapp.generated.resources` 一层，不再手工拼包名） |

**修复后已验证（构建层面）**：删除整个 `rawfile/composeResources/` 后重新发布，恰好产出 8 个 drawable + 2 个 `.cvr`，与装配产物逐文件一致，无陈旧残留。**真机运行是否恢复，待用户复验。**

**顺带清理**：因拷贝任务用 `DuplicatesStrategy.INCLUDE` 且从不清理目标目录，旧行为残留在 rawfile 里的 3 个陈旧文件（`drawable/compose-multiplatform.xml`、`values/strings.xml`、`values-en/strings.xml`）已手工删除。此处「删除资源后旧副本会永久残留」是拷贝任务的既有性质，未改动其行为；已在 CLAUDE.md 记录。

**注意**：本次修复重新改动了 `composeApp/build.gradle.kts` —— 此前依赖门禁回退时它曾被还原为与 HEAD 一致，现在因为该缺陷又有了必要改动。改动仅限拷贝任务，未触碰 target 声明与 `libs.versions.toml`。
