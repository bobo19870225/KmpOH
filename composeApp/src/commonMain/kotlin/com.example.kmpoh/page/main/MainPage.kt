package com.example.kmpoh.page.main

import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Icon
import androidx.compose.material3.NavigationBar
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.NavigationBarItemDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import com.example.kmpoh.page.message.MessagePage
import com.example.kmpoh.page.profile.ProfilePage
import com.example.kmpoh.page.workorder.WorkOrderPage
import com.example.kmpoh.ui.theme.AppColors
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.ic_tab_message
import kmpoh.composeapp.generated.resources.ic_tab_profile
import kmpoh.composeapp.generated.resources.ic_tab_workorder
import kmpoh.composeapp.generated.resources.str_main_tab_message
import kmpoh.composeapp.generated.resources.str_main_tab_profile
import kmpoh.composeapp.generated.resources.str_main_tab_workorder
import org.jetbrains.compose.resources.DrawableResource
import org.jetbrains.compose.resources.StringResource
import org.jetbrains.compose.resources.painterResource
import org.jetbrains.compose.resources.stringResource

private data class BottomTab(
    val labelRes: StringResource,
    val iconRes: DrawableResource,
)

/**
 * 主框架壳（spec ui/home-shell）：底部导航 + 内容区分发到各页面单元（page/workorder|message|profile）。
 * tab 切换为壳内状态、不走路由（design 决策 3，对齐原工程 MainPage 的 selectedTab）；
 * 内容区本期为迁移占位，业务由后续变更替换。无顶栏（原工程 TopAppBar 已注释停用）。
 *
 * 消息项暂不显示：注释停用（对齐原工程停用 DataCenter 的写法），恢复=取消注释。
 */
@Composable
fun MainPage(onLogout: () -> Unit) {
    var selectedTab by remember { mutableIntStateOf(0) }
    val tabs = listOf(
        BottomTab(Res.string.str_main_tab_workorder, Res.drawable.ic_tab_workorder),
//        BottomTab(Res.string.str_main_tab_message, Res.drawable.ic_tab_message),
        BottomTab(Res.string.str_main_tab_profile, Res.drawable.ic_tab_profile),
    )

    Scaffold(
        bottomBar = {
            NavigationBar(containerColor = AppColors.PaletteWhite) {
                tabs.forEachIndexed { index, tab ->
                    NavigationBarItem(
                        selected = selectedTab == index,
                        onClick = { selectedTab = index },
                        icon = {
                            Icon(
                                painter = painterResource(tab.iconRes),
                                contentDescription = stringResource(tab.labelRes)
                            )
                        },
                        label = { Text(stringResource(tab.labelRes)) },
                        colors = NavigationBarItemDefaults.colors(
                            selectedIconColor = AppColors.PaletteFF1D6F86,
                            selectedTextColor = AppColors.PaletteFF1D6F86,
                            unselectedIconColor = AppColors.PaletteFFAEB6C3,
                            unselectedTextColor = AppColors.PaletteFFAEB6C3,
                            indicatorColor = AppColors.PaletteFFEAF1F4,
                        ),
                    )
                }
            }
        }
    ) { padding ->
        when (selectedTab) {
            0 -> WorkOrderPage(modifier = Modifier.padding(padding))
//            1 -> MessagePage(modifier = Modifier.padding(padding))
            else -> ProfilePage(onLogout = onLogout, modifier = Modifier.padding(padding))
        }
    }
}
