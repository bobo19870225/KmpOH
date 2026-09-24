package com.example.kmpoh.router

import kotlinx.serialization.Serializable

/**
 * 类型安全路由目标（对齐原工程 router/NavGraph.kt 的 `AppDestination.*` + `toRoute<T>()` 模式）。
 * 后续业务页面在此追加目标；既有目标的跳转与返回栈语义不变（spec ui/navigation）。
 */
@Serializable
sealed interface AppDestination {

    /** 登录页（应用起始路由；Splash 未迁，见变更非目标）。 */
    @Serializable
    data object Login : AppDestination

    /** 主框架页（底部三 tab 壳，spec ui/home-shell）。 */
    @Serializable
    data object Main : AppDestination
}
