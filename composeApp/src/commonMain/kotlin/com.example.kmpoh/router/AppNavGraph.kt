package com.example.kmpoh.router

import androidx.compose.runtime.Composable
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import com.example.kmpoh.logger.Logger
import com.example.kmpoh.page.login.LoginPage
import com.example.kmpoh.page.main.MainPage
import com.example.kmpoh.page.profile.ChangePasswordPage

/**
 * 登录成功进入主框架：Main 入栈、Login 移出返回栈（返回键不回登录页）。
 * spec ui/navigation「登录成功进入主框架」。
 */
internal fun NavHostController.navigateToMainAfterLogin() {
    navigate(AppDestination.Main) {
        popUpTo<AppDestination.Login> { inclusive = true }
    }
}

/**
 * 登出 / 登录失效 / 修改密码成功回登录页：清空整个返回栈（`popUpTo(0)` 惯用法），
 * 后续栈上叠业务页时同样不留残留。spec ui/navigation「登出回登录页」「登录失效自动回登录页」。
 */
internal fun NavHostController.navigateToLoginClearingStack() {
    navigate(AppDestination.Login) {
        popUpTo(0) { inclusive = true }
    }
}

/**
 * 应用导航图：Login / Main / ChangePassword 三目标，业务路由后续逐条挂接（design 决策 2）。
 * 起始路由由调用方按本地会话二分（决策 8：有会话 Main、无会话 Login）。
 */
@Composable
fun AppNavGraph(
    navController: NavHostController,
    startDestination: AppDestination
) {
    NavHost(navController = navController, startDestination = startDestination) {
        composable<AppDestination.Login> {
            LoginPage(
                onLoginSuccess = { navController.navigateToMainAfterLogin() },
                onToastMessage = { message -> Logger.debug("LoginPage toast: $message") }
            )
        }
        composable<AppDestination.Main> {
            MainPage(
                onLoggedOut = { navController.navigateToLoginClearingStack() },
                onNavigateToChangePassword = { navController.navigate(AppDestination.ChangePassword) }
            )
        }
        composable<AppDestination.ChangePassword> {
            ChangePasswordPage(
                onBack = { navController.popBackStack() },
                onToastMessage = { message -> Logger.debug("ChangePassword toast: $message") },
                // 修改密码成功清会话回登录（决策 5，spec「修改成功回登录页」）
                onPasswordChangedSuccess = { navController.navigateToLoginClearingStack() }
            )
        }
    }
}
