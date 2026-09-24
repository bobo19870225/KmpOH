package com.example.kmpoh.page.workorder

/**
 * 「工单」页 ViewModel 空壳（MVVM 结构先行）：形态对齐
 * [com.example.kmpoh.page.login.LoginViewModel]——自写纯 Kotlin 状态容器
 * （对外只读 StateFlow）、不引 androidx.lifecycle。业务状态随工单迁移填充
 * （当前占位期零状态，沿用 home-shell design 决策 6）。
 */
class WorkOrderViewModel
