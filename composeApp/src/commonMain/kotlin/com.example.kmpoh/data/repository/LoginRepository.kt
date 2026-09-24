package com.example.kmpoh.data.repository

import com.example.kmpoh.data.model.dto.LoginRequestDto
import com.example.kmpoh.data.model.dto.LoginResponseDto
import com.example.kmpoh.data.model.mapper.effectiveAccessToken
import com.example.kmpoh.data.model.mapper.effectiveRefreshToken
import com.example.kmpoh.data.model.mapper.toUserEntity
import com.example.kmpoh.data.model.mapper.toUiModel
import com.example.kmpoh.data.model.ui.UserUiModel
import com.example.kmpoh.logger.BUSINESS_LOG_TAG
import com.example.kmpoh.logger.DEBUG_LOG_TAG
import com.example.kmpoh.logger.Logger
import com.example.kmpoh.network.ApiGateway
import com.example.kmpoh.network.AuthSessionManager
import com.example.kmpoh.network.BusinessApiException
import com.example.kmpoh.network.NetworkException
import com.example.kmpoh.network.GeneratedApiConfig
import com.example.kmpoh.network.NetworkMessages
import com.example.kmpoh.network.createApiClient
import com.example.kmpoh.network.postJson
import com.example.kmpoh.storage.KeyValueStore
import com.example.kmpoh.storage.PLATFORM_NAME
import com.example.kmpoh.storage.createKeyValueStore
import com.example.kmpoh.storage.getOrCreateDeviceId

private const val PATH_LOGIN = "mobile/Staff.Login/login"

/**
 * 登录数据源（openspec/changes/migrate-network-and-login/specs/data/login）。
 * 出口约定与原工程一致：`Result<T>`，失败信息为可直接呈现的用户文案。
 */
interface LoginRepository {
    suspend fun login(staffCode: String, password: String): Result<UserUiModel>
}

/**
 * 基于 Ktor 网关的真实登录实现：组包 → 登录请求 → 持久化令牌 → DTO→Entity→UiModel。
 * 成功即写会话令牌；失败不写任何令牌。
 */
class NetworkLoginRepository(
    private val gateway: ApiGateway,
    private val session: AuthSessionManager,
    private val store: KeyValueStore
) : LoginRepository {

    override suspend fun login(staffCode: String, password: String): Result<UserUiModel> = try {
        val request = LoginRequestDto(
            staffCode = staffCode,
            password = password,
            deviceId = getOrCreateDeviceId(store),
            platform = PLATFORM_NAME
        )
        // 登录为令牌获取调用：不带认证头；其 401 也不会触发刷新（网关对登录路径豁免）
        val response = gateway.postJson<LoginResponseDto, LoginRequestDto>(
            path = PATH_LOGIN,
            body = request,
            authenticated = false
        )
        session.saveTokens(
            accessToken = response.effectiveAccessToken(),
            refreshToken = response.effectiveRefreshToken()
        )
        val model = response.toUserEntity().toUiModel()
        session.saveUserName(model.displayName)
        Logger.debug(BUSINESS_LOG_TAG, "Login success userId=${response.userId}")
        Result.success(model)
    } catch (e: Exception) {
        // 排障关键日志：异常类因果链（tasks 6.1 归因用）
        Logger.debugSingleLine(
            DEBUG_LOG_TAG,
            "Login failure chain: " +
                generateSequence<Throwable>(e) { it.cause }.joinToString(" <- ") { it::class.simpleName ?: "?" }
        )
        Result.failure(Exception(e.toLoginFailureMessage(), e))
    }
}

/**
 * 登录失败文案映射（spec「登录失败文案映射」）：
 * 服务端提示优先 → 网络类别文案 → 通用登录失败兜底。
 */
internal fun Throwable.toLoginFailureMessage(): String = when (this) {
    is BusinessApiException -> businessMessage.ifBlank { NetworkMessages.LOGIN_FALLBACK }
    is NetworkException -> (message ?: "").ifBlank { NetworkMessages.LOGIN_FALLBACK }
    else -> NetworkMessages.LOGIN_FALLBACK
}

/**
 * 全局装配单例（手写服务定位器，Hilt 的跨端替代路线）：登录数据栈与 `App()` 的
 * 登录失效订阅必须共享同一 [AuthSessionManager] 实例，否则事件流接不上
 * （openspec/changes/2026-09-24-migrate-navigation-and-home-shell）。后续引入正式 DI 容器时替换此处。
 */
object AppGraph {
    val store by lazy { createKeyValueStore() }
    val session by lazy { AuthSessionManager(store) }
    val gateway by lazy { ApiGateway(createApiClient(), session, deviceId = getOrCreateDeviceId(store)) }
    val loginRepository by lazy {
        // 启动期输出生效配置（不含密钥），便于联调时一眼确认环境/地址是否符合预期
        Logger.debug(
            DEBUG_LOG_TAG,
            "ApiConfig env=${GeneratedApiConfig.ENVIRONMENT} baseUrl=${GeneratedApiConfig.BASE_URL} " +
                "signature=${GeneratedApiConfig.SIGNATURE_MODE} log=${Logger.isTestEnvironment}"
        )
        NetworkLoginRepository(gateway, session, store)
    }
    val profileRepository by lazy { ProfileRepository(gateway, session, store) }
}

/** 组装登录数据栈（手写依赖装配，design 决策 9）：
 * KV 存储 → 会话管理 → API 网关 → 登录仓库，收敛到 [AppGraph] 单例。 */
fun createLoginRepository(): LoginRepository = AppGraph.loginRepository

/** 组装账号资料与安全数据栈（design 决策 1 方案 B 聚合），收敛到 [AppGraph] 单例。 */
fun createProfileRepository(): ProfileRepository = AppGraph.profileRepository
