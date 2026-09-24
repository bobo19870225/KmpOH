package com.example.kmpoh.data.repository

import com.example.kmpoh.data.model.dto.InitInfoDto
import com.example.kmpoh.data.model.dto.PasswordRulesDto
import com.example.kmpoh.data.model.entity.PasswordRulesEntity
import com.example.kmpoh.data.model.mapper.toEntity
import com.example.kmpoh.network.ApiGateway
import com.example.kmpoh.network.AuthSessionManager
import com.example.kmpoh.network.postJson
import com.example.kmpoh.storage.KeyValueStore

private const val PATH_LOGOUT = "mobile/Staff.Login/logout"
private const val PATH_PASSWORD_EDIT = "mobile/Staff.Login/passwordEdit"
private const val PATH_GET_PASS_RULES = "mobile/Staff.Login/getPassRules"
private const val PATH_INIT_INFO = "mobile/Order.Order/initInfo"

/**
 * 账号资料与安全数据能力（openspec data/profile；design 决策 1 方案 B 聚合）：
 * 服务端登出、修改密码、密码规则、密码状态。`LoginRepository` 保持登录专责。
 */
class ProfileRepository(
    private val gateway: ApiGateway,
    private val session: AuthSessionManager,
    @Suppress("unused") private val store: KeyValueStore
) {

    /** 登出：服务端尽力而为、失败不阻断；本地会话（令牌 + 展示名）必清（spec data/profile）。 */
    suspend fun logout() {
        try {
            gateway.postMessage(path = PATH_LOGOUT)
        } catch (e: Exception) {
            // 服务端登出失败不阻断登出流程（spec「服务端登出失败仍清理本地会话」）
        } finally {
            session.clearTokens()
        }
    }

    /** 修改密码（明文 body，对齐原工程 `toPlainTextRequestBody`）：成功清会话并返回服务端提示文案。 */
    suspend fun changePassword(newPassword: String): Result<String> = try {
        val message = gateway.postMessage(path = PATH_PASSWORD_EDIT, bodyText = newPassword)
        session.clearTokens()
        Result.success(message)
    } catch (e: Exception) {
        Result.failure(e)
    }

    /** 密码规则：防御式别名映射 + 正则长度区间提取 + 默认兜底（见 mapper）。 */
    suspend fun getPasswordRules(): Result<PasswordRulesEntity> = try {
        Result.success(gateway.postJson<PasswordRulesDto>(path = PATH_GET_PASS_RULES).toEntity())
    } catch (e: Exception) {
        Result.failure(e)
    }

    /**
     * 密码状态：`passStatus == 0` 需改密；字段缺失视为无需改密（spec data/profile）。
     * 查询失败由调用方按「无需改密」处理，不阻断主框架。
     */
    suspend fun loadPasswordStatus(): Result<Int> = try {
        val dto = gateway.postJson<InitInfoDto>(path = PATH_INIT_INFO)
        Result.success(dto.passStatus ?: 1)
    } catch (e: Exception) {
        Result.failure(e)
    }
}
