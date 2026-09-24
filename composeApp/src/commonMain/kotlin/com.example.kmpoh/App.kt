package com.example.kmpoh

import androidx.compose.material3.MaterialTheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.navigation.compose.rememberNavController
import com.example.kmpoh.data.repository.AppGraph
import com.example.kmpoh.network.AuthSessionEvent
import com.example.kmpoh.router.AppNavGraph
import com.example.kmpoh.router.navigateToLoginClearingStack

@Composable
internal fun App() {
    MaterialTheme {
        val navController = rememberNavController()
        // 登录失效自动回登录页（spec ui/navigation）：事件在 UI 装配层消费，
        // 网络层保持无导航依赖（design 决策 4）。
        LaunchedEffect(navController) {
            AppGraph.session.events.collect { event ->
                when (event) {
                    is AuthSessionEvent.LoginExpired -> navController.navigateToLoginClearingStack()
                }
            }
        }
        AppNavGraph(navController = navController, authSession = AppGraph.session)
    }
}
