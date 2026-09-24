
import org.jetbrains.kotlin.gradle.ExperimentalKotlinGradlePluginApi
import org.jetbrains.kotlin.gradle.dsl.JvmTarget
import android.databinding.tool.ext.capitalizeUS
import java.util.Properties

plugins {
    alias(libs.plugins.kotlinMultiplatform)
    alias(libs.plugins.androidApplication)
    alias(libs.plugins.composeMultiplatform)
    alias(libs.plugins.composeCompiler)
    alias(libs.plugins.kotlinSerialization)
}

kotlin {
    androidTarget {
        @OptIn(ExperimentalKotlinGradlePluginApi::class)
        compilerOptions {
            jvmTarget.set(JvmTarget.JVM_11) 
        }
    }

    listOf(
        iosX64(),    
        iosArm64(),   
        iosSimulatorArm64()
    ).forEach { iosTarget ->
        iosTarget.binaries.framework {
            baseName = "ComposeApp"
            isStatic = true    
        }
    }
    
  // 配置OHOS（华为鸿蒙）多架构目标
    listOf(
        ohosArm64(),   // 真机 arm64
    ).forEach { ohosTarget ->
        ohosTarget.binaries.sharedLib {
            baseName = "kn"
            export(libs.compose.multiplatform.export)
            linkerOpts("-lz")
            // 存储（platform.ArkData.Preferences）、协程调度（platform.FunctionFlowRuntimeKit，
            // kotlinx-coroutines 的 FfrtDefaultDispatcher）与日志（platform.PerformanceAnalysisKit.HiLog，
            // PlatformLog.ohos）：cinterop 的 OH_Preferences* / ffrt_* 均为弱导入（WEAK UND），
            // 弱引用不触发 as-needed 保留 → libohpreferences.so / libffrt.z.so
            // 缺失 DT_NEEDED → 运行时不加载 → 弱符号解析为空 → undefined-api-protection 抛：
            //   - Preferences：FileFailedToInitializeException（nova 13 实测启动即崩）
            //   - FFRT：IllegalStateException: Missing API symbol:
            //     ffrt_alloc_auto_managed_function_storage_base（点击登录派发协程即崩，nova 13 实测）
            // OH_LOG_* 同为弱导入（readelf 可见 WEAK UND），-lhilog_ndk.z 一并强制保留（否则 HiLog 出口同理失效）。
            // 强制保留这三个依赖。注意 sysroot 中 FFRT 只有 libffrt.z.so（OHOS .z 系统库命名），
            // 须写 -lffrt.z 而非 -lffrt。
            // 注意本工具链直接调用 ld.lld，须写裸标志（-Wl, 前缀会报 unknown argument）。
            linkerOpts("--no-as-needed", "-lohpreferences", "-lffrt.z", "-lhilog_ndk.z", "--as-needed")
                // 渲染模式
 	             // 背景：当 libkn.so 为旧编译产物时，其 DT_NEEDED 可能缺少以下库（正确构建时
 	             // NativeTasksConfiguration.kt 已通过 -l 选项将它们写入 DT_NEEDED）。
 	             // 在 build.gradle.kts 中统一补全，避免在 CMakeLists.txt 中硬编码。
 	             val rendererBackend = rootProject.findProperty("rendererBackend")?.toString() ?: "fusion-renderer"
                    if (rendererBackend == "fusion-renderer") {
 	                 linkerOpts(
 	                     "-lnative_drawing",    // OH_Drawing_*（字体、绘制）
 	                     "-limage_source",       // OH_ImageSourceNative_*（图像解码）
 	                     "-lpixelmap",           // OH_PixelMap_*
 	                     "-lpixelmap_ndk.z",     // OH_PixelMapNdk_*
 	                     "-lnative_window",      // OH_NativeWindow_*
 	                     "-lace_napi.z",         // N-API
 	                     "-lhilog_ndk.z",        // HiLog 日志
 	                     "-lhitrace_ndk.z",      // HiTrace 性能追踪
 	                     "-luv",                 // libuv 事件循环
 	                     "-lunwind",             // 栈展开
 	                     "-licu",               // ICU 文本处理
 	                 )
 	             }
        }
    }

    sourceSets {
        androidMain.dependencies {
            implementation(libs.ktor.client.okhttp)
            implementation(libs.androidx.activity.compose)
            implementation(libs.androidx.lifecycle.viewmodelCompose)
            implementation(libs.androidx.lifecycle.runtimeCompose)
            implementation(libs.androidx.collection)
        }
        commonTest.dependencies {
            // 1.1 修复既有缺陷：此前从未声明 commonTest 依赖，kotlin.test 无法解析
            implementation(libs.kotlin.test)
            implementation(libs.ktor.client.mock)
        }
        commonMain.dependencies {
            // 网络层（openspec/changes/migrate-network-and-login）：Ktor 3.3.3-1.0.0 fork 线
            // （CPF-KMP-CMP 三方库文档对 KMP 2.2.21 & CMP 1.9.2 的推荐版本）。
            // 引擎按平台拆分：Android=OkHttp、iOS=Darwin、鸿蒙=自定义 RcpHttpClientEngine
            // （经 NAPI 桥接 ArkTS RCP——ktor-network-tls nonJvm 无 TLS 实现，CIO 不能用于
            //  HTTPS；且不能依赖引擎服务发现，实测抛 "Failed to find HTTP client engine
            //  implementation"）。鸿蒙侧无需任何 ktor 引擎工件。
            implementation(libs.ktor.client.core)
            implementation(libs.ktor.client.content.negotiation)
            implementation(libs.ktor.client.logging)
            implementation(libs.ktor.serialization.kotlinx.json)
            implementation(libs.kotlinx.serialization.json)
            implementation(compose.runtime)                     
            implementation(compose.foundation)                   
            implementation(compose.material3)                    
            implementation(compose.ui)                          
            implementation(compose.components.resources)         
        }
          // iOS平台共享代码
                val iosMain = sourceSets.create("iosMain").apply {
                    dependsOn(commonMain.get())
                }
                // iOS平台依赖
                iosMain.dependencies {
                    implementation(libs.ktor.client.darwin)
                }
                // iOS平台变体依赖关系
                listOf("iosX64Main", "iosArm64Main", "iosSimulatorArm64Main").forEach {
                    sourceSets.getByName(it).dependsOn(iosMain)
                }

         // OHOS 共享（对应目录 src/ohosMain/，arm64/x64 共用）
        val ohosMain = sourceSets.create("ohosMain").apply {
            dependsOn(commonMain.get())
        }
        ohosMain.dependencies {
            api(libs.compose.multiplatform.export)
            // 鸿蒙端网络引擎是自定义 RcpHttpClientEngine（network/bridge/），经 NAPI 桥接
            // ArkTS RCP（RemoteCommunicationKit），不依赖任何 ktor 引擎工件。
        }
        val ohosArm64Main by getting {
            dependsOn(ohosMain)
        }
    }
}


android {
    namespace = "com.example.kmpoh"                     
    compileSdk = libs.versions.android.compileSdk.get().toInt()  

    defaultConfig {
        applicationId = "com.example.kmpoh"                  
        minSdk = libs.versions.android.minSdk.get().toInt()     
        targetSdk = libs.versions.android.targetSdk.get().toInt()
        versionCode = 1                                       
        versionName = "1.0"                                  
    }
    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
        }
    }
    testOptions {
        // JVM 单测中 android.util.Log 等返回默认值（Logger 平台输出在单测里不抛异常）
        unitTests.isReturnDefaultValues = true
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11   
        targetCompatibility = JavaVersion.VERSION_11   
    }
}

dependencies {
    debugImplementation(libs.compose.ui.tooling)   
}



// Harmony App 输出目录（支持命令行 --harmonyAppPath）
val harmonyAppDir: File = run {
    val cliPath = project.findProperty("harmonyAppPath") as String?
    if (cliPath.isNullOrBlank()) {
        // 默认：项目根目录 /harmonyApp
        rootProject.file("harmonyApp")
    } else {
        // 命令行传入的路径
        file(cliPath)
    }
}

// 字符串首字母大写工具函数
fun String.capitalizeUS(): String = this.replaceFirstChar { 
    if (it.isLowerCase()) it.titlecase() else it.toString() 
}


// 为不同类型(debug、release)OHOS构建注册Copy任务并发布到Harmony App目录
arrayOf("debug", "release").forEach { type ->
    tasks.register<Copy>("publish${type.capitalizeUS()}BinariesToHarmonyApp") {
        group = "harmony" // 归类到harmony任务组
        dependsOn(
            "link${type.capitalizeUS()}SharedOhosArm64",
            "assembleOhosArm64MainResources",
        )
        duplicatesStrategy = DuplicatesStrategy.INCLUDE
         into(harmonyAppDir) // 输出目标目录
        from("build/bin/ohosArm64/${type}Shared/libkn_api.h") { // 复制头文件
            into("entry/src/main/cpp/include/arm64-v8a/")         // 指定目录
        }
        from(project.file("build/bin/ohosArm64/${type}Shared/libkn.so")) { // 复制共享库文件
            into("entry/libs/arm64-v8a/")           // 指定目标目录
        }
	    // 资源必须取自"已装配"产物（assembledResources/ohosArm64Main），而不是
	    // src/commonMain/composeResources 源码目录。
	    // 原因：drawable 的源码 XML 可以直接使用，但**字符串资源必须先由 Compose 插件
	    // 编译成 .cvr**，运行时会去找 values/strings.commonMain.cvr。
	    // 只拷源码会让鸿蒙端启动即崩：
	    //   IllegalArgumentException: Failed to open raw file:
	    //   composeResources/kmpoh.composeapp.generated.resources/values/strings.commonMain.cvr
	    // 该目录树已自带 `kmpoh.composeapp.generated.resources` 这一层，故直接落到
	    // rawfile/composeResources/ 下即可。
	    from(layout.buildDirectory.dir("generated/compose/resourceGenerator/assembledResources/ohosArm64Main/composeResources")) {
	        into("entry/src/main/resources/rawfile/composeResources/")
	    }

    }
}


// ---------------------------------------------------------------------------
// API 配置注入（openspec/changes/migrate-network-and-login/design.md 决策 7）
// 取值优先级：环境变量 > local.properties > 默认值。签名密钥不入库：
// 仅经环境变量 API_SIGNATURE_SECRET 或 local.properties（已被 .gitignore 忽略）注入。
// 生成物位于 build/generated/apiConfig/（build/ 不入库）。
// ---------------------------------------------------------------------------
// 经 providers.fileContents 读取：配置缓存可感知 local.properties 变更（直接文件 IO 不被追踪，
// 改完 local.properties 再构建可能吃到陈旧配置——联调期踩过）
val apiLocalPropsText: String = providers
    .fileContents(rootProject.layout.projectDirectory.file("local.properties"))
    .asText.orNull ?: ""
val apiLocalProps = Properties().apply {
    if (apiLocalPropsText.isNotBlank()) {
        apiLocalPropsText.byteInputStream().use { load(it) }
    }
}

fun apiConfigValue(name: String): String? =
    System.getenv(name)?.takeIf { it.isNotBlank() }
        ?: apiLocalProps.getProperty(name)?.takeIf { it.isNotBlank() }

val apiEnvironment = apiConfigValue("API_ENVIRONMENT") ?: "dev"
val apiBaseUrlOverride = apiConfigValue("API_BASE_URL")
val apiSignatureSecret = apiConfigValue("API_SIGNATURE_SECRET") ?: ""
val apiSignatureMode = apiConfigValue("API_SIGNATURE_MODE") ?: "off"
val apiSignatureSkewSeconds = (apiConfigValue("API_SIGNATURE_MAX_CLOCK_SKEW_SECONDS") ?: "300")
    .trim().toIntOrNull() ?: error("API_SIGNATURE_MAX_CLOCK_SKEW_SECONDS must be an integer")

// 三环境地址与原工程 productFlavors 取值逐字一致（含 dev 拼写，见 design.md Open Questions）
val apiBaseUrl = apiBaseUrlOverride ?: when (apiEnvironment) {
    "dev" -> "https://tchnician.mobile.local.cn/"
    "uat" -> "https://uatapp.lbsapps.cn/"
    "prod" -> "https://v1.teach.lbsapps.cn/"
    else -> error("Unknown API_ENVIRONMENT '$apiEnvironment' (expected dev|uat|prod)")
}
val apiSignatureModeNormalized = when (apiSignatureMode) {
    "off", "request", "mutual" -> apiSignatureMode
    else -> error("Unknown API_SIGNATURE_MODE '$apiSignatureMode' (expected off|request|mutual)")
}

val generateApiConfig = tasks.register("generateApiConfig") {
    // 配置缓存要求 doLast 只捕获纯值，脚本级函数/对象不可进入闭包
    val outDir = layout.buildDirectory.dir("generated/apiConfig/kotlin")
    val environmentValue = apiEnvironment
    val baseUrlValue = apiBaseUrl
    val modeValue = apiSignatureModeNormalized
    val secretValue = apiSignatureSecret
    val skewValue = apiSignatureSkewSeconds
    outputs.dir(outDir)
    inputs.property("apiEnvironment", environmentValue)
    inputs.property("apiBaseUrl", baseUrlValue)
    inputs.property("apiSignatureMode", modeValue)
    inputs.property("apiSignatureSecret", secretValue)
    inputs.property("apiSignatureSkewSeconds", skewValue)
    doLast {
        val esc: (String) -> String = { s -> s.replace("\\", "\\\\").replace("\"", "\\\"") }
        val file = outDir.get().file("GeneratedApiConfig.kt").asFile
        file.parentFile.mkdirs()
        file.writeText(
            """
            |// 由 :composeApp:generateApiConfig 生成（build/generated/，不入库）。请勿手改。
            |// 配置取值：环境变量 > local.properties > 默认值；密钥仅经上述本地渠道注入。
            |package com.example.kmpoh.network
            |
            |/** 构建期注入的 API 配置（openspec/changes/migrate-network-and-login）。 */
            |internal object GeneratedApiConfig {
            |    /** dev | uat | prod */
            |    const val ENVIRONMENT: String = "${esc(environmentValue)}"
            |    const val BASE_URL: String = "${esc(baseUrlValue)}"
            |    /** off | request | mutual（对齐原工程 ApiSignatureMode） */
            |    const val SIGNATURE_MODE: String = "${esc(modeValue)}"
            |    /** 本地注入、不入库；为空表示不签名（对齐 spec「签名密钥缺失」场景） */
            |    const val API_SIGNATURE_SECRET: String = "${esc(secretValue)}"
            |    const val SIGNATURE_MAX_CLOCK_SKEW_SECONDS: Int = $skewValue
            |}
            |
            """.trimMargin()
        )
    }
}

kotlin.sourceSets.commonMain {
    kotlin.srcDir(generateApiConfig.map { it.outputs.files.singleFile })
}

// 确保生成先于所有 Kotlin 编译（fork 的 KGP 未暴露 KotlinCompilation 类型，按任务名挂钩）
tasks.configureEach {
    if (name.startsWith("compile") && name.contains("Kotlin")) {
        dependsOn(generateApiConfig)
    }
}
