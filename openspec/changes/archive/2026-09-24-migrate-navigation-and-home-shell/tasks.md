# Tasks

## 1. 依赖与构建基线

- [x] 1.1 记录改动前构建基线：`./gradlew :composeApp:assembleDebug`、`./gradlew :composeApp:linkDebugSharedOhosArm64` 的结果；iOS 编译在 Windows 不可执行（沿用既有环境阻塞结论），如实记录即可。

  > **基线结果**（2026-09-24）：Android `assembleDebug` 与鸿蒙 `linkDebugSharedOhosArm64` 同轮 Gradle 调用 ✅ BUILD SUCCESSFUL（42s，EXIT=0）。iOS 编译在 Windows 不可执行（Kotlin/Native 无法解析 Apple 平台库，既有环境限制，本次未触碰 iOS 代码）。

- [x] 1.2 在 `gradle/libs.versions.toml` 与 `commonMain.dependencies` 引入 `org.jetbrains.androidx.navigation:navigation-compose`（fork 线 `2.10.0-0.1.0-xx`，与 CMP `1.9.2-0.3.0` 不兼容时在该线降号重试并记录取号结论）；验证方式：`./gradlew :composeApp:dependencies --configuration commonMainResolvableDependencies` 输出含 `navigation-compose`，且 `assembleDebug` / `linkDebugSharedOhosArm64` 编译通过（解析器须能取到 `ohosArm64` 变体）。

  > **取号结论**（2026-09-24）：`2.10.0-0.1.0-04` 解析通过但 **AAR metadata 检查失败**——传递绑定 `androidx.navigation:*-android:2.10.0-alpha05`，要求 compileSdk 37（本工程 android-36，AGP 8.6.0）；降号 `-03` 的 POM 同样钉死 upstream `2.10.0-alpha05`（同一堵墙），故 **2.10.0-0.1.0-xx 线整体不可用**。改用 fork 快照线 **`2.9.4-20260525000011`**（nexus 实测含 `navigation-compose-ohosarm64`/`navigation-runtime-ohosarm64`，上游 2.9.x 编译要求 ≤36，同源 Kotlin 2.2.21），`commonMainResolvableDependencies` 解析含 `navigation-compose`，`assembleDebug` + `linkDebugSharedOhosArm64` ✅ BUILD SUCCESSFUL（4m39s）。

## 2. 导航框架

- [x] 2.1 新增 `composeApp/src/commonMain/kotlin/com.example.kmpoh/router/AppDestination.kt`：`@Serializable` 路由目标 `Login` / `Main`（对齐原工程 `AppDestination.*` 命名习惯）；验证方式：编译通过，两目标均为无参可序列化对象。

- [x] 2.2 新增 `.../router/AppNavGraph.kt`：`NavHost` 装配，`startDestination = Login`；登录成功 → `Main` 时把 `Login` 移出返回栈（`popUpTo(Login) { inclusive = true }`）；登出/登录失效 → `Login` 时清空整个返回栈（等价 `popUpTo(0) { inclusive = true }`，后续栈上叠业务页时同样不留残留）；验证方式：编译通过，且跳转调用点的 popUpTo 语义与本条一致（代码审阅）。

- [x] 2.3 改造 `.../App.kt`：`App()` 挂 `AppNavGraph`，`LoginPage(onLoginSuccess)` 空接缝接上导航到 `Main`（删除「当前无导航框架」注释）；验证方式：编译通过，`App.kt` 不再存在空接缝注释。

- [x] 2.4 核查 `AuthSessionManager` 是否具备清除会话令牌的入口，缺失则补（供登出使用）；验证方式：存在清除令牌的方法且清除后读取令牌为空（有既有测试形态则补对应用例）。

  > **核查结论**：`clearTokens()` 已存在（`AuthSessionManager.kt`），无需补 API；按既有测试形态（`FakeKeyValueStore` + kotlin.test）补 `AuthSessionManagerTest.clearTokensRemovesAccessAndRefreshTokens`。另：装配收敛为 `AppGraph` 单例（`LoginRepository.kt`），登录链路与 `App()` 订阅共享同一 `AuthSessionManager` 实例，否则 4.2 的事件流接不上。

## 3. 首页壳

- [x] 3.1 新增 `.../page/main/MainPage.kt`：`Scaffold` + 底部 `NavigationBar`（工单 / 消息 / 我的 三项），`selectedTab` 壳内状态切换内容区（不走路由）；验证方式：编译通过，三项顺序与默认选中工单符合 spec「主框架壳结构」。

- [x] 3.2 新增无状态占位组件（`MainTabPlaceholder`，放 `page/main/`）：展示模块名与「迁移中」提示；验证方式：编译通过，三个 tab 内容区均经该组件渲染，文件不含 ViewModel / 网络调用。

- [x] 3.3 新增 3 个自备矢量图标 `composeResources/drawable/ic_tab_workorder.xml`、`ic_tab_message.xml`、`ic_tab_profile.xml`（对齐 `ic_login_*` 的 Android VectorDrawable 迁移形态）；验证方式：编译通过且 `Res.drawable.ic_tab_*` 可引用。

  > **待用户验证**（三端图形渲染部分）。

- [x] 3.4 新增文案 `str_main_tab_workorder` / `str_main_tab_message` / `str_main_tab_profile` / `str_main_placeholder_*`（占位说明与退出登录），中文落 `values/strings.xml`、英文落 `values-en/strings.xml`，键名集合一致；验证方式：两套文件键名差集为空（脚本比对）。

- [x] 3.5 `ui/theme/AppColors.kt` 补导航色值（选中 `#1D6F86`、未选 `#AEB6C3`、指示条 `#EAF1F4`，命名对齐既有 `Palette*` 惯例）；验证方式：编译通过，`MainPage` 引用 token 而非内联色值。

  > **核查结论**：三个色值已存在（`PaletteFF1D6F86` / `PaletteFFAEB6C3` / `PaletteFFEAF1F4`，设计 token 时整体迁入），零补充；`MainPage` 引用 token，无内联色值。

## 4. 登出回流与 401 接线

- [x] 4.1 「我的」占位页放临时「退出登录」按钮：清除会话令牌（2.4 的入口）+ 导航回 `Login`（清 `Main` 栈）；验证方式：编译通过，点击回调串联「清令牌 → 跳转」两步（代码审阅）。

- [x] 4.2 `App()` 层订阅 `AuthSessionManager` 登录失效事件流：收到事件即导航回 `Login` 并清空返回栈；验证方式：编译通过，订阅在 UI 装配层、网络层无 `NavController` 依赖（分层检查）。

- [x] 4.3 全量单测回归：`./gradlew :composeApp:testDebugUnitTest` 全绿（既有 60 条不回归；视图装配按既定口径不做 JVM 单测）。

  > **结果**：BUILD SUCCESSFUL（含新增 `AuthSessionManagerTest` 1 条，共 61 条 0 失败）。

## 5. 构建流水线与交付

- [x] 5.1 `./gradlew :composeApp:assembleDebug`、`:composeApp:publishDebugBinariesToHarmonyApp`、`devecocli build`（harmonyApp 打 HAP）全部成功；验证方式：各命令 BUILD SUCCESSFUL。

  > **结果**（2026-09-24）：`assembleDebug` + `linkDebugSharedOhosArm64` ✅（2m32s）；`publishDebugBinariesToHarmonyApp` ✅（2s）；`devecocli build` ✅（33 tasks，含 PackageHap/SignHap，产物 `harmonyApp/entry/build/default/outputs/default/entry-default-signed.hap`）。

- [ ] 5.2 登录跳转与返回栈实机验证；验证方式：登录成功进主框架、主框架按返回键不回登录页。

  > **待用户验证**。

- [ ] 5.3 tab 切换与占位实机验证；验证方式：三项可切换、选中态可见、占位文案随系统语言中英切换。

  > **待用户验证**。

- [ ] 5.4 登出与 401 回流实机验证；验证方式：「我的」退出登录回登录页且再发请求不带令牌；（可选）伪造 401 响应确认自动回登录页。

  > **待用户验证**。

## 6. tab 页面单元抽离与消息暂隐藏（2026-09-24 增补）

- [x] 6.1 新增 `page/workorder/WorkOrderPage.kt` + `WorkOrderViewModel.kt`、`page/message/MessagePage.kt` + `MessageViewModel.kt`、`page/profile/ProfilePage.kt` + `ProfileViewModel.kt`：页面单元复用 `MainTabPlaceholder`（「我的」含退出登录 action），ViewModel 为空壳状态容器（对齐 LoginViewModel 样板：纯 Kotlin、不引 androidx.lifecycle，页面默认参数 `remember` 持有）；验证方式：编译通过，VM 空壳文件不含 `androidx.lifecycle` import。

- [x] 6.2 `MainPage.kt` 瘦身为纯壳：tabs 列表 + `when` 分发到页面单元；消息项与消息分支注释停用（对齐原工程停用 DataCenter 写法），可见 tab 为工单/我的；验证方式：编译通过，代码审阅注释保留可恢复。

- [x] 6.3 全量单测回归 + 双端编译 + `publishDebugBinariesToHarmonyApp` + `devecocli build`；验证方式：各命令 BUILD SUCCESSFUL。

  > **结果**（2026-09-24）：`testDebugUnitTest` + `assembleDebug` + `linkDebugSharedOhosArm64` ✅（2m39s）；`publishDebugBinariesToHarmonyApp` ✅；`devecocli build` ✅（HAP 已签名）。

- [ ] 6.4 实机验证：底部仅工单/我的两 tab、切换正常、「我的」含退出登录、消息不出现在导航。

  > **待用户验证**。

## 7. 启动自动登录（2026-09-24 增补）

- [x] 7.1 起始路由按会话判定：`AppNavGraph` 的 `startDestination` 参数化，`App()` 以 `AppGraph.session.accessToken()` 非空 → `Main`、空 → `Login`（对齐原工程 Splash 二分语义，决策 8）；验证方式：编译通过，代码审阅判定与返回栈语义（Main 起步时返回键不进入登录页）。

- [x] 7.2 工件同步：`ui/navigation`「类型安全路由骨架」按会话二分改写、`design.md` 决策 8、`proposal.md` 范围同步（本组已随实施完成）；验证方式：工件与实现一致。

- [x] 7.3 全量单测回归 + 双端编译 + `publishDebugBinariesToHarmonyApp` + `devecocli build`；验证方式：各命令 BUILD SUCCESSFUL。

  > **结果**（2026-09-24）：`testDebugUnitTest` + `assembleDebug` + `linkDebugSharedOhosArm64` + `publishDebugBinariesToHarmonyApp` ✅（3m2s）；`devecocli build` ✅（HAP 已签名）。

- [ ] 7.4 实机验证自动登录；验证方式：登录后杀进程重开直进主框架；登出后重开进登录页；（可选）token 失效自动回登录页。

  > **待用户验证**。

## 用户验证清单（汇总，均待用户验证）

1. 登录成功进入主框架，默认工单 tab。
2. 主框架按系统返回键不回登录页（按系统语义退出或保持）。
3. 底部工单/我的两 tab 可切换，选中色 `#1D6F86` + 指示条可见，切换不影响返回键行为（消息项不在导航中显示）。
4. 各 tab 显示迁移占位说明；中/英系统语言下文案正确（英文环境英文、其他语言回退中文）。
5. 「我的」退出登录：回登录页、返回键不回主框架、后续请求不带会话令牌。
6. （可选）触发 401 登录失效：自动回登录页无残留栈。
7. 三端 tab 图标渲染正常（Android / 鸿蒙实机；iOS 需 macOS 环境补验）。
8. 自动登录：登录后杀进程重开直进主框架；登出后重开进登录页；（可选）token 失效自动回登录页。
