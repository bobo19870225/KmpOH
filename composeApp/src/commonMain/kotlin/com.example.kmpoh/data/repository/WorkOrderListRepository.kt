package com.example.kmpoh.data.repository

import com.example.kmpoh.data.model.dto.DayOrderDataDto
import com.example.kmpoh.data.model.dto.UnfinishedJobDateDto
import com.example.kmpoh.data.model.dto.WorkOrderDayCountDto
import com.example.kmpoh.data.model.dto.InitInfoDto
import com.example.kmpoh.data.model.entity.WorkOrderDayCountEntity
import com.example.kmpoh.data.model.entity.WorkOrderDayOrdersEntity
import com.example.kmpoh.data.model.mapper.WorkOrderListKeys
import com.example.kmpoh.data.model.mapper.parseColorArgb
import com.example.kmpoh.data.model.mapper.toEntity
import com.example.kmpoh.logger.BUSINESS_LOG_TAG
import com.example.kmpoh.logger.Logger
import com.example.kmpoh.network.ApiGateway
import com.example.kmpoh.network.MultipartTextContent
import com.example.kmpoh.network.postJson
import io.ktor.client.request.forms.FormDataContent
import io.ktor.http.Parameters

private const val PATH_DAY_ORDER = "/mobile/Order.Order/dayOrder"
private const val PATH_UNFINISH_JOBS = "/mobile/Order.Order/unfinishJobs"
private const val PATH_DAY_COUNT = "/mobile/Order.Order/dayCount"
private const val PATH_INIT_INFO = "/mobile/Order.Order/initInfo"

const val DAY_ORDER_PAGE_SIZE = 20
const val FIRST_PAGE = 1

/**
 * 工单列表数据出口（原样迁原工程 WorkOrderListRepository；spec data/work-order-list）。
 * `dayOrder`/`unfinishJobs` 为 FormUrlEncoded、`dayCount` 为 Multipart（决策 8），
 * 签名体统一以字段 JSON 文本入 `bodyText` 复用规范化。
 */
class WorkOrderListRepository(
    private val gateway: ApiGateway
) {
    // 跨平台无 @Volatile（JVM 专有注解）；单写多读的缓存映射，接受可见性延迟
    private var riskTitleColors: Map<String, Int> = emptyMap()

    fun riskColor(label: String): Int? = riskTitleColors[label]

    suspend fun loadDayOrders(
        jobDate: String,
        dayOrderType: String = WorkOrderListKeys.ALL,
        page: Int = FIRST_PAGE,
        limit: Int = DAY_ORDER_PAGE_SIZE
    ): Result<WorkOrderDayOrdersEntity> = try {
        val fields = mapOf(
            "job_date" to jobDate,
            "day_order_type" to dayOrderType.ifBlank { WorkOrderListKeys.ALL },
            "page" to page.toString(),
            "limit" to limit.toString()
        )
        val dto = gateway.post(
            path = PATH_DAY_ORDER,
            deserializer = DayOrderDataDto.serializer(),
            body = FormDataContent(Parameters.build {
                fields.forEach { (key, value) -> append(key, value) }
            }),
            bodyText = fields.toSignJson()
        )
        Logger.debug(BUSINESS_LOG_TAG, "Day order request succeeded")
        Result.success(dto.toEntity())
    } catch (e: Exception) {
        Logger.debug(BUSINESS_LOG_TAG, "Day order request failed: $e")
        Result.failure(e)
    }

    suspend fun loadUnfinishedJobDates(jobDate: String): Result<List<String>> = try {
        val fields = mapOf("job_date" to jobDate)
        val dto = gateway.post(
            path = PATH_UNFINISH_JOBS,
            deserializer = kotlinx.serialization.builtins.ListSerializer(UnfinishedJobDateDto.serializer()),
            body = FormDataContent(Parameters.build {
                fields.forEach { (key, value) -> append(key, value) }
            }),
            bodyText = fields.toSignJson()
        )
        Result.success(dto.map { it.jobDate }.filter { it.isNotBlank() }.distinct())
    } catch (e: Exception) {
        Logger.debug(BUSINESS_LOG_TAG, "Unfinished jobs request failed: $e")
        Result.failure(e)
    }

    suspend fun loadDayCounts(month: String): Result<List<WorkOrderDayCountEntity>> = try {
        val fields = mapOf("month" to month)
        val dto = gateway.post(
            path = PATH_DAY_COUNT,
            deserializer = kotlinx.serialization.builtins.ListSerializer(WorkOrderDayCountDto.serializer()),
            body = MultipartTextContent(fields),
            bodyText = fields.toSignJson()
        )
        Result.success(
            dto.map {
                WorkOrderDayCountEntity(
                    date = it.date,
                    count = it.count,
                    unfinished = it.unfinish,
                    overdue = it.overdue
                )
            }.filter { it.date.isNotBlank() }
        )
    } catch (e: Exception) {
        Logger.debug(BUSINESS_LOG_TAG, "Day count request failed: $e")
        Result.failure(e)
    }

    /** 风险标签色配置（spec「风险标签色配置」）：非法色值忽略；失败保留旧映射。 */
    suspend fun loadRiskColors(): Result<Unit> = try {
        val dto = gateway.postJson<InitInfoDto>(path = PATH_INIT_INFO)
        riskTitleColors = dto.colorConfig.riskTitle
            .mapNotNull { (title, color) -> parseColorArgb(color)?.let { title to it } }
            .toMap()
        Logger.debug(BUSINESS_LOG_TAG, "Risk colors loaded count=${riskTitleColors.size}")
        Result.success(Unit)
    } catch (e: Exception) {
        Logger.debug(BUSINESS_LOG_TAG, "Init info request failed: $e")
        Result.failure(e)
    }
}

/** 字段映射 → 签名规范化用 JSON 文本（决策 8）。 */
private fun Map<String, String>.toSignJson(): String =
    entries.joinToString(",", "{", "}") { (key, value) -> "\"$key\":\"$value\"" }
