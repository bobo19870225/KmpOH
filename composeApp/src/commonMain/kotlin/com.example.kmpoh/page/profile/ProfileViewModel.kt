package com.example.kmpoh.page.profile

import com.example.kmpoh.data.repository.ProfileRepository
import com.example.kmpoh.network.AuthSessionManager
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharedFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asSharedFlow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.profile_about
import kmpoh.composeapp.generated.resources.profile_about_desc
import kmpoh.composeapp.generated.resources.profile_help
import kmpoh.composeapp.generated.resources.profile_help_desc
import kmpoh.composeapp.generated.resources.profile_preferences
import kmpoh.composeapp.generated.resources.profile_preferences_desc
import kmpoh.composeapp.generated.resources.profile_title_engineer
import org.jetbrains.compose.resources.StringResource

/**
 * 「我的」页菜单项（原样迁原工程 ProfileMenuItem；文案以资源入参由 Page 映射，保证多语言——
 * 原工程在 VM 内硬编码中文，属迁移时的刻意修正）。
 */
data class ProfileMenuItem(
    val id: String,
    val titleRes: StringResource,
    val subtitleRes: StringResource,
    val bgColor: Long,
    val iconTint: Long,
    val icon: String,
    val showBadge: Boolean = false,
    val subtitleArg: String? = null
)

data class ProfileUiState(
    val isLoggingOut: Boolean = false,
    val avatarName: String = "",
    val displayName: String = "",
    val titleRes: StringResource = Res.string.profile_title_engineer,
    val employeeId: String = "T-20086",
    val isVerified: Boolean = true,
    val systemSettings: List<ProfileMenuItem> = emptyList()
)

/** 页面一次性事件：导航类动作不落 UI 状态（对齐原工程 ProfileEffect）。 */
sealed interface ProfileEffect {
    /** 登出流程完成，页面收到后交由导航层清栈回登录页。 */
    data object LoggedOut : ProfileEffect
}

/**
 * 「我的」页 ViewModel（原样迁原工程状态结构与登出语义；自写纯 Kotlin 状态容器，
 * 对齐 LoginViewModel 样板）。displayName 以登录持久化的用户姓名为单一数据来源
 * （data/profile「用户展示名数据源」）；职称/工号/已认证为展示默认值（对齐原工程，决策 3）。
 */
class ProfileViewModel(
    private val profileRepository: ProfileRepository,
    private val session: AuthSessionManager,
    private val scope: CoroutineScope
) {
    /** 登出中间态独立保存，再与资料状态合并为统一页面状态（对齐原工程）。 */
    private val loggingOutState = MutableStateFlow(false)

    private val _effect = MutableSharedFlow<ProfileEffect>(extraBufferCapacity = 1)
    val effect: SharedFlow<ProfileEffect> = _effect.asSharedFlow()

    private val baseState: ProfileUiState = run {
        val name = session.userName().orEmpty()
        ProfileUiState(
            avatarName = name.take(1),
            displayName = name,
            systemSettings = listOf(
                ProfileMenuItem(
                    id = "preferences",
                    titleRes = Res.string.profile_preferences,
                    subtitleRes = Res.string.profile_preferences_desc,
                    bgColor = 0xFFF3F4F6,
                    iconTint = 0xFF6B7280,
                    icon = "⚙️"
                ),
                ProfileMenuItem(
                    id = "help",
                    titleRes = Res.string.profile_help,
                    subtitleRes = Res.string.profile_help_desc,
                    bgColor = 0xFFF0F9FF,
                    iconTint = 0xFF3B82F6,
                    icon = "❓"
                ),
                ProfileMenuItem(
                    id = "about",
                    titleRes = Res.string.profile_about,
                    subtitleRes = Res.string.profile_about_desc,
                    bgColor = 0xFFF3F4F6,
                    iconTint = 0xFF9CA3AF,
                    icon = "ℹ️",
                    subtitleArg = "1.0.0"
                )
            )
        )
    }

    val state: StateFlow<ProfileUiState> = loggingOutState
        .map { isLoggingOut -> baseState.copy(isLoggingOut = isLoggingOut) }
        .stateIn(scope, SharingStarted.Eagerly, baseState)

    /** 统一登出入口：防重复触发；服务端登出与本地清理由 Repository 处理（spec ui/profile）。 */
    fun onLogoutClick() {
        if (loggingOutState.value) return
        scope.launch {
            loggingOutState.value = true
            profileRepository.logout()
            loggingOutState.value = false
            _effect.emit(ProfileEffect.LoggedOut)
        }
    }
}
