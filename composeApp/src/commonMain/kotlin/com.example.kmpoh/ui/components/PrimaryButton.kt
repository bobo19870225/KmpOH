package com.example.kmpoh.ui.components

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.Dp
import com.example.kmpoh.ui.theme.AppDimens
import com.example.kmpoh.ui.theme.AppFontSize

/** 登录等主操作按钮，参数与历史 widget API 保持一致。 */
@Composable
fun PrimaryButton(
    text: String,
    onClick: () -> Unit,
    modifier: Modifier = Modifier,
    enabled: Boolean = true,
    isLoading: Boolean = false,
    height: Dp = AppDimens.ButtonHeight,
    containerColor: Color = Color(0xFF0D536A),
    disabledContainerColor: Color = Color(0xFFC6D0D8),
    contentColor: Color = Color.White,
    trailingIcon: @Composable (() -> Unit)? = null
) {
    Button(
        onClick = onClick,
        modifier = modifier.fillMaxWidth().height(height),
        enabled = enabled && !isLoading,
        shape = RoundedCornerShape(height / 2),
        contentPadding = PaddingValues(horizontal = AppDimens.Dp20),
        colors = ButtonDefaults.buttonColors(
            containerColor = containerColor,
            disabledContainerColor = disabledContainerColor,
            contentColor = contentColor,
            disabledContentColor = contentColor
        )
    ) {
        if (isLoading) {
            CircularProgressIndicator(Modifier.size(AppDimens.Dp22), strokeWidth = AppDimens.Dp2, color = contentColor)
        } else {
            Box(Modifier.fillMaxWidth(), contentAlignment = Alignment.Center) {
                Text(text, fontSize = AppFontSize.Sp18, fontWeight = FontWeight.Bold)
                trailingIcon?.let { icon ->
                    Box(Modifier.fillMaxSize(), contentAlignment = Alignment.CenterEnd) { icon() }
                }
            }
        }
    }
}
