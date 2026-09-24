package com.example.kmpoh.page.workorder

import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import com.example.kmpoh.page.main.MainTabPlaceholder
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.str_main_tab_workorder
import org.jetbrains.compose.resources.stringResource

/**
 * 「工单」页单元（spec ui/home-shell「tab 迁移占位内容」）：占位期渲染迁移占位，
 * 业务内容由后续变更整块替换。MVVM 接缝：[WorkOrderViewModel] 由页面默认参数 remember 持有。
 */
@Composable
fun WorkOrderPage(
    modifier: Modifier = Modifier,
    viewModel: WorkOrderViewModel = remember { WorkOrderViewModel() }
) {
    MainTabPlaceholder(
        moduleName = stringResource(Res.string.str_main_tab_workorder),
        modifier = modifier
    )
}
