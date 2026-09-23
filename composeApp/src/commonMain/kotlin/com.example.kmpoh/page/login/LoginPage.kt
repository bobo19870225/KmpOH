package com.example.kmpoh.page.login

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.BoxWithConstraints
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.heightIn
import androidx.compose.foundation.layout.offset
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.safeDrawing
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.graphics.graphicsLayer
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.text.input.VisualTransformation
import androidx.compose.ui.unit.Density
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.kmpoh.data.repository.createLoginRepository
import com.example.kmpoh.ui.components.LoadingView
import com.example.kmpoh.ui.components.PrimaryButton
import com.example.kmpoh.ui.components.PrimaryInput
import com.example.kmpoh.ui.theme.AppColors
import com.example.kmpoh.utils.UiState
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.ic_login_arrow_forward
import kmpoh.composeapp.generated.resources.ic_login_checkmark
import kmpoh.composeapp.generated.resources.ic_login_iphone
import kmpoh.composeapp.generated.resources.ic_login_lock
import kmpoh.composeapp.generated.resources.ic_login_shield
import kmpoh.composeapp.generated.resources.ic_login_sparkle
import kmpoh.composeapp.generated.resources.ic_login_visibility
import kmpoh.composeapp.generated.resources.ic_login_visibility_off
import kmpoh.composeapp.generated.resources.str_login_eyebrow
import kmpoh.composeapp.generated.resources.str_login_security_note
import kmpoh.composeapp.generated.resources.str_login_service_eyebrow
import kmpoh.composeapp.generated.resources.str_login_service_title
import kmpoh.composeapp.generated.resources.str_login_slogan
import kmpoh.composeapp.generated.resources.str_login_slogan_desc
import kmpoh.composeapp.generated.resources.str_login_start_service
import kmpoh.composeapp.generated.resources.str_login_subtitle
import kmpoh.composeapp.generated.resources.str_login_title
import kmpoh.composeapp.generated.resources.str_password_hide
import kmpoh.composeapp.generated.resources.str_password_hint
import kmpoh.composeapp.generated.resources.str_password_login_hint
import kmpoh.composeapp.generated.resources.str_password_show
import kmpoh.composeapp.generated.resources.str_phone_label
import kmpoh.composeapp.generated.resources.str_phone_login_hint
import org.jetbrains.compose.resources.DrawableResource
import org.jetbrains.compose.resources.StringResource
import org.jetbrains.compose.resources.painterResource
import org.jetbrains.compose.resources.stringResource

private val LoginBackground = Color(0xFFF8F8F2)
private val LoginInk = Color(0xFF0B3D4B)
private val LoginMuted = Color(0xFF7A8584)
private val LoginInputBackground = Color(0xFFF6F8F7)
private val LoginInputBorder = Color(0xFFE7ECEA)
private val LoginButtonDisabled = Color(0xFFC9D4D8)
private val LoginOrange = Color(0xFFFFBC61)

// 登录页内容自然高度估算 = 固定部分 + sp 部分（后者随系统字体缩放线性增长），
// 由 LoginContent / LoginHero / LoginServiceBanner / 登录卡片里的固定尺寸求和得出。
// 注意：无 lineHeight 的文本按 CJK 行高 ≈ 字号×1.45em 折算，系数取的是偏保守上界
// （宁可轻微缩小也不溢出）。若调整布局尺寸或字号，请同步更新这两个系数。
private const val LoginDesignHeightDp = 400f
private const val LoginDesignHeightSp = 300f

@Composable
fun LoginPage(
    onLoginSuccess: () -> Unit,
    onToastMessage: (String) -> Unit
) {
    val scope = rememberCoroutineScope()
    // 自写容器由页面持有，作用域跟随组合（见 LoginViewModel 的类注释）
    val viewModel = remember { LoginViewModel(createLoginRepository(), scope) }

    val uiState by viewModel.uiState.collectAsState()
    val phone by viewModel.phone.collectAsState()
    val password by viewModel.password.collectAsState()
    val loginEnabled by viewModel.loginEnabled.collectAsState()
    val toastMessage by viewModel.toastMessage.collectAsState()

    LaunchedEffect(toastMessage) {
        toastMessage?.let {
            onToastMessage(it)
            viewModel.onToastShown()
        }
    }
    LaunchedEffect(uiState) {
        if (uiState is UiState.Success) onLoginSuccess()
    }

    LoginContent(
        phone = phone,
        password = password,
        onPhoneChanged = viewModel::onPhoneChanged,
        onPasswordChanged = viewModel::onPasswordChanged,
        onLoginClick = viewModel::onLoginClick,
        isLoading = uiState is UiState.Loading,
        loginEnabled = loginEnabled
    )
}

@Composable
private fun LoginContent(
    phone: String,
    password: String,
    onPhoneChanged: (String) -> Unit,
    onPasswordChanged: (String) -> Unit,
    onLoginClick: () -> Unit,
    isLoading: Boolean,
    loginEnabled: Boolean
) {
    var passwordVisible by remember { mutableStateOf(false) }

    Box(Modifier.fillMaxSize().background(LoginBackground)) {
        val density = LocalDensity.current
        // 原安卓工程由宿主 MainActivity 的 Surface.statusBarsPadding() 统一避让状态栏。
        // 本页自带全屏背景色，若把避让放在宿主会在状态栏区域留出一条异色边——
        // 故改由页面自身避让安全区，背景保持满屏。safeDrawing 同时覆盖
        // Android 状态栏/导航栏、iOS 刘海与鸿蒙安全区。避让量必须留在缩放层之外，
        // 按真实像素计算，不随整页缩放变化。
        BoxWithConstraints(
            Modifier
                .fillMaxSize()
                .windowInsetsPadding(WindowInsets.safeDrawing)
        ) {
            // 一屏自适应：常规屏幕 scale=1 原样排版；视口放不下时整页等比缩小，
            // 保证登录页不出现滚动、内容完整显示在一屏内。
            val designHeight = with(density) {
                LoginDesignHeightDp.dp + LoginDesignHeightSp.sp.toDp()
            }
            val scale =
                if (maxHeight <= 0.dp || designHeight <= 0.dp) 1f
                else minOf(1f, maxHeight.value / designHeight.value)
            CompositionLocalProvider(
                // 只放大 density、不动 fontScale：dp 与 sp 的渲染同比例缩放（sp→px = sp×fontScale×density）
                LocalDensity provides Density(density.density * scale, density.fontScale)
            ) {
                Column(
                    Modifier
                        .fillMaxSize()
                        .padding(horizontal = 24.dp)
                        .padding(top = 14.dp, bottom = 12.dp)
                ) {
                    LoginHero()
                    // 弹性间距：富余高度在此吸收；紧张时收到 0，仍放不下由上方 scale 缩放兜底
                    Spacer(Modifier.weight(1f))
                    Card(
                        Modifier
                            .fillMaxWidth()
                            .shadow(12.dp, RoundedCornerShape(26.dp), clip = false),
                        RoundedCornerShape(26.dp),
                        colors = CardDefaults.cardColors(containerColor = AppColors.PaletteWhite)
                    ) {
                        Column(Modifier.padding(horizontal = 22.dp, vertical = 14.dp)) {
                            Text(
                                stringResource(Res.string.str_login_title),
                                color = LoginInk,
                                fontSize = 21.sp,
                                fontWeight = FontWeight.Bold
                            )
                            Spacer(Modifier.height(4.dp))
                            Text(
                                stringResource(Res.string.str_login_subtitle),
                                color = LoginMuted,
                                fontSize = 13.sp
                            )
                            Spacer(Modifier.height(10.dp))

                            LoginFieldLabel(Res.string.str_phone_label)
                            Spacer(Modifier.height(5.dp))
                            PrimaryInput(
                                value = phone,
                                onValueChange = onPhoneChanged,
                                placeholder = stringResource(Res.string.str_phone_login_hint),
                                leadingIcon = { LoginResourceIcon(Res.drawable.ic_login_iphone) },
                                enabled = !isLoading,
                                keyboardOptions = KeyboardOptions(
                                    keyboardType = KeyboardType.Text,
                                    imeAction = ImeAction.Next
                                ),
                                height = 44.dp,
                                fontSize = 15.sp,
                                focusedBorderColor = LoginInk,
                                unfocusedBorderColor = LoginInputBorder,
                                containerColor = LoginInputBackground
                            )
                            Spacer(Modifier.height(10.dp))

                            LoginFieldLabel(Res.string.str_password_hint)
                            Spacer(Modifier.height(5.dp))
                            PrimaryInput(
                                value = password,
                                onValueChange = onPasswordChanged,
                                placeholder = stringResource(Res.string.str_password_login_hint),
                                leadingIcon = { LoginResourceIcon(Res.drawable.ic_login_lock) },
                                trailingIcon = {
                                    IconButton(onClick = { passwordVisible = !passwordVisible }) {
                                        Icon(
                                            painter = painterResource(
                                                if (passwordVisible) Res.drawable.ic_login_visibility_off
                                                else Res.drawable.ic_login_visibility
                                            ),
                                            contentDescription = stringResource(
                                                if (passwordVisible) Res.string.str_password_hide
                                                else Res.string.str_password_show
                                            ),
                                            tint = LoginMuted,
                                            modifier = Modifier.size(21.dp)
                                        )
                                    }
                                },
                                enabled = !isLoading,
                                keyboardOptions = KeyboardOptions(
                                    keyboardType = KeyboardType.Password,
                                    imeAction = ImeAction.Done
                                ),
                                visualTransformation = if (passwordVisible) VisualTransformation.None
                                else PasswordVisualTransformation(),
                                height = 44.dp,
                                fontSize = 15.sp,
                                focusedBorderColor = LoginInk,
                                unfocusedBorderColor = LoginInputBorder,
                                containerColor = LoginInputBackground
                            )
                            Spacer(Modifier.height(12.dp))

                            PrimaryButton(
                                text = stringResource(Res.string.str_login_start_service),
                                onClick = onLoginClick,
                                enabled = loginEnabled,
                                isLoading = isLoading,
                                height = 44.dp,
                                containerColor = LoginInk,
                                disabledContainerColor = LoginButtonDisabled,
                                trailingIcon = {
                                    Icon(
                                        painter = painterResource(Res.drawable.ic_login_arrow_forward),
                                        contentDescription = null,
                                        modifier = Modifier.size(21.dp)
                                    )
                                }
                            )
                        }
                    }
                    Spacer(Modifier.weight(1f))
                    Row(
                        Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.Center,
                        verticalAlignment = Alignment.CenterVertically
                    ) {
                        LoginResourceIcon(Res.drawable.ic_login_shield, size = 16.dp)
                        Spacer(Modifier.width(8.dp))
                        Text(
                            stringResource(Res.string.str_login_security_note),
                            color = LoginMuted,
                            fontSize = 13.sp,
                            fontWeight = FontWeight.Medium
                        )
                    }
                }
            }
        }

        if (isLoading) {
            Box(
                modifier = Modifier.fillMaxSize().background(Color.Black.copy(alpha = 0.16f)),
                contentAlignment = Alignment.Center
            ) {
                LoadingView()
            }
        }
    }
}

@Composable
private fun LoginHero() {
    Column {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Box(Modifier.size(width = 28.dp, height = 5.dp).clip(CircleShape).background(LoginOrange))
            Spacer(Modifier.width(10.dp))
            Text(
                stringResource(Res.string.str_login_eyebrow),
                color = LoginMuted,
                fontSize = 10.sp,
                fontWeight = FontWeight.Bold,
                letterSpacing = 3.sp
            )
        }
        Spacer(Modifier.height(5.dp))
        Text(
            stringResource(Res.string.str_login_slogan),
            color = LoginInk,
            fontSize = 28.sp,
            lineHeight = 34.sp,
            fontWeight = FontWeight.Bold
        )
        Spacer(Modifier.height(5.dp))
        Text(
            stringResource(Res.string.str_login_slogan_desc),
            color = LoginMuted,
            fontSize = 14.sp
        )
        Spacer(Modifier.height(10.dp))
        LoginServiceBanner()
    }
}

@Composable
private fun LoginServiceBanner() {
    Box(
        Modifier
            .fillMaxWidth()
            // 高度自适应：文案列高度随系统字体缩放增长，固定高度会在大字体下
            // 从底部裁掉「SERVICE WITH CARE」（鸿蒙实机踩过）。min 保住设计感。
            .heightIn(min = 116.dp)
            .clip(RoundedCornerShape(24.dp))
            .background(Color(0xFFE3F0ED))
            .padding(14.dp)
    ) {
        Canvas(Modifier.matchParentSize()) {
            val circleCenter = Offset(size.width * .82f, size.height * .5f)
            drawCircle(
                Color(0xFFBFDAD5).copy(alpha = .42f),
                size.height * .88f,
                circleCenter,
                style = Stroke(1.dp.toPx())
            )
            drawCircle(
                Color(0xFFBFDAD5).copy(alpha = .24f),
                size.height * .58f,
                circleCenter,
                style = Stroke(1.dp.toPx())
            )
        }
        Column(Modifier.align(Alignment.CenterStart)) {
            LoginResourceIcon(Res.drawable.ic_login_sparkle, tint = LoginInk, size = 16.dp)
            Spacer(Modifier.height(5.dp))
            Text(
                stringResource(Res.string.str_login_service_title),
                color = LoginInk,
                fontSize = 17.sp,
                lineHeight = 22.sp,
                fontWeight = FontWeight.Bold
            )
            Spacer(Modifier.height(5.dp))
            Text(
                stringResource(Res.string.str_login_service_eyebrow),
                color = LoginInk,
                fontSize = 8.sp,
                letterSpacing = 1.5.sp
            )
        }
        Box(
            Modifier
                .align(Alignment.CenterEnd)
                .offset(x = (-4).dp)
                .size(76.dp)
                .graphicsLayer { rotationZ = 8f }
                .shadow(8.dp, RoundedCornerShape(24.dp), clip = false)
                .clip(RoundedCornerShape(24.dp))
                .background(LoginInk),
            contentAlignment = Alignment.Center
        ) {
            LoginResourceIcon(Res.drawable.ic_login_shield, tint = AppColors.PaletteWhite, size = 34.dp)
        }
        Box(
            Modifier
                .align(Alignment.BottomEnd)
                .offset(x = 1.dp, y = 1.dp)
                .size(38.dp)
                .shadow(4.dp, CircleShape, clip = false)
                .clip(CircleShape)
                .background(AppColors.PaletteWhite),
            contentAlignment = Alignment.Center
        ) {
            Box(
                Modifier
                    .size(32.dp)
                    .clip(CircleShape)
                    .background(LoginOrange),
                contentAlignment = Alignment.Center
            ) {
                LoginResourceIcon(Res.drawable.ic_login_checkmark, tint = LoginInk, size = 16.dp)
            }
        }
    }
}

@Composable
private fun LoginFieldLabel(textRes: StringResource) = Text(
    stringResource(textRes),
    color = LoginInk,
    fontSize = 14.sp,
    fontWeight = FontWeight.SemiBold
)

@Composable
private fun LoginResourceIcon(
    resource: DrawableResource,
    tint: Color = LoginMuted,
    size: Dp = 19.dp
) = Icon(
    painter = painterResource(resource),
    contentDescription = null,
    tint = tint,
    modifier = Modifier.size(size)
)
