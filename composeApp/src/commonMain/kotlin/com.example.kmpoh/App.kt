package com.example.kmpoh

import androidx.compose.material3.MaterialTheme
import androidx.compose.runtime.Composable
import com.example.kmpoh.logger.Logger
import com.example.kmpoh.page.login.LoginPage

@Composable
internal fun App() {
    MaterialTheme {
        LoginPage(
            onLoginSuccess = {
                // 导航接缝：下一步引入路由后，在此跳转技师工作台。
                // 当前无导航框架，登录成功后页面停留在原处（加载态已结束）。
            },
            onToastMessage = { message ->
                // 宿主尚未接入 Toast 基建（原工程由 MainActivity 弹 Android Toast）。
                // 当前仅输出到日志（Android logcat / 鸿蒙 hilog），
                // 便于在真机上确认"失败提示只消费一次、重组不重复弹出"。
                Logger.debug("LoginPage toast: $message")
            }
        )
    }
}
