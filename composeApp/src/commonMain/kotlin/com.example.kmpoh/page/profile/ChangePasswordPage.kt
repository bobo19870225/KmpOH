package com.example.kmpoh.page.profile

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.text.input.VisualTransformation
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.kmpoh.data.repository.createProfileRepository
import com.example.kmpoh.ui.theme.AppColors
import kmpoh.composeapp.generated.resources.Res
import kmpoh.composeapp.generated.resources.change_password_back_desc
import kmpoh.composeapp.generated.resources.change_password_confirm_mismatch
import kmpoh.composeapp.generated.resources.change_password_confirm_password
import kmpoh.composeapp.generated.resources.change_password_failed
import kmpoh.composeapp.generated.resources.change_password_form_desc
import kmpoh.composeapp.generated.resources.change_password_form_title
import kmpoh.composeapp.generated.resources.change_password_hide_password
import kmpoh.composeapp.generated.resources.change_password_max_length
import kmpoh.composeapp.generated.resources.change_password_min_length
import kmpoh.composeapp.generated.resources.change_password_new_password
import kmpoh.composeapp.generated.resources.change_password_required
import kmpoh.composeapp.generated.resources.change_password_rule_length_format
import kmpoh.composeapp.generated.resources.change_password_rules_load_failed
import kmpoh.composeapp.generated.resources.change_password_show_password
import kmpoh.composeapp.generated.resources.change_password_submit
import kmpoh.composeapp.generated.resources.change_password_success
import kmpoh.composeapp.generated.resources.change_password_title
import kmpoh.composeapp.generated.resources.ic_back_arrow
import kmpoh.composeapp.generated.resources.ic_login_visibility
import kmpoh.composeapp.generated.resources.ic_login_visibility_off
import kmpoh.composeapp.generated.resources.ic_password_lock
import org.jetbrains.compose.resources.painterResource
import org.jetbrains.compose.resources.stringResource

private val ChangePasswordBackground = AppColors.PaletteFFF3F4F6
private val ChangePasswordCard = AppColors.PaletteWhite
private val ChangePasswordPrimary = AppColors.PaletteFF1D6F86
private val ChangePasswordText = AppColors.PaletteFF111827
private val ChangePasswordSubText = AppColors.PaletteFF6B7280
private val ChangePasswordInputBorder = Color(0xFFE7ECEA)

/**
 * 修改密码页（spec ui/profile「修改密码表单与校验」）：双密码框 + 服务端规则校验 + 提交。
 * 成功经 [onPasswordChangedSuccess] 由导航层清栈回登录页（决策 5）；toast 文案由
 * [ChangePasswordToast] 映射多语言后交 [onToastMessage]（宿主无 Toast 基建时落日志，对齐登录页接缝）。
 */
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ChangePasswordPage(
    onBack: () -> Unit,
    onToastMessage: (String) -> Unit,
    onPasswordChangedSuccess: () -> Unit
) {
    val scope = rememberCoroutineScope()
    val viewModel = remember { ChangePasswordViewModel(createProfileRepository(), scope) }
    val state by viewModel.state.collectAsState()
    var newPasswordVisible by remember { mutableStateOf(false) }
    var confirmPasswordVisible by remember { mutableStateOf(false) }

    // 文案映射须在组合期完成（toDisplayString 是 @Composable），effect 内只做转发
    val toastText = state.toast?.toDisplayString()
    LaunchedEffect(state.toast) {
        toastText?.let { text ->
            onToastMessage(text)
            viewModel.onToastShown()
        }
    }

    LaunchedEffect(state.passwordChanged) {
        if (state.passwordChanged) {
            viewModel.onPasswordChangedHandled()
            onPasswordChangedSuccess()
        }
    }

    Scaffold(
        containerColor = ChangePasswordBackground,
        topBar = {
            CenterAlignedTopAppBar(
                title = {
                    Text(
                        text = stringResource(Res.string.change_password_title),
                        fontSize = 16.sp,
                        fontWeight = FontWeight.Bold,
                        color = ChangePasswordText
                    )
                },
                navigationIcon = {
                    IconButton(onClick = onBack) {
                        Icon(
                            painter = painterResource(Res.drawable.ic_back_arrow),
                            contentDescription = stringResource(Res.string.change_password_back_desc),
                            tint = ChangePasswordText
                        )
                    }
                },
                colors = TopAppBarDefaults.centerAlignedTopAppBarColors(
                    containerColor = ChangePasswordCard
                )
            )
        }
    ) { padding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .background(ChangePasswordBackground)
                .padding(padding)
                .padding(16.dp),
            verticalArrangement = Arrangement.spacedBy(12.dp)
        ) {
            Column(
                modifier = Modifier
                    .fillMaxWidth()
                    .clip(RoundedCornerShape(16.dp))
                    .background(ChangePasswordCard)
                    .padding(16.dp),
                verticalArrangement = Arrangement.spacedBy(12.dp)
            ) {
                Text(
                    text = stringResource(Res.string.change_password_form_title),
                    fontSize = 14.sp,
                    fontWeight = FontWeight.Bold,
                    color = ChangePasswordText
                )
                Text(
                    text = stringResource(Res.string.change_password_form_desc),
                    fontSize = 12.sp,
                    color = ChangePasswordSubText
                )
                PasswordInput(
                    value = state.newPassword,
                    onValueChange = viewModel::onNewPasswordChange,
                    label = stringResource(Res.string.change_password_new_password),
                    imeAction = ImeAction.Next,
                    isError = state.passwordRuleError != null,
                    errorMessage = state.passwordRuleError,
                    passwordVisible = newPasswordVisible,
                    onPasswordVisibleChange = { newPasswordVisible = !newPasswordVisible }
                )
                Text(
                    text = state.passwordRuleDescription.ifBlank {
                        stringResource(
                            Res.string.change_password_rule_length_format,
                            state.passwordRules.minLength,
                            state.passwordRules.maxLength
                        )
                    },
                    fontSize = 12.sp,
                    color = ChangePasswordSubText
                )
                PasswordInput(
                    value = state.confirmPassword,
                    onValueChange = viewModel::onConfirmPasswordChange,
                    label = stringResource(Res.string.change_password_confirm_password),
                    imeAction = ImeAction.Done,
                    isError = state.shouldShowConfirmMismatch,
                    errorMessage = if (state.shouldShowConfirmMismatch) {
                        stringResource(Res.string.change_password_confirm_mismatch)
                    } else {
                        null
                    },
                    passwordVisible = confirmPasswordVisible,
                    onPasswordVisibleChange = { confirmPasswordVisible = !confirmPasswordVisible }
                )
            }

            Spacer(Modifier.height(4.dp))

            state.requestErrorMessage?.takeIf { it.isNotBlank() }?.let { message ->
                Text(
                    text = message,
                    modifier = Modifier.fillMaxWidth(),
                    color = AppColors.PaletteFFEF4444,
                    fontSize = 12.sp
                )
            }

            Button(
                onClick = viewModel::submit,
                enabled = state.canSubmit,
                modifier = Modifier
                    .fillMaxWidth()
                    .height(50.dp),
                shape = RoundedCornerShape(12.dp),
                colors = ButtonDefaults.buttonColors(
                    containerColor = ChangePasswordPrimary,
                    disabledContainerColor = AppColors.PaletteFFC9D3DF,
                    contentColor = Color.White,
                    disabledContentColor = Color.White
                )
            ) {
                if (state.isSubmitting) {
                    CircularProgressIndicator(
                        color = Color.White,
                        strokeWidth = 2.dp,
                        modifier = Modifier.size(18.dp)
                    )
                } else {
                    Text(
                        text = stringResource(Res.string.change_password_submit),
                        fontSize = 14.sp,
                        fontWeight = FontWeight.Bold
                    )
                }
            }
        }
    }
}

/** 类型化 toast 文案 → 多语言（决策 2）。 */
@Composable
private fun ChangePasswordToast.toDisplayString(): String = when (this) {
    ChangePasswordToast.Required -> stringResource(Res.string.change_password_required)
    ChangePasswordToast.ConfirmMismatch -> stringResource(Res.string.change_password_confirm_mismatch)
    is ChangePasswordToast.MinLength -> stringResource(Res.string.change_password_min_length, min)
    is ChangePasswordToast.MaxLength -> stringResource(Res.string.change_password_max_length, max)
    ChangePasswordToast.RulesLoadFailed -> stringResource(Res.string.change_password_rules_load_failed)
    ChangePasswordToast.Failed -> stringResource(Res.string.change_password_failed)
    is ChangePasswordToast.Success ->
        message?.takeIf { it.isNotBlank() } ?: stringResource(Res.string.change_password_success)

    is ChangePasswordToast.Error -> message
}

@Composable
private fun PasswordInput(
    value: String,
    onValueChange: (String) -> Unit,
    label: String,
    imeAction: ImeAction,
    isError: Boolean,
    errorMessage: String?,
    passwordVisible: Boolean,
    onPasswordVisibleChange: () -> Unit
) {
    Column(verticalArrangement = Arrangement.spacedBy(4.dp)) {
        Text(label, fontSize = 14.sp, fontWeight = FontWeight.Medium, color = ChangePasswordText)
        OutlinedTextField(
            value = value,
            onValueChange = onValueChange,
            modifier = Modifier.fillMaxWidth(),
            singleLine = true,
            isError = isError,
            visualTransformation = if (passwordVisible) VisualTransformation.None else PasswordVisualTransformation(),
            keyboardOptions = KeyboardOptions(
                keyboardType = KeyboardType.Password,
                imeAction = imeAction
            ),
            leadingIcon = {
                Icon(
                    painter = painterResource(Res.drawable.ic_password_lock),
                    contentDescription = null,
                    tint = ChangePasswordSubText
                )
            },
            trailingIcon = {
                IconButton(onClick = onPasswordVisibleChange) {
                    Icon(
                        painter = painterResource(
                            if (passwordVisible) Res.drawable.ic_login_visibility_off
                            else Res.drawable.ic_login_visibility
                        ),
                        contentDescription = stringResource(
                            if (passwordVisible) Res.string.change_password_hide_password
                            else Res.string.change_password_show_password
                        ),
                        tint = ChangePasswordSubText
                    )
                }
            },
            shape = RoundedCornerShape(12.dp),
            colors = OutlinedTextFieldDefaults.colors(
                focusedBorderColor = ChangePasswordPrimary,
                unfocusedBorderColor = ChangePasswordInputBorder,
                errorBorderColor = AppColors.PaletteFFEF4444,
                focusedContainerColor = ChangePasswordCard,
                unfocusedContainerColor = ChangePasswordCard,
                cursorColor = ChangePasswordPrimary
            )
        )
        errorMessage?.let {
            Text(it, color = AppColors.PaletteFFEF4444, fontSize = 12.sp)
        }
    }
}
