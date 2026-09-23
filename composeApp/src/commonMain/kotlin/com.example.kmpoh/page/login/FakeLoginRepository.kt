package com.example.kmpoh.page.login

import kotlinx.coroutines.delay

/**
 * 【临时脚手架 —— 下一步接入网络层时整体删除本文件】
 *
 * 登录数据源的本地假实现。不发起任何网络请求，不读写任何存储，
 * 仅按固定规则返回成功或失败，用于本次「只做 UI」阶段驱动页面状态。
 *
 * 失败规则（便于在真机上手动验证失败分支）：
 *  - 密码等于 [FAIL_PASSWORD] 时返回失败，用于触发错误提示；
 *  - 其余情况返回成功。
 *
 * 待办（下一变更）：替换为基于 Ktor 的真实实现。
 */
class FakeLoginRepository {

    suspend fun login(staffCode: String, password: String): Result<Unit> {
        // 模拟一次网络往返，使加载态在真机上肉眼可见
        delay(NETWORK_LATENCY_MS)

        return when {
            staffCode.isBlank() || password.isBlank() ->
                Result.failure(IllegalArgumentException("账号或密码不能为空"))

            password == FAIL_PASSWORD ->
                Result.failure(RuntimeException("账号或密码不正确"))

            else -> Result.success(Unit)
        }
    }

    private companion object {
        const val NETWORK_LATENCY_MS = 1500L

        /** 输入该密码即可在真机上复现失败提示。 */
        const val FAIL_PASSWORD = "error"
    }
}
