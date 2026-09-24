package com.example.kmpoh.page.profile

import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import com.example.kmpoh.page.main.MainTabPlaceholder
import com.example.kmpoh.ui.components.PrimaryButton
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.str_main_placeholder_logout
import kmpoh.composeapp.generated.resources.str_main_tab_profile
import org.jetbrains.compose.resources.stringResource

/**
 * 「我的」页单元（spec ui/home-shell「tab 迁移占位内容」「占位期退出登录入口」）：
 * 占位期渲染迁移占位 + 临时退出登录入口（后续由「我的」业务页的退出登录能力替换）。
 * MVVM 接缝：[ProfileViewModel] 由页面默认参数 remember 持有。
 */
@Composable
fun ProfilePage(
    onLogout: () -> Unit,
    modifier: Modifier = Modifier,
    viewModel: ProfileViewModel = remember { ProfileViewModel() }
) {
    MainTabPlaceholder(
        moduleName = stringResource(Res.string.str_main_tab_profile),
        modifier = modifier,
        action = {
            PrimaryButton(
                text = stringResource(Res.string.str_main_placeholder_logout),
                onClick = onLogout
            )
        }
    )
}
