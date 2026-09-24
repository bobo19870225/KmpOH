# Tasks

## 1. 数据层（ProfileRepository 与密码规则）

- [ ] 1.1 新增 `data/model/dto/PasswordRulesDto.kt`、`data/model/entity/PasswordRulesEntity.kt` 与 mapper：原样迁原工程字段与防御式别名（长度字段 `minLength/minLen/passwordMin` 等）、空白规则剔除；验证方式：编译通过，mapper 不含 Android 专有 import。

- [ ] 1.2 （TDD）新增 `PasswordRulesEntity` 纯逻辑测试：长度区间从规则正则 `{m,n}` 提取、缺失时默认 6..50、`maxInputLength` 派生、别名字段映射；验证方式：先写失败用例再实现，`testDebugUnitTest` 全绿。

- [ ] 1.3 新增 `data/repository/ProfileRepository.kt`（方案 B 聚合）：`logout()`（服务端尽力而为、本地会话必清含用户名）、`changePassword(newPassword)`（明文 body）、`getPasswordRules()`（含兜底）、`loadPasswordStatus()`（`passStatus`，缺失默认 1）；验证方式：编译通过，走 `ApiGateway`（信封/签名/401 复用），`LoginRepository` 无改动。

- [ ] 1.4 `StorageKeys` 增用户姓名键，登录成功持久化姓名（对齐 `data/login` 扩充要求）；验证方式：登录成功后可读出姓名，登出/改密成功后读取为空（补 commonTest 用例）。

## 2. 「我的」页

- [ ] 2.1 `page/profile/ProfileViewModel.kt` 由空壳填充：`ProfileUiState` / `ProfileMenuItem` / `ProfileEffect.LoggedOut` 原样迁（自写容器 + `SharedFlow` 一次性事件）；displayName 读持久化姓名；`onLogoutClick()` 防重复 + 调 `ProfileRepository.logout()` 后发 `LoggedOut`；验证方式：编译通过，不含 `androidx.lifecycle` import。

- [ ] 2.2 `page/profile/ProfilePage.kt` 由占位替换为完整页：资料卡、系统设置菜单（含动态「修改密码」项）、退出登录按钮（`isLoggingOut` 禁用）；统计区/工作功能区/NFC 入口不迁（决策 7）；验证方式：编译通过，结构顺序与 spec「个人资料卡」「系统设置菜单」一致。

- [ ] 2.3 退出登录接线：`LoggedOut` 事件 → 导航清栈回登录（复用 `navigateToLoginClearingStack`）；验证方式：代码审阅事件消费在 UI 装配层。

- [ ] 2.4 `profile_*` 文案键族迁入 `values/strings.xml`（中文默认回退）与 `values-en/strings.xml`，键名沿用原工程；验证方式：两套键名差集为空（脚本比对）。

## 3. 修改密码页（新路由）

- [ ] 3.1 `AppDestination` 增 `ChangePassword` 路由目标并在 `AppNavGraph` 挂接（Main 栈上叠、返回 popBackStack、成功清栈回登录）；验证方式：编译通过，跳转语义与 spec「修改密码页导航」一致（代码审阅）。

- [ ] 3.2 （TDD）`ChangePasswordUiState` 纯逻辑测试：`canSubmit` / `passwordRuleError`（正则逐条 + 长度）/ `isConfirmMismatch` / `shouldShowConfirmMismatch`；验证方式：先写失败用例再实现，全绿。

- [ ] 3.3 `page/profile/ChangePasswordViewModel.kt` 填充：规则加载、输入截断（`maxInputLength`）、校验、`changePassword` 提交（成功清会话 + `passwordChanged` 一次性）、类型化文案枚举入 state（决策 2，VM 不引 Context）；验证方式：编译通过，VM 文件无 `androidx.*.R` / Context 引用。

- [ ] 3.4 `page/profile/ChangePasswordPage.kt`：TopAppBar（返回）、双密码框（显隐切换、规则说明、错误行）、提交按钮（加载态）、toast/文案映射 `stringResource`；新增自备矢量 `ic_back_arrow.xml`、`ic_password_lock.xml`；验证方式：编译通过且 `Res.drawable.*` 可引用。

  > **待用户验证**（图标渲染部分）。

- [ ] 3.5 `change_password_*` 文案键族迁入中英两套；验证方式：键名差集为空。

## 4. 强制改密提示

- [ ] 4.1 `page/main/MainViewModel.kt` 由空壳填充：`requiresPasswordChange` + `refreshPasswordStatus()`（调 `loadPasswordStatus`，进入 Main 路由时触发，决策 4）；验证方式：编译通过，不含 `androidx.lifecycle` import。

- [ ] 4.2 强制改密弹窗挂 `MainPage`：不可 dismiss +「去修改」导航 `ChangePassword`；验证方式：编译通过，`onDismissRequest` 不可关闭（代码审阅）。

## 5. 验证与交付

- [ ] 5.1 全量单测回归：`./gradlew :composeApp:testDebugUnitTest` 全绿（含 1.2/3.2/1.4 新增用例）。

- [ ] 5.2 `assembleDebug` + `linkDebugSharedOhosArm64` + `publishDebugBinariesToHarmonyApp` + `devecocli build` 全部成功；验证方式：各命令 BUILD SUCCESSFUL。

- [ ] 5.3 实机验证「我的」页与登出；验证方式：资料卡展示、菜单可点、登出回登录且返回栈干净、再发请求不带令牌。

  > **待用户验证**。

- [ ] 5.4 实机验证修改密码全链路；验证方式：规则提示、校验错误、成功回登录、失败留本页。

  > **待用户验证**。

- [ ] 5.5 实机验证强制改密提示；验证方式：`passStatus == 0` 时进主框架即弹、不可关闭、「去修改」进修改密码页、改密成功回登录后重登不再弹。

  > **待用户验证**。

## 用户验证清单（汇总，均待用户验证）

1. 「我的」tab：资料卡（头像首字/姓名/职称·工号/已认证）展示正确，姓名为登录时的姓名。
2. 系统设置菜单四项（含「修改密码」）展示正确；仅「修改密码」有跳转。
3. 退出登录：按钮点击后回登录页、返回键不回主框架、重复点击不重复登出。
4. 修改密码页：返回箭头回「我的」；规则说明展示；不满足规则/两次不一致时提示且无法提交；成功 toast 后回登录页；失败提示服务端文案且留在本页。
5. 强制改密：`passStatus == 0` 账号登录进入主框架即弹提示、点外部不可关闭、「去修改」进修改密码页；改密成功重登后不再弹。
6. 中/英系统语言下文案正确（英文环境英文、其他语言回退中文）。
7. 返回箭头与锁图标渲染正常（Android / 鸿蒙实机；iOS 需 macOS 环境补验）。
