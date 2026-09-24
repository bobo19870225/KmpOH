package com.example.kmpoh.ui.components

import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.heightIn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.input.VisualTransformation
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.TextUnit
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

/** 登录等主输入框，保留既有尺寸、颜色和交互参数。 */
@Composable
fun PrimaryInput(
    value: String,
    onValueChange: (String) -> Unit,
    placeholder: String,
    fontSize: TextUnit = 14.sp,
    modifier: Modifier = Modifier,
    enabled: Boolean = true,
    singleLine: Boolean = true,
    height: Dp = 56.dp,
    leadingIcon: @Composable (() -> Unit)? = null,
    trailingIcon: @Composable (() -> Unit)? = null,
    visualTransformation: VisualTransformation = VisualTransformation.None,
    keyboardOptions: KeyboardOptions = KeyboardOptions.Default,
    focusedBorderColor: Color = Color(0xFF2B7890),
    unfocusedBorderColor: Color = Color(0xFFE6EAF0),
    containerColor: Color = Color(0xFFF8FAFD),
    keyboardActions: KeyboardActions = KeyboardActions.Default
) {
    OutlinedTextField(
        value = value,
        onValueChange = onValueChange,
        modifier = modifier.fillMaxWidth().height(height).heightIn(height),
        enabled = enabled,
        singleLine = singleLine,
        shape = RoundedCornerShape(12.dp),
        // 不设 lineHeight：lineHeight = fontSize（1em）的行框小于 CJK 字形自然行高（≈1.2em），
        // 溢出部分在鸿蒙 CMP 文本栈会被裁掉字形底部（Android fontPadding 容忍，原工程未暴露）。
        textStyle = TextStyle(
            color = if (enabled) Color.Black else Color(0xFF9EA7B3),
            fontSize = fontSize
        ),
        placeholder = { Text(placeholder, color = Color(0xFFC1C6CE), fontSize = fontSize) },
        leadingIcon = leadingIcon,
        trailingIcon = trailingIcon,
        visualTransformation = visualTransformation,
        keyboardOptions = keyboardOptions,
        keyboardActions = keyboardActions,
        colors = OutlinedTextFieldDefaults.colors(
            focusedBorderColor = focusedBorderColor,
            unfocusedBorderColor = unfocusedBorderColor,
            disabledBorderColor = unfocusedBorderColor,
            focusedContainerColor = containerColor,
            unfocusedContainerColor = containerColor,
            disabledContainerColor = containerColor,
            cursorColor = Color(0xFF137FF5),
            focusedTextColor = Color.Black,
            unfocusedTextColor = Color.Black,
            disabledTextColor = Color(0xFF9EA7B3),
            focusedLeadingIconColor = Color(0xFF137FF5),
            unfocusedLeadingIconColor = Color(0xFF9EA7B3),
            disabledLeadingIconColor = Color(0xFFC1C6CE)
        )
    )
}
