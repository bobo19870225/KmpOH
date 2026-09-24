package com.example.kmpoh.page.profile

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.kmpoh.data.repository.AppGraph
import com.example.kmpoh.data.repository.createProfileRepository
import com.example.kmpoh.ui.theme.AppColors
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.profile_change_password
import kmpoh.composeapp.generated.resources.profile_change_password_desc
import kmpoh.composeapp.generated.resources.profile_id_format
import kmpoh.composeapp.generated.resources.profile_logout
import kmpoh.composeapp.generated.resources.profile_system_settings
import kmpoh.composeapp.generated.resources.profile_verified
import org.jetbrains.compose.resources.stringResource

private val Background = AppColors.PaletteFFF3F4F6
private val CardWhite = AppColors.PaletteWhite
private val TextPrimary = AppColors.PaletteFF111827
private val TextSecondary = AppColors.PaletteFF6B7280
private val VerifiedBg = AppColors.PaletteFFFFF8E1
private val VerifiedText = AppColors.PaletteFFD97706
private val ChevronGray = AppColors.PaletteFFD1D5DB
private const val CHANGE_PASSWORD_ITEM_ID = "change_password"

/**
 * 「我的」页（spec ui/profile）：资料卡 + 系统设置菜单 + 退出登录。
 * 统计区/工作功能区（原工程已注释停用）与 NFC 入口（NFC 域未迁）不迁（决策 7）。
 * 登出完成后经 [onLoggedOut] 交由导航层清栈回登录页（对齐原工程 effect→NavGraph 语义）。
 */
@Composable
fun ProfilePage(
    onLoggedOut: () -> Unit,
    onNavigateToChangePassword: () -> Unit,
    modifier: Modifier = Modifier
) {
    val scope = rememberCoroutineScope()
    val viewModel = remember { ProfileViewModel(createProfileRepository(), AppGraph.session, scope) }
    val state by viewModel.state.collectAsState()

    LaunchedEffect(viewModel) {
        viewModel.effect.collect { effect ->
            when (effect) {
                ProfileEffect.LoggedOut -> onLoggedOut()
            }
        }
    }

    val systemSettings = state.systemSettings + ProfileMenuItem(
        id = CHANGE_PASSWORD_ITEM_ID,
        titleRes = Res.string.profile_change_password,
        subtitleRes = Res.string.profile_change_password_desc,
        bgColor = 0xFFFFF5E6,
        iconTint = 0xFFD4943A,
        icon = "🔒"
    )

    Column(
        modifier = modifier
            .fillMaxSize()
            .background(Background)
    ) {
        Column(
            modifier = Modifier
                .weight(1f)
                .verticalScroll(rememberScrollState())
                .padding(horizontal = 16.dp)
                .padding(top = 16.dp, bottom = 24.dp),
            verticalArrangement = Arrangement.spacedBy(16.dp)
        ) {
            ProfileCard(state = state)

            MenuSection(
                title = stringResource(Res.string.profile_system_settings),
                items = systemSettings,
                onItemClick = { item ->
                    if (item.id == CHANGE_PASSWORD_ITEM_ID) {
                        onNavigateToChangePassword()
                    }
                }
            )

            LogoutButton(
                enabled = !state.isLoggingOut,
                onClick = viewModel::onLogoutClick
            )
        }
    }
}

/** 个人资料卡：头像首字 / 姓名 / 职称·工号 / 已认证徽章（spec「个人资料卡」）。 */
@Composable
private fun ProfileCard(state: ProfileUiState) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(24.dp))
            .background(CardWhite)
            .padding(vertical = 24.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Box(
            modifier = Modifier
                .size(80.dp)
                .clip(CircleShape)
                .background(AppColors.PaletteFF475569),
            contentAlignment = Alignment.Center
        ) {
            Text(
                state.avatarName,
                fontSize = 32.sp,
                fontWeight = FontWeight.Medium,
                color = CardWhite
            )
        }

        Spacer(Modifier.height(12.dp))

        Text(
            state.displayName,
            fontSize = 20.sp,
            fontWeight = FontWeight.Bold,
            color = TextPrimary
        )

        Spacer(Modifier.height(4.dp))

        Text(
            "${stringResource(state.titleRes)} · ${stringResource(Res.string.profile_id_format, state.employeeId)}",
            fontSize = 14.sp,
            color = TextSecondary
        )

        Spacer(Modifier.height(10.dp))

        Row(
            modifier = Modifier
                .clip(RoundedCornerShape(100.dp))
                .background(VerifiedBg)
                .padding(horizontal = 12.dp, vertical = 4.dp),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.spacedBy(4.dp)
        ) {
            Text("🛡", fontSize = 10.sp)
            Text(
                stringResource(Res.string.profile_verified),
                fontSize = 12.sp,
                fontWeight = FontWeight.Medium,
                color = VerifiedText
            )
        }
    }
}

@Composable
private fun MenuSection(
    title: String,
    items: List<ProfileMenuItem>,
    onItemClick: (ProfileMenuItem) -> Unit = {}
) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(24.dp))
            .background(CardWhite)
            .padding(horizontal = 8.dp, vertical = 8.dp)
    ) {
        Text(
            title,
            fontSize = 16.sp,
            fontWeight = FontWeight.Bold,
            color = TextPrimary,
            modifier = Modifier.padding(horizontal = 8.dp, vertical = 6.dp)
        )

        items.forEachIndexed { index, item ->
            MenuItemRow(item = item, onClick = { onItemClick(item) })
            if (index < items.lastIndex) {
                HorizontalDivider(
                    modifier = Modifier.padding(horizontal = 16.dp),
                    thickness = 0.5.dp,
                    color = Background
                )
            }
        }
    }
}

@Composable
private fun MenuItemRow(item: ProfileMenuItem, onClick: () -> Unit) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .clickable(onClick = onClick)
            .padding(horizontal = 8.dp, vertical = 4.dp)
            .clip(RoundedCornerShape(12.dp))
            .padding(horizontal = 4.dp, vertical = 8.dp),
        verticalAlignment = Alignment.CenterVertically
    ) {
        Box(
            modifier = Modifier
                .size(40.dp)
                .clip(RoundedCornerShape(12.dp))
                .background(Color(item.bgColor)),
            contentAlignment = Alignment.Center
        ) {
            Text(item.icon, fontSize = 16.sp)
        }

        Spacer(Modifier.width(12.dp))

        Column(modifier = Modifier.weight(1f)) {
            Text(
                stringResource(item.titleRes),
                fontSize = 15.sp,
                fontWeight = FontWeight.Medium,
                color = TextPrimary
            )
            Text(
                if (item.subtitleArg != null) stringResource(item.subtitleRes, item.subtitleArg)
                else stringResource(item.subtitleRes),
                fontSize = 13.sp,
                color = TextSecondary
            )
        }

        Text("›", fontSize = 18.sp, color = ChevronGray)
    }
}

@Composable
private fun LogoutButton(enabled: Boolean, onClick: () -> Unit) {
    Box(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(16.dp))
            .background(CardWhite)
            .clickable(enabled = enabled, onClick = onClick)
            .padding(vertical = 16.dp),
        contentAlignment = Alignment.Center
    ) {
        Text(
            stringResource(Res.string.profile_logout),
            fontSize = 16.sp,
            fontWeight = FontWeight.Medium,
            color = AppColors.PaletteFFEF4444
        )
    }
}
