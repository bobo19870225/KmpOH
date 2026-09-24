package com.example.kmpoh.page.main

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.kmpoh.ui.theme.AppColors
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.str_main_placeholder_message
import org.jetbrains.compose.resources.stringResource

/**
 * tab 迁移占位（spec ui/home-shell「tab 迁移占位内容」）：仅静态文案，
 * 不建 ViewModel、不发业务请求（design 决策 6）。业务迁移时整块替换。
 * [action] 供占位期临时入口使用（如「我的」的退出登录，spec ui/home-shell「占位期退出登录入口」）。
 */
@Composable
fun MainTabPlaceholder(
    moduleName: String,
    modifier: Modifier = Modifier,
    action: @Composable (() -> Unit)? = null
) {
    Column(
        modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(moduleName, color = AppColors.PaletteFF101826, fontSize = 20.sp, fontWeight = FontWeight.Bold)
        Spacer(Modifier.height(8.dp))
        Text(stringResource(Res.string.str_main_placeholder_message), color = AppColors.PaletteFFAEB6C3, fontSize = 13.sp)
        if (action != null) {
            Spacer(Modifier.height(24.dp))
            action()
        }
    }
}
