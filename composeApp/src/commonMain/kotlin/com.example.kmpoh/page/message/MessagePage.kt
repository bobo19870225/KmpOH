package com.example.kmpoh.page.message

import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import com.example.kmpoh.page.main.MainTabPlaceholder
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.str_main_tab_message
import org.jetbrains.compose.resources.stringResource

/**
 * 「消息」页单元（spec ui/home-shell「tab 迁移占位内容」）：占位期渲染迁移占位。
 * 消息 tab 当前在 [com.example.kmpoh.page.main.MainPage] 注释停用、不可达；
 * 恢复=取消注释。MVVM 接缝：[MessageViewModel] 由页面默认参数 remember 持有。
 */
@Composable
fun MessagePage(
    modifier: Modifier = Modifier,
    viewModel: MessageViewModel = remember { MessageViewModel() }
) {
    MainTabPlaceholder(
        moduleName = stringResource(Res.string.str_main_tab_message),
        modifier = modifier
    )
}
