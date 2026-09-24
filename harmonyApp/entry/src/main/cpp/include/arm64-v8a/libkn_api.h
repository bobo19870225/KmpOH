#ifndef KONAN_LIBKN_H
#define KONAN_LIBKN_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
typedef bool            libkn_KBoolean;
#else
typedef _Bool           libkn_KBoolean;
#endif
typedef unsigned short     libkn_KChar;
typedef signed char        libkn_KByte;
typedef short              libkn_KShort;
typedef int                libkn_KInt;
typedef long long          libkn_KLong;
typedef unsigned char      libkn_KUByte;
typedef unsigned short     libkn_KUShort;
typedef unsigned int       libkn_KUInt;
typedef unsigned long long libkn_KULong;
typedef float              libkn_KFloat;
typedef double             libkn_KDouble;
typedef float __attribute__ ((__vector_size__ (16))) libkn_KVector128;
typedef void*              libkn_KNativePtr;
struct libkn_KType;
typedef struct libkn_KType libkn_KType;

typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Byte;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Short;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Int;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Long;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Float;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Double;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Char;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Boolean;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Unit;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_UByte;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_UShort;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_UInt;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_ULong;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_Platform;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Any;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Array;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_serialization_encoding_Decoder;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_serialization_encoding_Encoder;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_serialization_KSerializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_UserDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_UserDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_UserDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_collections_List;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_serialization_json_JsonElement;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_collections_Map;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_UserEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_mapper_WorkOrderListKeys;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_repository_LoginRepository;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_repository_ProfileRepository;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_repository_WorkOrderListRepository;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_repository_NetworkLoginRepository;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_ApiGateway;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_AuthSessionManager;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_storage_KeyValueStore;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_data_repository_AppGraph;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_logger_LogLevel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_logger_LogLevel_DEBUG;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_logger_LogLevel_INFO;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_logger_LogLevel_WARN;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_logger_LogLevel_ERROR;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_logger_Logger;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Throwable;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_serialization_json_Json;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_io_ktor_client_HttpClient;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Function1;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_bridge_ConnectTimeoutException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_bridge_SocketTimeoutException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_bridge_UnknownHostException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_bridge_ConnectException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_io_ktor_http_Headers;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignatureEngine;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode_Off;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode_RequestOnly;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode_Mutual;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_collections_Set;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_signature_SignatureVerificationException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_BusinessApiException;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_AuthSessionEvent;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_coroutines_flow_SharedFlow;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_MultipartTextContent;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_io_ktor_http_ContentType;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkException_Http;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkException_Timeout;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkException_Unavailable;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkException_Transport;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkException_Parsing;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkMessages;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkRequestTracker;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_coroutines_flow_StateFlow;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_network_NetworkRequestTracker_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Function0;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_login_LoginViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_coroutines_CoroutineScope;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_androidx_compose_ui_Modifier;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_main_MainUiState;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_main_MainViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_message_MessageViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Required;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Failed;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_org_jetbrains_compose_resources_StringResource;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ProfileUiState;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ProfileEffect;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ProfileEffect_LoggedOut;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_profile_ProfileViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus_Waiting;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus_Running;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus_Done;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrder;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_datetime_LocalDate;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_datetime_YearMonth;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_utils_UiState;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_androidx_navigation_NavHostController;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_router_AppDestination;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_router_AppDestination_Login;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_router_AppDestination_Main;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_router_AppDestination_Companion;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_storage_StorageKeys;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_androidx_compose_ui_text_input_VisualTransformation;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_androidx_compose_foundation_text_KeyboardOptions;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_androidx_compose_foundation_text_KeyboardActions;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_ui_theme_AppColors;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_ui_theme_AppDimens;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_ui_theme_AppFontSize;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_OhosPlatform;

extern void OhosHttpBridgeRespond(void* requestId, void* responseJson);
extern void OhosHttpTransportInit(void* postFn);
extern void* MainArkUIViewController(void* env);
extern void InitJsRenderNodeContext(void* env, void* nodeConstructor, void* statusModifyConstructor, libkn_KDouble ratio, libkn_KBoolean fixed);
extern void androidx_compose_ui_arkui_ArkUIViewController_aboutToAppear(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_aboutToDisappear(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_cancelSyncRefresh(void* controllerRef, libkn_KInt refreshId);
extern void androidx_compose_ui_arkui_ArkUIViewController_dispatchHoverEvent(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_dispatchMouseEvent(void* controllerRef);
extern libkn_KBoolean androidx_compose_ui_arkui_ArkUIViewController_dispatchTouchEvent(void* controllerRef, void* nativeTouchEvent, libkn_KBoolean ignoreInteropView);
extern void AndroidxComposeUiArkuiArkUiViewControllerDraw(void* controllerRef, void* canvas);
extern libkn_KInt androidx_compose_ui_arkui_ArkUIViewController_findNodeIdAt(void* controllerRef, libkn_KFloat x, libkn_KFloat y);
extern const char* androidx_compose_ui_arkui_ArkUIViewController_getId(void* controllerRef);
extern void* AndroidxComposeUiArkuiArkUiViewControllerGetJsNode(void* controllerRef);
extern libkn_KInt androidx_compose_ui_arkui_ArkUIViewController_getRendererTypeId();
extern void* androidx_compose_ui_arkui_ArkUIViewController_getXComponentRender(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_initFusionRendererNode(void* controllerRef, libkn_KBoolean enableCApi, void* rootContent, void* frameMgr);
extern void androidx_compose_ui_arkui_ArkUIViewController_keyboardWillHide(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_keyboardWillShow(void* controllerRef, libkn_KFloat keyboardHeight);
extern libkn_KBoolean androidx_compose_ui_arkui_ArkUIViewController_onBackPress(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onConfigurationUpdate(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onFinalize(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onFocusEvent(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onFrame(void* controllerRef, libkn_KLong timestamp, libkn_KLong targetTimestamp);
extern void AndroidXComposeUIArkUIArkUIViewControllerOnIdle(void* controllerRef, libkn_KLong timeLeft);
extern void androidx_compose_ui_arkui_ArkUIViewController_onKeyEvent(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onPageHide(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onPageShow(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onSurfaceChanged(void* controllerRef, libkn_KInt width, libkn_KInt height);
extern void androidx_compose_ui_arkui_ArkUIViewController_onSurfaceCreated(void* controllerRef, void* xcomponentPtr, libkn_KInt width, libkn_KInt height);
extern void androidx_compose_ui_arkui_ArkUIViewController_onSurfaceDestroyed(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onSurfaceHide(void* controllerRef);
extern void androidx_compose_ui_arkui_ArkUIViewController_onSurfaceShow(void* controllerRef);
extern libkn_KInt androidx_compose_ui_arkui_ArkUIViewController_requestSyncRefresh(void* controllerRef);
extern const char* androidx_compose_ui_arkui_ArkUIViewController_sendMessage(void* controllerRef, const char* type, const char* message);
extern void androidx_compose_ui_arkui_ArkUIViewController_setContext(void* controllerRef, void* context);
extern void androidx_compose_ui_arkui_ArkUIViewController_setEnv(void* controllerRef, void* env);
extern void androidx_compose_ui_arkui_ArkUIViewController_setId(void* controllerRef, const char* id);
extern void androidx_compose_ui_arkui_ArkUIViewController_setLocaleAndStringProvider(void* controllerRef, void* provider);
extern void androidx_compose_ui_arkui_ArkUIViewController_setMessenger(void* controllerRef, void* messenger);
extern void androidx_compose_ui_arkui_ArkUIViewController_setRendererBackendId(void* controllerRef, libkn_KInt backendId);
extern void androidx_compose_ui_arkui_ArkUIViewController_setRootView(void* controllerRef, void* backRootView, void* foreRootView, void* touchableRootView);
extern void androidx_compose_ui_arkui_ArkUIViewController_setUIContext(void* controllerRef, void* uiContext);
extern void androidx_compose_ui_arkui_ArkUIViewController_setXComponentRender(void* controllerRef, void* render);
extern void androidx_compose_ui_arkui_init(void* env, void* exports);

typedef struct {
  /* Service functions. */
  void (*DisposeStablePointer)(libkn_KNativePtr ptr);
  void (*DisposeString)(const char* string);
  libkn_KBoolean (*IsInstance)(libkn_KNativePtr ref, const libkn_KType* type);
  libkn_kref_kotlin_Byte (*createNullableByte)(libkn_KByte);
  libkn_KByte (*getNonNullValueOfByte)(libkn_kref_kotlin_Byte);
  libkn_kref_kotlin_Short (*createNullableShort)(libkn_KShort);
  libkn_KShort (*getNonNullValueOfShort)(libkn_kref_kotlin_Short);
  libkn_kref_kotlin_Int (*createNullableInt)(libkn_KInt);
  libkn_KInt (*getNonNullValueOfInt)(libkn_kref_kotlin_Int);
  libkn_kref_kotlin_Long (*createNullableLong)(libkn_KLong);
  libkn_KLong (*getNonNullValueOfLong)(libkn_kref_kotlin_Long);
  libkn_kref_kotlin_Float (*createNullableFloat)(libkn_KFloat);
  libkn_KFloat (*getNonNullValueOfFloat)(libkn_kref_kotlin_Float);
  libkn_kref_kotlin_Double (*createNullableDouble)(libkn_KDouble);
  libkn_KDouble (*getNonNullValueOfDouble)(libkn_kref_kotlin_Double);
  libkn_kref_kotlin_Char (*createNullableChar)(libkn_KChar);
  libkn_KChar (*getNonNullValueOfChar)(libkn_kref_kotlin_Char);
  libkn_kref_kotlin_Boolean (*createNullableBoolean)(libkn_KBoolean);
  libkn_KBoolean (*getNonNullValueOfBoolean)(libkn_kref_kotlin_Boolean);
  libkn_kref_kotlin_Unit (*createNullableUnit)(void);
  libkn_kref_kotlin_UByte (*createNullableUByte)(libkn_KUByte);
  libkn_KUByte (*getNonNullValueOfUByte)(libkn_kref_kotlin_UByte);
  libkn_kref_kotlin_UShort (*createNullableUShort)(libkn_KUShort);
  libkn_KUShort (*getNonNullValueOfUShort)(libkn_kref_kotlin_UShort);
  libkn_kref_kotlin_UInt (*createNullableUInt)(libkn_KUInt);
  libkn_KUInt (*getNonNullValueOfUInt)(libkn_kref_kotlin_UInt);
  libkn_kref_kotlin_ULong (*createNullableULong)(libkn_KULong);
  libkn_KULong (*getNonNullValueOfULong)(libkn_kref_kotlin_ULong);

  /* User functions. */
  struct {
    struct {
      struct {
        struct {
          struct {
            struct {
              struct {
                struct {
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto (*InitInfoDto)(libkn_kref_kotlin_Int passStatus, libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto colorConfig);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto (*get_colorConfig)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz);
                    libkn_kref_kotlin_Int (*get_passStatus)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz);
                    libkn_kref_kotlin_Int (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz, libkn_kref_kotlin_Int passStatus, libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto colorConfig);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_InitInfoDto thiz);
                  } InitInfoDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto (*LoginRequestDto)(const char* staffCode, const char* password, const char* deviceId, const char* platform);
                    const char* (*get_deviceId)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*get_password)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*get_platform)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*get_staffCode)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz, const char* staffCode, const char* password, const char* deviceId, const char* platform);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_LoginRequestDto thiz);
                  } LoginRequestDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto (*LoginResponseDto)(const char* token, libkn_KInt userId, const char* name, const char* code, const char* phone, const char* accessToken, const char* refreshToken, libkn_kref_com_example_kmpoh_data_model_dto_UserDto user);
                    const char* (*get_accessToken)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*get_code)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*get_name)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*get_phone)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*get_refreshToken)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*get_token)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_UserDto (*get_user)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    libkn_KInt (*get_userId)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*component5)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*component6)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*component7)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_UserDto (*component8)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz, const char* token, libkn_KInt userId, const char* name, const char* code, const char* phone, const char* accessToken, const char* refreshToken, libkn_kref_com_example_kmpoh_data_model_dto_UserDto user);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_LoginResponseDto thiz);
                  } LoginResponseDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_UserDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_UserDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_UserDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_UserDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_UserDto (*UserDto)(libkn_KLong id, libkn_KInt userId, const char* name, const char* phone, const char* avatarUrl, const char* email, const char* role, libkn_KBoolean isActive);
                    const char* (*get_avatarUrl)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*get_email)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_KLong (*get_id)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_KBoolean (*get_isActive)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*get_name)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*get_phone)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*get_role)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_KInt (*get_userId)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_KLong (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*component5)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*component6)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*component7)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_KBoolean (*component8)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_UserDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz, libkn_KLong id, libkn_KInt userId, const char* name, const char* phone, const char* avatarUrl, const char* email, const char* role, libkn_KBoolean isActive);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_UserDto thiz);
                  } UserDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto (*PasswordRulesDto)(libkn_kref_kotlin_collections_List rules, libkn_kref_kotlinx_serialization_json_JsonElement minLength, libkn_kref_kotlinx_serialization_json_JsonElement minLen, libkn_kref_kotlinx_serialization_json_JsonElement passwordMin, libkn_kref_kotlinx_serialization_json_JsonElement maxLength, libkn_kref_kotlinx_serialization_json_JsonElement maxLen, libkn_kref_kotlinx_serialization_json_JsonElement passwordMax, libkn_kref_kotlinx_serialization_json_JsonElement strength, libkn_kref_kotlinx_serialization_json_JsonElement passwordStrength, libkn_kref_kotlinx_serialization_json_JsonElement level, const char* regex, const char* rule, const char* desc, const char* lengthMessage, const char* weakMessage);
                    const char* (*get_desc)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*get_lengthMessage)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_level)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_maxLen)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_maxLength)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_minLen)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_minLength)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_passwordMax)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_passwordMin)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_passwordStrength)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*get_regex)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*get_rule)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlin_collections_List (*get_rules)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_strength)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*get_weakMessage)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlin_collections_List (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component10)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*component11)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*component12)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*component13)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*component14)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    const char* (*component15)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component5)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component6)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component7)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component8)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component9)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz, libkn_kref_kotlin_collections_List rules, libkn_kref_kotlinx_serialization_json_JsonElement minLength, libkn_kref_kotlinx_serialization_json_JsonElement minLen, libkn_kref_kotlinx_serialization_json_JsonElement passwordMin, libkn_kref_kotlinx_serialization_json_JsonElement maxLength, libkn_kref_kotlinx_serialization_json_JsonElement maxLen, libkn_kref_kotlinx_serialization_json_JsonElement passwordMax, libkn_kref_kotlinx_serialization_json_JsonElement strength, libkn_kref_kotlinx_serialization_json_JsonElement passwordStrength, libkn_kref_kotlinx_serialization_json_JsonElement level, const char* regex, const char* rule, const char* desc, const char* lengthMessage, const char* weakMessage);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                    libkn_kref_kotlin_Int (*intValue)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz, libkn_kref_kotlin_Array values);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRulesDto thiz);
                  } PasswordRulesDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto (*PasswordRuleDto)(const char* regex, const char* message);
                    const char* (*get_message)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz);
                    const char* (*get_regex)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz, const char* regex, const char* message);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_PasswordRuleDto thiz);
                  } PasswordRuleDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto (*DayOrderDataDto)(libkn_kref_kotlin_collections_List list, libkn_kref_kotlin_collections_List begin, libkn_kref_kotlin_collections_List inProgress, libkn_kref_kotlin_collections_List complete, libkn_KInt beginCount, libkn_KInt inProgressCount, libkn_KInt completeCount, libkn_KInt beginPage, libkn_KInt beginCurrentPage, libkn_KInt inProgressPage, libkn_KInt inProgressCurrentPage, libkn_KInt completePage, libkn_KInt completeCurrentPage);
                    libkn_kref_kotlin_collections_List (*get_begin)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_beginCount)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_beginCurrentPage)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_beginPage)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*get_complete)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_completeCount)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_completeCurrentPage)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_completePage)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*get_inProgress)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_inProgressCount)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_inProgressCurrentPage)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*get_inProgressPage)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*get_list)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component10)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component11)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component12)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component13)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_kotlin_collections_List (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component5)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component6)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component7)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component8)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_KInt (*component9)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz, libkn_kref_kotlin_collections_List list, libkn_kref_kotlin_collections_List begin, libkn_kref_kotlin_collections_List inProgress, libkn_kref_kotlin_collections_List complete, libkn_KInt beginCount, libkn_KInt inProgressCount, libkn_KInt completeCount, libkn_KInt beginPage, libkn_KInt beginCurrentPage, libkn_KInt inProgressPage, libkn_KInt inProgressCurrentPage, libkn_KInt completePage, libkn_KInt completeCurrentPage);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_DayOrderDataDto thiz);
                  } DayOrderDataDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto (*WorkOrderColorConfigDto)(libkn_kref_kotlin_collections_Map riskTitle);
                    libkn_kref_kotlin_collections_Map (*get_riskTitle)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto thiz);
                    libkn_kref_kotlin_collections_Map (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto thiz, libkn_kref_kotlin_collections_Map riskTitle);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto thiz);
                  } WorkOrderColorConfigDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto (*UnfinishedJobDateDto)(const char* jobDate);
                    const char* (*get_jobDate)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto thiz, const char* jobDate);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_UnfinishedJobDateDto thiz);
                  } UnfinishedJobDateDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto (*WorkOrderDayCountDto)(const char* date, libkn_KInt count, libkn_KInt unfinish, libkn_KInt overdue);
                    libkn_KInt (*get_count)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    const char* (*get_date)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    libkn_KInt (*get_overdue)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    libkn_KInt (*get_unfinish)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    libkn_KInt (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    libkn_KInt (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz, const char* date, libkn_KInt count, libkn_KInt unfinish, libkn_KInt overdue);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDayCountDto thiz);
                  } WorkOrderDayCountDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto (*WorkOrderDto)(libkn_KLong id, libkn_kref_kotlin_Long jobId, libkn_kref_kotlin_Long jobType, const char* jobDate, const char* jobStartTime, const char* jobEndTime, libkn_kref_kotlin_Int status, const char* addr, libkn_kref_kotlin_Long customerId, const char* customerCode, const char* customerName, const char* nameZh, const char* contactName, const char* contactMobile, libkn_kref_kotlinx_serialization_json_JsonElement customerType, const char* customerTypeText, const char* mobile, const char* tel, libkn_kref_kotlinx_serialization_json_JsonElement lat, libkn_kref_kotlinx_serialization_json_JsonElement lng, libkn_kref_kotlin_Long serviceType, const char* serviceTypeName, const char* serviceTypeAliasName, const char* riskTitle, const char* levelTitle, const char* riskLevel, const char* dataType, libkn_kref_kotlin_Int needSignIn, libkn_kref_kotlinx_serialization_json_JsonElement jobProgress, libkn_kref_kotlin_collections_List displayTags, const char* remarks, libkn_kref_kotlinx_serialization_json_JsonElement firstJobFlag);
                    const char* (*get_addr)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_contactMobile)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_contactName)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_customerCode)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*get_customerId)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_customerName)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_customerType)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_customerTypeText)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_dataType)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_collections_List (*get_displayTags)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_firstJobFlag)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_KLong (*get_id)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_jobDate)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_jobEndTime)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*get_jobId)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_jobProgress)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_jobStartTime)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*get_jobType)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_lat)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_levelTitle)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*get_lng)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_mobile)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_nameZh)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Int (*get_needSignIn)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_remarks)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_riskLevel)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_riskTitle)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*get_serviceType)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_serviceTypeAliasName)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_serviceTypeName)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Int (*get_status)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*get_tel)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_KLong (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component10)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component11)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component12)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component13)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component14)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component15)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component16)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component17)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component18)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component19)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component20)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*component21)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component22)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component23)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component24)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component25)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component26)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component27)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Int (*component28)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component29)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*component3)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_collections_List (*component30)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component31)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlinx_serialization_json_JsonElement (*component32)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component4)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component5)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component6)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Int (*component7)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*component8)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_kotlin_Long (*component9)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz, libkn_KLong id, libkn_kref_kotlin_Long jobId, libkn_kref_kotlin_Long jobType, const char* jobDate, const char* jobStartTime, const char* jobEndTime, libkn_kref_kotlin_Int status, const char* addr, libkn_kref_kotlin_Long customerId, const char* customerCode, const char* customerName, const char* nameZh, const char* contactName, const char* contactMobile, libkn_kref_kotlinx_serialization_json_JsonElement customerType, const char* customerTypeText, const char* mobile, const char* tel, libkn_kref_kotlinx_serialization_json_JsonElement lat, libkn_kref_kotlinx_serialization_json_JsonElement lng, libkn_kref_kotlin_Long serviceType, const char* serviceTypeName, const char* serviceTypeAliasName, const char* riskTitle, const char* levelTitle, const char* riskLevel, const char* dataType, libkn_kref_kotlin_Int needSignIn, libkn_kref_kotlinx_serialization_json_JsonElement jobProgress, libkn_kref_kotlin_collections_List displayTags, const char* remarks, libkn_kref_kotlinx_serialization_json_JsonElement firstJobFlag);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto thiz);
                  } WorkOrderDto;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer (*_instance)();
                      libkn_kref_kotlinx_serialization_descriptors_SerialDescriptor (*get_descriptor)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer thiz);
                      libkn_kref_kotlin_Array (*childSerializers)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer thiz);
                      libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto (*deserialize)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Decoder decoder);
                      void (*serialize)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer thiz, libkn_kref_kotlinx_serialization_encoding_Encoder encoder, libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto value);
                    } $serializer;
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_Companion (*_instance)();
                      libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto (*DisplayTagDto)(const char* key, const char* text);
                    const char* (*get_key)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz);
                    const char* (*get_text)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz);
                    libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto (*copy)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz, const char* key, const char* text);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_dto_DisplayTagDto thiz);
                  } DisplayTagDto;
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DayOrderDataDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_DisplayTagDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_InitInfoDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginRequestDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_LoginResponseDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRuleDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_PasswordRulesDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UnfinishedJobDateDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_UserDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderColorConfigDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDayCountDto_$serializer$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto$stableprop_getter___)();
                  libkn_KInt (*com_example_kmpoh_data_model_dto_WorkOrderDto_$serializer$stableprop_getter___)();
                } dto;
                struct {
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity_Companion (*_instance)();
                      libkn_KInt (*get_DEFAULT_MAX_LENGTH)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity_Companion thiz);
                      libkn_KInt (*get_DEFAULT_MIN_LENGTH)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity_Companion thiz);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity (*PasswordRulesEntity)(libkn_KInt minLength, libkn_KInt maxLength, libkn_KInt strengthLevel, const char* regex, const char* description, libkn_kref_kotlin_collections_List rules);
                    const char* (*get_description)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*get_maxInputLength)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*get_maxLength)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*get_minLength)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    const char* (*get_regex)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_kref_kotlin_collections_List (*get_rules)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*get_strengthLevel)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_KInt (*component3)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    const char* (*component4)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    const char* (*component5)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_kref_kotlin_collections_List (*component6)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz, libkn_KInt minLength, libkn_KInt maxLength, libkn_KInt strengthLevel, const char* regex, const char* description, libkn_kref_kotlin_collections_List rules);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity thiz);
                  } PasswordRulesEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity (*PasswordRuleEntity)(const char* regex, const char* message);
                    const char* (*get_message)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz);
                    const char* (*get_regex)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz, const char* regex, const char* message);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_PasswordRuleEntity thiz);
                  } PasswordRuleEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_UserEntity (*UserEntity)(libkn_KLong id, libkn_KInt userId, const char* name);
                    libkn_KLong (*get_id)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    const char* (*get_name)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    libkn_KInt (*get_userId)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    libkn_KLong (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    const char* (*component3)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_UserEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz, libkn_KLong id, libkn_KInt userId, const char* name);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_UserEntity thiz);
                  } UserEntity;
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion (*_instance)();
                      libkn_KInt (*get_JOB_TYPE_REPAIR)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_JOB_TYPE_REVISIT)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_JOB_TYPE_SURVEY)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_JOB_TYPE_UNKNOWN)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_STATUS_DONE)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_STATUS_RUNNING)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_STATUS_UNKNOWN)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_KInt (*get_STATUS_WAITING)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz);
                      libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity (*fromDto)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity_Companion thiz, libkn_kref_com_example_kmpoh_data_model_dto_WorkOrderDto dto, libkn_kref_kotlin_Int statusOverride, libkn_KLong cachedAtMillis);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity (*WorkOrderEntity)(libkn_KLong id, const char* address, const char* customerName, libkn_KLong customerId, const char* jobDate, const char* startTime, const char* endTime, libkn_KInt jobType, libkn_KInt status, libkn_KInt serviceType, const char* serviceTypeName, const char* riskTitle, const char* levelTitle, const char* customerCode, const char* contactName, const char* contactMobile, const char* mobile, const char* telephone, libkn_KDouble latitude, libkn_KDouble longitude, const char* remarks, libkn_KLong cachedAtMillis, const char* serviceTypeAliasName, libkn_kref_kotlin_collections_List displayTags, const char* dataType, libkn_KBoolean needSignIn, libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity jobProgress);
                    const char* (*get_address)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KLong (*get_cachedAtMillis)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_contactMobile)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_contactName)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_customerCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KLong (*get_customerId)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_customerName)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_dataType)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_kref_kotlin_collections_List (*get_displayTags)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_endTime)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KLong (*get_id)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_jobDate)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity (*get_jobProgress)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KInt (*get_jobType)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KDouble (*get_latitude)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_levelTitle)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KDouble (*get_longitude)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_mobile)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KBoolean (*get_needSignIn)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_remarks)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KBoolean (*get_requiresSignIn)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_riskTitle)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KInt (*get_serviceType)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_serviceTypeAliasName)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_serviceTypeName)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_startTime)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KInt (*get_status)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*get_telephone)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KLong (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KInt (*component10)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component11)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component12)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component13)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component14)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component15)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component16)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component17)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component18)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KDouble (*component19)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KDouble (*component20)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component21)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KLong (*component22)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component23)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_kref_kotlin_collections_List (*component24)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component25)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KBoolean (*component26)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity (*component27)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component3)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KLong (*component4)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component5)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component6)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*component7)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KInt (*component8)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_KInt (*component9)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz, libkn_KLong id, const char* address, const char* customerName, libkn_KLong customerId, const char* jobDate, const char* startTime, const char* endTime, libkn_KInt jobType, libkn_KInt status, libkn_KInt serviceType, const char* serviceTypeName, const char* riskTitle, const char* levelTitle, const char* customerCode, const char* contactName, const char* contactMobile, const char* mobile, const char* telephone, libkn_KDouble latitude, libkn_KDouble longitude, const char* remarks, libkn_KLong cachedAtMillis, const char* serviceTypeAliasName, libkn_kref_kotlin_collections_List displayTags, const char* dataType, libkn_KBoolean needSignIn, libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity jobProgress);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderEntity thiz);
                  } WorkOrderEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity (*WorkOrderProgressEntity)(libkn_KBoolean signedIn, libkn_KBoolean customerSigned, libkn_KBoolean signedOff, libkn_KBoolean reportReady, libkn_KBoolean completed);
                    libkn_KBoolean (*get_completed)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*get_customerSigned)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*get_reportReady)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*get_signedIn)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*get_signedOff)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*component3)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*component4)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_KBoolean (*component5)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz, libkn_KBoolean signedIn, libkn_KBoolean customerSigned, libkn_KBoolean signedOff, libkn_KBoolean reportReady, libkn_KBoolean completed);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderProgressEntity thiz);
                  } WorkOrderProgressEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity (*WorkOrderDisplayTagEntity)(const char* key, const char* text);
                    const char* (*get_key)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz);
                    const char* (*get_text)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz, const char* key, const char* text);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity thiz);
                  } WorkOrderDisplayTagEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity (*WorkOrderPageEntity)(libkn_KInt currentPage, libkn_KInt totalPage);
                    libkn_KInt (*get_currentPage)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz);
                    libkn_KInt (*get_totalPage)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz);
                    libkn_KInt (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz, libkn_KInt currentPage, libkn_KInt totalPage);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderPageEntity thiz);
                  } WorkOrderPageEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity (*WorkOrderDayOrdersEntity)(libkn_kref_kotlin_collections_List orders, libkn_kref_kotlin_collections_Map paging);
                    libkn_kref_kotlin_collections_List (*get_orders)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz);
                    libkn_kref_kotlin_collections_Map (*get_paging)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz);
                    libkn_kref_kotlin_collections_List (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz);
                    libkn_kref_kotlin_collections_Map (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz, libkn_kref_kotlin_collections_List orders, libkn_kref_kotlin_collections_Map paging);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity thiz);
                  } WorkOrderDayOrdersEntity;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity (*WorkOrderDayCountEntity)(const char* date, libkn_KInt count, libkn_KInt unfinished, libkn_KInt overdue);
                    libkn_KInt (*get_count)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    const char* (*get_date)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KBoolean (*get_hasFinished)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KBoolean (*get_hasOverdue)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KBoolean (*get_hasUnfinished)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KInt (*get_overdue)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KInt (*get_unfinished)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KInt (*component3)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_KInt (*component4)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity (*copy)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz, const char* date, libkn_KInt count, libkn_KInt unfinished, libkn_KInt overdue);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity thiz);
                  } WorkOrderDayCountEntity;
                  libkn_KInt (*com_example_kmpoh_data_model_entity_PasswordRuleEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_PasswordRulesEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_UserEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderPageEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderProgressEntity$stableprop_getter)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_PasswordRuleEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_PasswordRulesEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_UserEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderPageEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderProgressEntity$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_PasswordRuleEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_PasswordRulesEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_UserEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDayCountEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDayOrdersEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderDisplayTagEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderPageEntity$stableprop_getter__)();
                  libkn_KInt (*com_example_kmpoh_data_model_entity_WorkOrderProgressEntity$stableprop_getter__)();
                } entity;
                struct {
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_mapper_WorkOrderListKeys (*_instance)();
                    const char* (*get_ALL)(libkn_kref_com_example_kmpoh_data_model_mapper_WorkOrderListKeys thiz);
                    const char* (*get_BEGIN)(libkn_kref_com_example_kmpoh_data_model_mapper_WorkOrderListKeys thiz);
                    const char* (*get_COMPLETE)(libkn_kref_com_example_kmpoh_data_model_mapper_WorkOrderListKeys thiz);
                    const char* (*get_IN_PROGRESS)(libkn_kref_com_example_kmpoh_data_model_mapper_WorkOrderListKeys thiz);
                  } WorkOrderListKeys;
                  libkn_KInt (*com_example_kmpoh_data_model_mapper_WorkOrderListKeys$stableprop_getter)();
                  const char* (*resolveAccessToken)(const char* token, const char* accessToken);
                  const char* (*resolveRefreshToken)(const char* refreshToken, const char* accessToken);
                  libkn_KInt (*com_example_kmpoh_data_model_mapper_WorkOrderListKeys$stableprop_getter_)();
                  libkn_KInt (*com_example_kmpoh_data_model_mapper_WorkOrderListKeys$stableprop_getter__)();
                } mapper;
                struct {
                  struct {
                    struct {
                      libkn_KType* (*_type)(void);
                      libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel_Companion (*_instance)();
                      libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel (*fromEntity)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel_Companion thiz, libkn_kref_com_example_kmpoh_data_model_entity_UserEntity entity);
                    } Companion;
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel (*UserUiModel)(libkn_KLong id, const char* displayName, const char* maskedPhone, const char* avatarUrl, const char* role, const char* email);
                    const char* (*get_avatarUrl)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*get_displayName)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*get_email)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    libkn_KLong (*get_id)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*get_maskedPhone)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*get_role)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    libkn_KLong (*component1)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*component2)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*component3)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*component4)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*component5)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*component6)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel (*copy)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz, libkn_KLong id, const char* displayName, const char* maskedPhone, const char* avatarUrl, const char* role, const char* email);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_data_model_ui_UserUiModel thiz);
                  } UserUiModel;
                  libkn_KInt (*com_example_kmpoh_data_model_ui_UserUiModel$stableprop_getter)();
                } ui;
              } model;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                } LoginRepository;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_data_repository_NetworkLoginRepository (*NetworkLoginRepository)(libkn_kref_com_example_kmpoh_network_ApiGateway gateway, libkn_kref_com_example_kmpoh_network_AuthSessionManager session, libkn_kref_com_example_kmpoh_storage_KeyValueStore store);
                } NetworkLoginRepository;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_data_repository_AppGraph (*_instance)();
                  libkn_kref_com_example_kmpoh_network_ApiGateway (*get_gateway)(libkn_kref_com_example_kmpoh_data_repository_AppGraph thiz);
                  libkn_kref_com_example_kmpoh_data_repository_NetworkLoginRepository (*get_loginRepository)(libkn_kref_com_example_kmpoh_data_repository_AppGraph thiz);
                  libkn_kref_com_example_kmpoh_data_repository_ProfileRepository (*get_profileRepository)(libkn_kref_com_example_kmpoh_data_repository_AppGraph thiz);
                  libkn_kref_com_example_kmpoh_network_AuthSessionManager (*get_session)(libkn_kref_com_example_kmpoh_data_repository_AppGraph thiz);
                  libkn_kref_com_example_kmpoh_storage_KeyValueStore (*get_store)(libkn_kref_com_example_kmpoh_data_repository_AppGraph thiz);
                  libkn_kref_com_example_kmpoh_data_repository_WorkOrderListRepository (*get_workOrderListRepository)(libkn_kref_com_example_kmpoh_data_repository_AppGraph thiz);
                } AppGraph;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_data_repository_ProfileRepository (*ProfileRepository)(libkn_kref_com_example_kmpoh_network_ApiGateway gateway, libkn_kref_com_example_kmpoh_network_AuthSessionManager session, libkn_kref_com_example_kmpoh_storage_KeyValueStore store);
                } ProfileRepository;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_data_repository_WorkOrderListRepository (*WorkOrderListRepository)(libkn_kref_com_example_kmpoh_network_ApiGateway gateway);
                  libkn_kref_kotlin_Int (*riskColor)(libkn_kref_com_example_kmpoh_data_repository_WorkOrderListRepository thiz, const char* label);
                } WorkOrderListRepository;
                libkn_KInt (*com_example_kmpoh_data_repository_AppGraph$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_data_repository_NetworkLoginRepository$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_data_repository_ProfileRepository$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_data_repository_WorkOrderListRepository$stableprop_getter)();
                libkn_kref_com_example_kmpoh_data_repository_LoginRepository (*createLoginRepository)();
                libkn_kref_com_example_kmpoh_data_repository_ProfileRepository (*createProfileRepository)();
                libkn_kref_com_example_kmpoh_data_repository_WorkOrderListRepository (*createWorkOrderListRepository)();
                libkn_KInt (*com_example_kmpoh_data_repository_AppGraph$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_data_repository_NetworkLoginRepository$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_data_repository_ProfileRepository$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_data_repository_WorkOrderListRepository$stableprop_getter_)();
                libkn_KInt (*get_DAY_ORDER_PAGE_SIZE)();
                libkn_KInt (*get_FIRST_PAGE)();
                libkn_KInt (*com_example_kmpoh_data_repository_AppGraph$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_data_repository_NetworkLoginRepository$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_data_repository_ProfileRepository$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_data_repository_WorkOrderListRepository$stableprop_getter__)();
              } repository;
            } data;
            struct {
              struct {
                struct {
                  libkn_kref_com_example_kmpoh_logger_LogLevel (*get)(); /* enum entry for DEBUG. */
                } DEBUG;
                struct {
                  libkn_kref_com_example_kmpoh_logger_LogLevel (*get)(); /* enum entry for INFO. */
                } INFO;
                struct {
                  libkn_kref_com_example_kmpoh_logger_LogLevel (*get)(); /* enum entry for WARN. */
                } WARN;
                struct {
                  libkn_kref_com_example_kmpoh_logger_LogLevel (*get)(); /* enum entry for ERROR. */
                } ERROR;
                libkn_KType* (*_type)(void);
              } LogLevel;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_logger_Logger (*_instance)();
                libkn_KBoolean (*get_isTestEnvironment)(libkn_kref_com_example_kmpoh_logger_Logger thiz);
                void (*debug)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* tag, const char* message);
                void (*debug_)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* message);
                void (*debugJson)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* tag, const char* header, const char* json);
                void (*debugSingleLine)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* tag, const char* message);
                void (*error)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* tag, const char* message);
                void (*error_)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* message);
                void (*info)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* tag, const char* message);
                void (*info_)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* message);
                const char* (*sanitize)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* message);
                void (*warn)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* tag, const char* message);
                void (*warn_)(libkn_kref_com_example_kmpoh_logger_Logger thiz, const char* message);
              } Logger;
              const char* (*get_BUSINESS_LOG_TAG)();
              const char* (*get_DEBUG_LOG_TAG)();
              const char* (*get_LOG_MASK)();
              const char* (*get_NETWORK_LOG_TAG)();
              libkn_KInt (*com_example_kmpoh_logger_Logger$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_logger_Logger$stableprop_getter_)();
              void (*platformLogLine)(libkn_kref_com_example_kmpoh_logger_LogLevel level, const char* tag, const char* message);
            } logger;
            struct {
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_bridge_ConnectTimeoutException (*ConnectTimeoutException)(const char* message);
                } ConnectTimeoutException;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_bridge_SocketTimeoutException (*SocketTimeoutException)(const char* message);
                } SocketTimeoutException;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_bridge_UnknownHostException (*UnknownHostException)(const char* message);
                } UnknownHostException;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_bridge_ConnectException (*ConnectException)(const char* message);
                } ConnectException;
                libkn_KInt (*com_example_kmpoh_network_bridge_ConnectException$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_network_bridge_ConnectTimeoutException$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_network_bridge_SocketTimeoutException$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_network_bridge_UnknownHostException$stableprop_getter)();
                void (*ohosHttpBridgeRespond)(void* requestId, void* responseJson);
                void (*ohosHttpTransportInit)(void* postFn);
                libkn_KInt (*com_example_kmpoh_network_bridge_ConnectException$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_network_bridge_ConnectTimeoutException$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_network_bridge_SocketTimeoutException$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_network_bridge_UnknownHostException$stableprop_getter_)();
              } bridge;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_signature_ApiSignatureEngine (*_instance)();
                  const char* (*canonicalParamsOf)(libkn_kref_com_example_kmpoh_network_signature_ApiSignatureEngine thiz, const char* bodyText);
                  libkn_KBoolean (*isTimestampValid)(libkn_kref_com_example_kmpoh_network_signature_ApiSignatureEngine thiz, const char* timestamp, libkn_KLong nowEpochSeconds, libkn_KLong maxClockSkewSeconds);
                  const char* (*sign)(libkn_kref_com_example_kmpoh_network_signature_ApiSignatureEngine thiz, const char* apiSecret, const char* timestamp, const char* nonce, const char* paramsString);
                  libkn_KBoolean (*signaturesMatch)(libkn_kref_com_example_kmpoh_network_signature_ApiSignatureEngine thiz, const char* expected, const char* actual);
                } ApiSignatureEngine;
                struct {
                  struct {
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode (*get)(); /* enum entry for Off. */
                  } Off;
                  struct {
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode (*get)(); /* enum entry for RequestOnly. */
                  } RequestOnly;
                  struct {
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode (*get)(); /* enum entry for Mutual. */
                  } Mutual;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode_Companion (*_instance)();
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode (*fromConfigValue)(libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode_Companion thiz, const char* value);
                  } Companion;
                  libkn_KType* (*_type)(void);
                } ApiSignatureMode;
                struct {
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy_Companion (*_instance)();
                    libkn_kref_kotlin_collections_Set (*get_unsignedPaths)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy_Companion thiz);
                    libkn_kref_kotlin_collections_Set (*get_unverifiedResponsePaths)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy_Companion thiz);
                    libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy (*fromConfig)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy_Companion thiz);
                  } Companion;
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy (*ApiSignaturePolicy)(libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode mode, const char* apiSecret, libkn_KLong maxClockSkewSeconds);
                  const char* (*get_apiSecret)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz);
                  libkn_KBoolean (*get_isEnabled)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz);
                  libkn_KLong (*get_maxClockSkewSeconds)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz);
                  libkn_kref_com_example_kmpoh_network_signature_ApiSignatureMode (*get_mode)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz);
                  libkn_KBoolean (*get_verifiesResponses)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz);
                  libkn_KBoolean (*isUnsignedPath)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz, const char* path);
                  libkn_KBoolean (*isUnverifiedResponsePath)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy thiz, const char* path);
                } ApiSignaturePolicy;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_signature_SignatureVerificationException (*SignatureVerificationException)(const char* message);
                } SignatureVerificationException;
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignatureEngine$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignaturePolicy$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_network_signature_SignatureVerificationException$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignatureEngine$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignaturePolicy$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_network_signature_SignatureVerificationException$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignatureEngine$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignaturePolicy$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_network_signature_SignatureVerificationException$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignatureEngine$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignaturePolicy$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_network_signature_SignatureVerificationException$stableprop_getter___)();
                const char* (*generateNonce)(libkn_KInt length);
                void (*verifyResponseSignature)(libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy policy, libkn_kref_io_ktor_http_Headers headers, const char* rawBody, libkn_KLong nowEpochSeconds);
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignatureEngine$stableprop_getter____)();
                libkn_KInt (*com_example_kmpoh_network_signature_ApiSignaturePolicy$stableprop_getter____)();
                libkn_KInt (*com_example_kmpoh_network_signature_SignatureVerificationException$stableprop_getter____)();
                libkn_KLong (*currentEpochSeconds)();
              } signature;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_ApiGateway (*ApiGateway)(libkn_kref_io_ktor_client_HttpClient http, libkn_kref_com_example_kmpoh_network_AuthSessionManager session, const char* deviceId, const char* appVersion, const char* language, libkn_kref_com_example_kmpoh_network_signature_ApiSignaturePolicy signature);
                libkn_kref_com_example_kmpoh_network_AuthSessionManager (*get_session)(libkn_kref_com_example_kmpoh_network_ApiGateway thiz);
              } ApiGateway;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_BusinessApiException (*BusinessApiException)(libkn_KInt businessCode, const char* businessMessage);
                libkn_KInt (*get_businessCode)(libkn_kref_com_example_kmpoh_network_BusinessApiException thiz);
                const char* (*get_businessMessage)(libkn_kref_com_example_kmpoh_network_BusinessApiException thiz);
              } BusinessApiException;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired (*LoginExpired)(const char* message);
                  const char* (*get_message)(libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired thiz);
                  const char* (*component1)(libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired thiz);
                  libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired (*copy)(libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired thiz, const char* message);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_network_AuthSessionEvent_LoginExpired thiz);
                } LoginExpired;
                libkn_KType* (*_type)(void);
              } AuthSessionEvent;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_AuthSessionManager (*AuthSessionManager)(libkn_kref_com_example_kmpoh_storage_KeyValueStore store);
                libkn_kref_kotlinx_coroutines_flow_SharedFlow (*get_events)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz);
                const char* (*accessToken)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz);
                void (*clearTokens)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz);
                void (*notifyLoginExpired)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz, const char* message);
                const char* (*refreshToken)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz);
                void (*saveTokens)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz, const char* accessToken, const char* refreshToken);
                void (*saveUserName)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz, const char* name);
                const char* (*userName)(libkn_kref_com_example_kmpoh_network_AuthSessionManager thiz);
              } AuthSessionManager;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_MultipartTextContent (*MultipartTextContent)(libkn_kref_kotlin_collections_Map fields);
                libkn_kref_kotlin_Long (*get_contentLength)(libkn_kref_com_example_kmpoh_network_MultipartTextContent thiz);
                libkn_kref_io_ktor_http_ContentType (*get_contentType)(libkn_kref_com_example_kmpoh_network_MultipartTextContent thiz);
                libkn_kref_kotlin_collections_Map (*get_fields)(libkn_kref_com_example_kmpoh_network_MultipartTextContent thiz);
              } MultipartTextContent;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_NetworkException_Http (*Http)(libkn_KInt statusCode, const char* statusMessage);
                  libkn_KInt (*get_statusCode)(libkn_kref_com_example_kmpoh_network_NetworkException_Http thiz);
                  const char* (*get_statusMessage)(libkn_kref_com_example_kmpoh_network_NetworkException_Http thiz);
                } Http;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_NetworkException_Timeout (*Timeout)(libkn_kref_kotlin_Throwable cause);
                } Timeout;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_NetworkException_Unavailable (*Unavailable)(libkn_kref_kotlin_Throwable cause);
                } Unavailable;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_NetworkException_Transport (*Transport)(libkn_kref_kotlin_Throwable cause);
                } Transport;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_NetworkException_Parsing (*Parsing)(libkn_kref_kotlin_Throwable cause);
                } Parsing;
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_NetworkException (*NetworkException)(const char* message, libkn_kref_kotlin_Throwable cause);
              } NetworkException;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_NetworkMessages (*_instance)();
                const char* (*get_LOGIN_EXPIRED)(libkn_kref_com_example_kmpoh_network_NetworkMessages thiz);
                const char* (*get_LOGIN_FALLBACK)(libkn_kref_com_example_kmpoh_network_NetworkMessages thiz);
                const char* (*get_PARSING)(libkn_kref_com_example_kmpoh_network_NetworkMessages thiz);
                const char* (*get_TIMEOUT)(libkn_kref_com_example_kmpoh_network_NetworkMessages thiz);
                const char* (*get_TRANSPORT)(libkn_kref_com_example_kmpoh_network_NetworkMessages thiz);
                const char* (*get_UNAVAILABLE)(libkn_kref_com_example_kmpoh_network_NetworkMessages thiz);
              } NetworkMessages;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_network_NetworkRequestTracker_Companion (*_instance)();
                  libkn_kref_com_example_kmpoh_network_NetworkRequestTracker (*get_global)(libkn_kref_com_example_kmpoh_network_NetworkRequestTracker_Companion thiz);
                } Companion;
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_network_NetworkRequestTracker (*NetworkRequestTracker)();
                libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_activeRequests)(libkn_kref_com_example_kmpoh_network_NetworkRequestTracker thiz);
                void (*onRequestFinished)(libkn_kref_com_example_kmpoh_network_NetworkRequestTracker thiz);
                void (*onRequestStarted)(libkn_kref_com_example_kmpoh_network_NetworkRequestTracker thiz);
              } NetworkRequestTracker;
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter_)();
              libkn_kref_com_example_kmpoh_network_NetworkException (*mapTransportFailure)(libkn_kref_kotlin_Throwable failure);
              const char* (*get_APP_VERSION)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter__)();
              libkn_KBoolean (*isLoginExpired)(libkn_kref_kotlin_Throwable failure);
              libkn_kref_kotlinx_serialization_json_Json (*get_ApiJson)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter___)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter____)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter_____)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter______)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter______)();
              libkn_KLong (*get_NETWORK_TIMEOUT_MILLIS)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter_______)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter_______)();
              libkn_kref_io_ktor_client_HttpClient (*createApiClient)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter________)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter_________)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter__________)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter__________)();
              libkn_KInt (*get_LOG_BODY_MAX_CHARS)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter___________)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter___________)();
              const char* (*describeRequestParams)(const char* bodyText, libkn_kref_kotlin_Any body);
              const char* (*formatRequestLine)(const char* url, const char* params, const char* headers);
              const char* (*formatResponseLine)(const char* path, const char* status, const char* body);
              const char* (*maskSensitiveText)(const char* text);
              const char* (*truncateForLog)(const char* text, libkn_KInt maxChars);
              const char* (*get_HEADER_SHOW_GLOBAL_LOADING)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter____________)();
              libkn_KInt (*com_example_kmpoh_network_ApiGateway$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_ApiResponse_$serializer$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionEvent_LoginExpired$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_AuthSessionManager$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_BusinessApiException$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_MultipartTextContent$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Http$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Parsing$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Timeout$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Transport$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkException_Unavailable$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkMessages$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_NetworkRequestTracker$stableprop_getter_____________)();
              libkn_KInt (*com_example_kmpoh_network_RefreshTokenData_$serializer$stableprop_getter_____________)();
              libkn_kref_io_ktor_client_HttpClient (*createPlatformHttpClient)(libkn_kref_kotlin_Function1 block);
            } network;
            struct {
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_login_LoginViewModel (*LoginViewModel)(libkn_kref_com_example_kmpoh_data_repository_LoginRepository repository, libkn_kref_kotlinx_coroutines_CoroutineScope scope);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_loginEnabled)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_password)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_phone)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_toastMessage)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_uiState)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                  void (*onLoginClick)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                  void (*onPasswordChanged)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz, const char* value);
                  void (*onPhoneChanged)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz, const char* value);
                  void (*onToastShown)(libkn_kref_com_example_kmpoh_page_login_LoginViewModel thiz);
                } LoginViewModel;
                void (*LoginPage)(libkn_kref_kotlin_Function0 onLoginSuccess, libkn_kref_kotlin_Function1 onToastMessage);
                libkn_KInt (*com_example_kmpoh_page_login_LoginViewModel$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_login_LoginViewModel$stableprop_getter_)();
              } login;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_main_MainUiState (*MainUiState)(libkn_KBoolean requiresPasswordChange, libkn_KBoolean isCheckingPasswordStatus);
                  libkn_KBoolean (*get_isCheckingPasswordStatus)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz);
                  libkn_KBoolean (*get_requiresPasswordChange)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz);
                  libkn_KBoolean (*component1)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz);
                  libkn_KBoolean (*component2)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz);
                  libkn_kref_com_example_kmpoh_page_main_MainUiState (*copy)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz, libkn_KBoolean requiresPasswordChange, libkn_KBoolean isCheckingPasswordStatus);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_main_MainUiState thiz);
                } MainUiState;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_main_MainViewModel (*MainViewModel)(libkn_kref_com_example_kmpoh_data_repository_ProfileRepository profileRepository, libkn_kref_kotlinx_coroutines_CoroutineScope scope);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_state)(libkn_kref_com_example_kmpoh_page_main_MainViewModel thiz);
                  void (*refreshPasswordStatus)(libkn_kref_com_example_kmpoh_page_main_MainViewModel thiz);
                } MainViewModel;
                void (*MainPage)(libkn_kref_kotlin_Function0 onLoggedOut, libkn_kref_kotlin_Function0 onNavigateToChangePassword, libkn_kref_kotlin_Function1 onOpenWorkOrderPreview, libkn_kref_kotlin_Function1 onToastMessage);
                libkn_KInt (*com_example_kmpoh_page_main_MainUiState$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_main_MainViewModel$stableprop_getter)();
                void (*MainTabPlaceholder)(const char* moduleName, libkn_kref_androidx_compose_ui_Modifier modifier, libkn_kref_kotlin_Function0 action);
                libkn_KInt (*com_example_kmpoh_page_main_MainUiState$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_main_MainViewModel$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_main_MainUiState$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_main_MainViewModel$stableprop_getter__)();
              } main;
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_message_MessageViewModel (*MessageViewModel)();
                } MessageViewModel;
                void (*MessagePage)(libkn_kref_androidx_compose_ui_Modifier modifier, libkn_kref_com_example_kmpoh_page_message_MessageViewModel viewModel);
                libkn_KInt (*com_example_kmpoh_page_message_MessageViewModel$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_message_MessageViewModel$stableprop_getter_)();
              } message;
              struct {
                struct {
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Required (*_instance)();
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Required thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Required thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Required thiz);
                  } Required;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch (*_instance)();
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch thiz);
                  } ConfirmMismatch;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength (*MinLength)(libkn_KInt min);
                    libkn_KInt (*get_min)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength thiz);
                    libkn_KInt (*component1)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength thiz);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength (*copy)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength thiz, libkn_KInt min);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MinLength thiz);
                  } MinLength;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength (*MaxLength)(libkn_KInt max);
                    libkn_KInt (*get_max)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength thiz);
                    libkn_KInt (*component1)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength thiz);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength (*copy)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength thiz, libkn_KInt max);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength thiz);
                  } MaxLength;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed (*_instance)();
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed thiz);
                  } RulesLoadFailed;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Failed (*_instance)();
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Failed thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Failed thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Failed thiz);
                  } Failed;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success (*Success)(const char* message);
                    const char* (*get_message)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success thiz);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success (*copy)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success thiz, const char* message);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Success thiz);
                  } Success;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error (*Error)(const char* message);
                    const char* (*get_message)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error thiz);
                    libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error (*copy)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error thiz, const char* message);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast_Error thiz);
                  } Error;
                  libkn_KType* (*_type)(void);
                } ChangePasswordToast;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState (*ChangePasswordUiState)(const char* newPassword, const char* confirmPassword, libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity passwordRules, libkn_KBoolean isSubmitting, libkn_KBoolean passwordChanged, const char* requestErrorMessage, libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast toast);
                  libkn_KBoolean (*get_canSubmit)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*get_confirmPassword)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*get_isConfirmMismatch)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*get_isPasswordLengthInvalid)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*get_isSubmitting)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*get_newPassword)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*get_passwordChanged)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*get_passwordRuleDescription)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*get_passwordRuleError)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity (*get_passwordRules)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*get_requestErrorMessage)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*get_shouldShowConfirmMismatch)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast (*get_toast)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*component1)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*component2)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity (*component3)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*component4)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_KBoolean (*component5)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*component6)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast (*component7)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState (*copy)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz, const char* newPassword, const char* confirmPassword, libkn_kref_com_example_kmpoh_data_model_entity_PasswordRulesEntity passwordRules, libkn_KBoolean isSubmitting, libkn_KBoolean passwordChanged, const char* requestErrorMessage, libkn_kref_com_example_kmpoh_page_profile_ChangePasswordToast toast);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordUiState thiz);
                } ChangePasswordUiState;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel (*ChangePasswordViewModel)(libkn_kref_com_example_kmpoh_data_repository_ProfileRepository profileRepository, libkn_kref_kotlinx_coroutines_CoroutineScope scope);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_state)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel thiz);
                  void (*onConfirmPasswordChange)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel thiz, const char* value);
                  void (*onNewPasswordChange)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel thiz, const char* value);
                  void (*onPasswordChangedHandled)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel thiz);
                  void (*onToastShown)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel thiz);
                  void (*submit)(libkn_kref_com_example_kmpoh_page_profile_ChangePasswordViewModel thiz);
                } ChangePasswordViewModel;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem (*ProfileMenuItem)(const char* id, libkn_kref_org_jetbrains_compose_resources_StringResource titleRes, libkn_kref_org_jetbrains_compose_resources_StringResource subtitleRes, libkn_KLong bgColor, libkn_KLong iconTint, const char* icon, libkn_KBoolean showBadge, const char* subtitleArg);
                  libkn_KLong (*get_bgColor)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*get_icon)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_KLong (*get_iconTint)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*get_id)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_KBoolean (*get_showBadge)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*get_subtitleArg)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_kref_org_jetbrains_compose_resources_StringResource (*get_subtitleRes)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_kref_org_jetbrains_compose_resources_StringResource (*get_titleRes)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*component1)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_kref_org_jetbrains_compose_resources_StringResource (*component2)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_kref_org_jetbrains_compose_resources_StringResource (*component3)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_KLong (*component4)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_KLong (*component5)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*component6)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_KBoolean (*component7)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*component8)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem (*copy)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz, const char* id, libkn_kref_org_jetbrains_compose_resources_StringResource titleRes, libkn_kref_org_jetbrains_compose_resources_StringResource subtitleRes, libkn_KLong bgColor, libkn_KLong iconTint, const char* icon, libkn_KBoolean showBadge, const char* subtitleArg);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ProfileMenuItem thiz);
                } ProfileMenuItem;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_profile_ProfileUiState (*ProfileUiState)(libkn_KBoolean isLoggingOut, const char* avatarName, const char* displayName, libkn_kref_org_jetbrains_compose_resources_StringResource titleRes, const char* employeeId, libkn_KBoolean isVerified, libkn_kref_kotlin_collections_List systemSettings);
                  const char* (*get_avatarName)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  const char* (*get_displayName)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  const char* (*get_employeeId)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_KBoolean (*get_isLoggingOut)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_KBoolean (*get_isVerified)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_kref_kotlin_collections_List (*get_systemSettings)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_kref_org_jetbrains_compose_resources_StringResource (*get_titleRes)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_KBoolean (*component1)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  const char* (*component2)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  const char* (*component3)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_kref_org_jetbrains_compose_resources_StringResource (*component4)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  const char* (*component5)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_KBoolean (*component6)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_kref_kotlin_collections_List (*component7)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  libkn_kref_com_example_kmpoh_page_profile_ProfileUiState (*copy)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz, libkn_KBoolean isLoggingOut, const char* avatarName, const char* displayName, libkn_kref_org_jetbrains_compose_resources_StringResource titleRes, const char* employeeId, libkn_KBoolean isVerified, libkn_kref_kotlin_collections_List systemSettings);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ProfileUiState thiz);
                } ProfileUiState;
                struct {
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_profile_ProfileEffect_LoggedOut (*_instance)();
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_profile_ProfileEffect_LoggedOut thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_profile_ProfileEffect_LoggedOut thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_profile_ProfileEffect_LoggedOut thiz);
                  } LoggedOut;
                  libkn_KType* (*_type)(void);
                } ProfileEffect;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_profile_ProfileViewModel (*ProfileViewModel)(libkn_kref_com_example_kmpoh_data_repository_ProfileRepository profileRepository, libkn_kref_com_example_kmpoh_network_AuthSessionManager session, libkn_kref_kotlinx_coroutines_CoroutineScope scope);
                  libkn_kref_kotlinx_coroutines_flow_SharedFlow (*get_effect)(libkn_kref_com_example_kmpoh_page_profile_ProfileViewModel thiz);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_state)(libkn_kref_com_example_kmpoh_page_profile_ProfileViewModel thiz);
                  void (*onLogoutClick)(libkn_kref_com_example_kmpoh_page_profile_ProfileViewModel thiz);
                } ProfileViewModel;
                void (*ChangePasswordPage)(libkn_kref_kotlin_Function0 onBack, libkn_kref_kotlin_Function1 onToastMessage, libkn_kref_kotlin_Function0 onPasswordChangedSuccess);
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Error$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Failed$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MinLength$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Required$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Success$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordUiState$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordViewModel$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileEffect_LoggedOut$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileMenuItem$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileUiState$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileViewModel$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Error$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Failed$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MinLength$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Required$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Success$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordUiState$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordViewModel$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileEffect_LoggedOut$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileMenuItem$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileUiState$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileViewModel$stableprop_getter_)();
                void (*ProfilePage)(libkn_kref_kotlin_Function0 onLoggedOut, libkn_kref_kotlin_Function0 onNavigateToChangePassword, libkn_kref_androidx_compose_ui_Modifier modifier);
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Error$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Failed$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MinLength$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Required$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Success$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordUiState$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordViewModel$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileEffect_LoggedOut$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileMenuItem$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileUiState$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileViewModel$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_ConfirmMismatch$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Error$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Failed$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MaxLength$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_MinLength$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Required$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_RulesLoadFailed$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordToast_Success$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordUiState$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ChangePasswordViewModel$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileEffect_LoggedOut$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileMenuItem$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileUiState$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_profile_ProfileViewModel$stableprop_getter___)();
              } profile;
              struct {
                struct {
                  struct {
                    libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*get)(); /* enum entry for Waiting. */
                  } Waiting;
                  struct {
                    libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*get)(); /* enum entry for Running. */
                  } Running;
                  struct {
                    libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*get)(); /* enum entry for Done. */
                  } Done;
                  libkn_KType* (*_type)(void);
                  libkn_KInt (*get_color)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus thiz);
                  const char* (*get_label)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus thiz);
                  libkn_KInt (*get_softColor)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus thiz);
                } WorkOrderStatus;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrder (*WorkOrder)(const char* title, libkn_kref_kotlinx_datetime_LocalDate date, const char* timeRange, const char* address, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus status, libkn_kref_kotlin_collections_List tags, const char* riskLabel, libkn_KInt riskColor, libkn_KDouble latitude, libkn_KDouble longitude, libkn_KLong id, const char* levelTitle, const char* serviceTypeAliasName, const char* dataType, const char* customerName, const char* customerLevel, const char* customerLevelTitle, const char* phone, libkn_KBoolean requiresSignIn, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress progress);
                  const char* (*get_address)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_customerLevel)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_customerLevelTitle)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_customerName)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_dataType)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_kotlinx_datetime_LocalDate (*get_date)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KLong (*get_id)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KDouble (*get_latitude)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_levelTitle)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KDouble (*get_longitude)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_phone)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress (*get_progress)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KBoolean (*get_requiresSignIn)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KInt (*get_riskColor)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_riskLabel)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_serviceTypeAliasName)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*get_status)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_kotlin_collections_List (*get_tags)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_timeRange)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*get_title)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component1)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KDouble (*component10)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KLong (*component11)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component12)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component13)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component14)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component15)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component16)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component17)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component18)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KBoolean (*component19)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_kotlinx_datetime_LocalDate (*component2)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress (*component20)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component3)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component4)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*component5)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_kotlin_collections_List (*component6)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*component7)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KInt (*component8)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_KDouble (*component9)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrder (*copy)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz, const char* title, libkn_kref_kotlinx_datetime_LocalDate date, const char* timeRange, const char* address, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus status, libkn_kref_kotlin_collections_List tags, const char* riskLabel, libkn_KInt riskColor, libkn_KDouble latitude, libkn_KDouble longitude, libkn_KLong id, const char* levelTitle, const char* serviceTypeAliasName, const char* dataType, const char* customerName, const char* customerLevel, const char* customerLevelTitle, const char* phone, libkn_KBoolean requiresSignIn, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress progress);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrder thiz);
                } WorkOrder;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag (*WorkOrderTag)(const char* label, libkn_KInt backgroundColor, libkn_KInt textColor);
                  libkn_KInt (*get_backgroundColor)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  const char* (*get_label)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  libkn_KInt (*get_textColor)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  const char* (*component1)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  libkn_KInt (*component2)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  libkn_KInt (*component3)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag (*copy)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz, const char* label, libkn_KInt backgroundColor, libkn_KInt textColor);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderTag thiz);
                } WorkOrderTag;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress (*WorkOrderProgress)(libkn_KBoolean signedIn, libkn_KBoolean customerSigned, libkn_KBoolean signedOff, libkn_KBoolean reportReady, libkn_KBoolean completed);
                  libkn_KBoolean (*get_completed)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*get_customerSigned)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*get_reportReady)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*get_signedIn)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*get_signedOff)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*component1)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*component2)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*component3)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*component4)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_KBoolean (*component5)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress (*copy)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz, libkn_KBoolean signedIn, libkn_KBoolean customerSigned, libkn_KBoolean signedOff, libkn_KBoolean reportReady, libkn_KBoolean completed);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderProgress thiz);
                } WorkOrderProgress;
                struct {
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed (*_instance)();
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed thiz);
                  } LoadFailed;
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage (*ServerMessage)(const char* message);
                    const char* (*get_message)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage thiz);
                    const char* (*component1)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage thiz);
                    libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage (*copy)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage thiz, const char* message);
                    libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage thiz, libkn_kref_kotlin_Any other);
                    libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage thiz);
                    const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage thiz);
                  } ServerMessage;
                  libkn_KType* (*_type)(void);
                } WorkOrderListToast;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState (*WorkOrderCalendarMarkerState)(libkn_KBoolean hasUnfinished, libkn_KBoolean hasFinished, libkn_KBoolean hasOverdue);
                  libkn_KBoolean (*get_hasFinished)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  libkn_KBoolean (*get_hasOverdue)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  libkn_KBoolean (*get_hasUnfinished)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  libkn_KBoolean (*component1)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  libkn_KBoolean (*component2)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  libkn_KBoolean (*component3)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState (*copy)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz, libkn_KBoolean hasUnfinished, libkn_KBoolean hasFinished, libkn_KBoolean hasOverdue);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState thiz);
                } WorkOrderCalendarMarkerState;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState (*WorkOrderListState)(libkn_kref_kotlinx_datetime_LocalDate selectedDate, libkn_kref_kotlinx_datetime_YearMonth displayedMonth, libkn_KBoolean expanded, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus selectedStatus, libkn_kref_com_example_kmpoh_utils_UiState uiState, libkn_kref_kotlin_collections_List orders, libkn_kref_kotlin_collections_List visibleOrders, libkn_kref_kotlin_collections_Map calendarMarkers, libkn_KInt monthOrderCount, libkn_KBoolean isRefreshing, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast toast, libkn_KBoolean isLoadingMore, libkn_KBoolean canLoadMore, libkn_KBoolean showNoMore);
                  libkn_kref_kotlin_collections_Map (*get_calendarMarkers)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*get_canLoadMore)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlinx_datetime_YearMonth (*get_displayedMonth)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*get_expanded)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*get_isLoadingMore)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*get_isRefreshing)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KInt (*get_monthOrderCount)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlin_collections_List (*get_orders)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlinx_datetime_LocalDate (*get_selectedDate)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*get_selectedStatus)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*get_showNoMore)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast (*get_toast)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_utils_UiState (*get_uiState)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlin_collections_List (*get_visibleOrders)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlinx_datetime_LocalDate (*component1)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*component10)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast (*component11)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*component12)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*component13)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*component14)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlinx_datetime_YearMonth (*component2)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KBoolean (*component3)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus (*component4)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_utils_UiState (*component5)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlin_collections_List (*component6)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlin_collections_List (*component7)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_kotlin_collections_Map (*component8)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_KInt (*component9)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState (*copy)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz, libkn_kref_kotlinx_datetime_LocalDate selectedDate, libkn_kref_kotlinx_datetime_YearMonth displayedMonth, libkn_KBoolean expanded, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus selectedStatus, libkn_kref_com_example_kmpoh_utils_UiState uiState, libkn_kref_kotlin_collections_List orders, libkn_kref_kotlin_collections_List visibleOrders, libkn_kref_kotlin_collections_Map calendarMarkers, libkn_KInt monthOrderCount, libkn_KBoolean isRefreshing, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListToast toast, libkn_KBoolean isLoadingMore, libkn_KBoolean canLoadMore, libkn_KBoolean showNoMore);
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderListState thiz);
                } WorkOrderListState;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel (*WorkOrderViewModel)(libkn_kref_com_example_kmpoh_data_repository_WorkOrderListRepository repository, libkn_kref_kotlinx_coroutines_CoroutineScope scope);
                  libkn_kref_kotlinx_coroutines_flow_StateFlow (*get_state)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*loadMore)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*onToastShown)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*refresh)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*refreshAfterReturn)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*retry)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*selectDate)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz, libkn_kref_kotlinx_datetime_LocalDate date);
                  void (*selectMonth)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz, libkn_kref_kotlinx_datetime_YearMonth month);
                  void (*selectStatus)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz, libkn_kref_com_example_kmpoh_page_workorder_WorkOrderStatus status);
                  void (*selectToday)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                  void (*shiftMonth)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz, libkn_KInt delta);
                  void (*shiftWeek)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz, libkn_KInt delta);
                  void (*toggleExpanded)(libkn_kref_com_example_kmpoh_page_workorder_WorkOrderViewModel thiz);
                } WorkOrderViewModel;
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrder$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListState$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderProgress$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderTag$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderViewModel$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrder$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListState$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderProgress$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderTag$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderViewModel$stableprop_getter_)();
                void (*WorkOrderPage)(libkn_kref_androidx_compose_ui_Modifier modifier, libkn_kref_kotlin_Function1 onOpenPreview, libkn_kref_kotlin_Function1 onToastMessage);
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrder$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListState$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderProgress$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderTag$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderViewModel$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrder$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderCalendarMarkerState$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListState$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_LoadFailed$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderListToast_ServerMessage$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderProgress$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderTag$stableprop_getter___)();
                libkn_KInt (*com_example_kmpoh_page_workorder_WorkOrderViewModel$stableprop_getter___)();
              } workorder;
            } page;
            struct {
              struct {
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_router_AppDestination_Login (*_instance)();
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_router_AppDestination_Login thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_router_AppDestination_Login thiz);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_router_AppDestination_Login thiz, libkn_kref_kotlin_Array typeParamsSerializers);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer_)(libkn_kref_com_example_kmpoh_router_AppDestination_Login thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_router_AppDestination_Login thiz);
                } Login;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_router_AppDestination_Main (*_instance)();
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_router_AppDestination_Main thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_router_AppDestination_Main thiz);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_router_AppDestination_Main thiz, libkn_kref_kotlin_Array typeParamsSerializers);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer_)(libkn_kref_com_example_kmpoh_router_AppDestination_Main thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_router_AppDestination_Main thiz);
                } Main;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword (*_instance)();
                  libkn_KBoolean (*equals)(libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword thiz, libkn_kref_kotlin_Any other);
                  libkn_KInt (*hashCode)(libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword thiz);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword thiz, libkn_kref_kotlin_Array typeParamsSerializers);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer_)(libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword thiz);
                  const char* (*toString)(libkn_kref_com_example_kmpoh_router_AppDestination_ChangePassword thiz);
                } ChangePassword;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_router_AppDestination_Companion (*_instance)();
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer)(libkn_kref_com_example_kmpoh_router_AppDestination_Companion thiz, libkn_kref_kotlin_Array typeParamsSerializers);
                  libkn_kref_kotlinx_serialization_KSerializer (*serializer_)(libkn_kref_com_example_kmpoh_router_AppDestination_Companion thiz);
                } Companion;
                libkn_KType* (*_type)(void);
              } AppDestination;
              libkn_KInt (*com_example_kmpoh_router_AppDestination_ChangePassword$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_router_AppDestination_Login$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_router_AppDestination_Main$stableprop_getter)();
              void (*AppNavGraph)(libkn_kref_androidx_navigation_NavHostController navController, libkn_kref_com_example_kmpoh_router_AppDestination startDestination);
              libkn_KInt (*com_example_kmpoh_router_AppDestination_ChangePassword$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_router_AppDestination_Login$stableprop_getter_)();
              libkn_KInt (*com_example_kmpoh_router_AppDestination_Main$stableprop_getter_)();
            } router;
            struct {
              struct {
                libkn_KType* (*_type)(void);
                const char* (*getString)(libkn_kref_com_example_kmpoh_storage_KeyValueStore thiz, const char* key);
                void (*putString)(libkn_kref_com_example_kmpoh_storage_KeyValueStore thiz, const char* key, const char* value);
                void (*remove)(libkn_kref_com_example_kmpoh_storage_KeyValueStore thiz, const char* key);
              } KeyValueStore;
              struct {
                libkn_KType* (*_type)(void);
                libkn_kref_com_example_kmpoh_storage_StorageKeys (*_instance)();
                const char* (*get_AUTH_ACCESS_TOKEN)(libkn_kref_com_example_kmpoh_storage_StorageKeys thiz);
                const char* (*get_AUTH_REFRESH_TOKEN)(libkn_kref_com_example_kmpoh_storage_StorageKeys thiz);
                const char* (*get_DEVICE_ID)(libkn_kref_com_example_kmpoh_storage_StorageKeys thiz);
                const char* (*get_USER_NAME)(libkn_kref_com_example_kmpoh_storage_StorageKeys thiz);
              } StorageKeys;
              libkn_KInt (*com_example_kmpoh_storage_StorageKeys$stableprop_getter)();
              const char* (*getOrCreateDeviceId)(libkn_kref_com_example_kmpoh_storage_KeyValueStore store);
              libkn_KInt (*com_example_kmpoh_storage_StorageKeys$stableprop_getter_)();
              const char* (*get_PLATFORM_NAME)();
              libkn_KInt (*com_example_kmpoh_storage_StorageKeys$stableprop_getter__)();
              libkn_KInt (*com_example_kmpoh_storage_StorageKeys$stableprop_getter___)();
              libkn_kref_com_example_kmpoh_storage_KeyValueStore (*createKeyValueStore)();
            } storage;
            struct {
              struct {
                void (*LoadingView)(libkn_kref_androidx_compose_ui_Modifier modifier);
                void (*PrimaryButton)(const char* text, libkn_kref_kotlin_Function0 onClick, libkn_kref_androidx_compose_ui_Modifier modifier, libkn_KBoolean enabled, libkn_KBoolean isLoading, libkn_KFloat height, libkn_KULong containerColor, libkn_KULong disabledContainerColor, libkn_KULong contentColor, libkn_kref_kotlin_Function0 trailingIcon);
                void (*PrimaryInput)(const char* value, libkn_kref_kotlin_Function1 onValueChange, const char* placeholder, libkn_KLong fontSize, libkn_kref_androidx_compose_ui_Modifier modifier, libkn_KBoolean enabled, libkn_KBoolean singleLine, libkn_KFloat height, libkn_kref_kotlin_Function0 leadingIcon, libkn_kref_kotlin_Function0 trailingIcon, libkn_kref_androidx_compose_ui_text_input_VisualTransformation visualTransformation, libkn_kref_androidx_compose_foundation_text_KeyboardOptions keyboardOptions, libkn_KULong focusedBorderColor, libkn_KULong unfocusedBorderColor, libkn_KULong containerColor, libkn_kref_androidx_compose_foundation_text_KeyboardActions keyboardActions);
              } components;
              struct {
                struct {
                  struct {
                    libkn_KType* (*_type)(void);
                    libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList (*_instance)();
                    libkn_KULong (*get_Accent)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_AccentLight)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Background)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Card)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_CustomerLevelBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_CustomerLevelText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Danger)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Divider)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_DoneBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_DoneText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_HighRiskBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_HighRiskText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_LowRiskBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_LowRiskText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_MediumRiskBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_MediumRiskText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_PreviewBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Primary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_PrimaryLight)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_RouteIconBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_RunningBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_RunningText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_ServiceModeBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_ServiceModeText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_ServiceTypeBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_ServiceTypeText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Success)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_TextPrimary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_TextSecondary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_TextTertiary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_WaitingBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_WaitingText)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                    libkn_KULong (*get_Warning)(libkn_kref_com_example_kmpoh_ui_theme_AppColors_WorkOrderList thiz);
                  } WorkOrderList;
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_ui_theme_AppColors (*_instance)();
                  libkn_KULong (*get_Background)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Black)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Border)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_BorderError)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_BorderFocused)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_DisabledBackground)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Divider)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Error)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Info)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Mask)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_MaskLight)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Palette1A000000)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Palette66000000)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Palette6637DDA0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Palette667B83FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Palette66FFFFFF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteCC000000)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteCCFFFFFF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF0284C7)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF047F5F)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF0D536A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF0D9488)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF101826)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF10BF6A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF111111)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF111827)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF145D70)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF14B980)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF171C28)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF17202E)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF17657A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF1A1A1E)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF1B6E70)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF1D6F86)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF1F2633)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF20242E)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF20A969)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF21A67A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF21C894)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF22B573)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF2563EB)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF2979FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF2B7890)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF2E7E96)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF2ECC71)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF3A3A3E)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF3F7EF3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF4285F4)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF475569)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF5A5A60)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6366F1)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6565F6)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF666666)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF696BFF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6978FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6A6A70)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6B7280)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6F7787)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF6F798A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF7A8494)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF7B61FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF7B8494)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF7D83FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF8A6D2A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF8CB3C0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF999999)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF9A9AA0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF9AA3B2)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF9BA6B8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF9BE9C6)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFF9EA7B3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFA4ACBA)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFAAB2BE)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFAAB4C3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFAEB6C3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFC4CCD7)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFC9D3DF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFCCCCCC)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFD1D1D1)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFD1D5DB)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFD4923B)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFD97706)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFD99A41)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFDDE6F0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE0E0E0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE0E5EC)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE0F2FE)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE1E6EE)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE25353)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE2E6EC)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE39A2D)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE4E4E8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE4F6EE)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE4F8EA)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE5E9EF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE6E6E9)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE6F0F2)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE6F2FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE7EAF0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE7F8EF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE7FFF4)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE8563C)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE88700)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE8A23B)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE8A93C)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE8EDF4)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFE9FFF4)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEAEAEA)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEAF1F4)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEAF1F5)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEAF6F0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEAF6F8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEEEEEE)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEF4444)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEFF2FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFEFF3F7)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF04B45)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF0F3F8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF1F1F3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF1F4F7)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF1F4F8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF1F5FF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF2F0F2)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF2F2F2)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF3F4F6)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF4F6FA)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF4F7FA)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF5A623)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF5F6FA)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF5F7FB)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF7F7F8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFF8FAFC)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFBEFC2)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFCF5E3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFF5A40)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFF9500)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFF9F0A)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFDED9)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFEEEE)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF2DD)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF3E3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF4DF)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF5E6)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF5F3)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF6E8)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF8E1)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFF9ED)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteFFFFFDF0)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PaletteWhite)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Primary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PrimaryDark)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_PrimaryLight)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Secondary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Success)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Surface)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_SurfaceVariant)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_TextDisabled)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_TextHint)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_TextPrimary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_TextSecondary)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_TextWhite)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Transparent)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                  libkn_KULong (*get_Warning)(libkn_kref_com_example_kmpoh_ui_theme_AppColors thiz);
                } AppColors;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_ui_theme_AppDimens (*_instance)();
                  libkn_KFloat (*get_BorderWidth)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_BorderWidthFocused)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_BottomBarHeight)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_ButtonHeight)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_ButtonHeightLarge)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_ButtonHeightSmall)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_CardElevation)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_CardPadding)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_DialogButtonHeight)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_DialogHorizontalPadding)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_DialogVerticalPadding)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Divider)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_DividerDot1)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_DividerHalf)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp0)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp0_5)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp0_6)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp0_8)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp1)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp10)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp100)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp102)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp106)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp11)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp112)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp12)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp120)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp13)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp136)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp14)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp15)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp15_5)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp16)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp17)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp170)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp174)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp18)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp180)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp19)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp2)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp20)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp200)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp22)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp24)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp240)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp26)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp28)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp292)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp2_2)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp2_5)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp2_8)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp3)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp30)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp32)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp320)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp34)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp36)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp38)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp4)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp40)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp42)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp44)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp46)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp48)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp5)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp50)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp52)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp56)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp58)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp6)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp60)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp62)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp64)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp68)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp7)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp72)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp76)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp78)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp8)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp80)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp82)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp86)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp88)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp9)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp90)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp92)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Dp96)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_IconExtraLarge)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_IconLarge)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_IconMedium)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_IconNormal)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_IconSmall)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_IconTiny)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_ListItemMinHeight)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_ListItemPaddingHorizontal)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_ListItemPaddingVertical)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_PageHorizontal)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_PageVertical)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space10)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space12)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space16)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space2)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space20)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space24)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space32)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space4)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space40)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space48)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space6)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_Space8)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_TextFieldHeight)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_TextFieldHeightLarge)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_TextFieldHeightSmall)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_TopBarHeight)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                  libkn_KFloat (*get_TouchTarget)(libkn_kref_com_example_kmpoh_ui_theme_AppDimens thiz);
                } AppDimens;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_ui_theme_AppFontSize (*_instance)();
                  libkn_KLong (*get_Body)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_BodyLarge)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_BodySmall)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Caption)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Display)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Headline)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Small)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp0_6)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp10)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp11)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp12)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp13)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp14)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp15)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp16)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp17)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp18)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp20)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp21)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp22)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp23)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp24)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp26)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp28)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp32)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Sp9)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Subtitle)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Tiny)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_Title)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                  libkn_KLong (*get_TitleLarge)(libkn_kref_com_example_kmpoh_ui_theme_AppFontSize thiz);
                } AppFontSize;
                libkn_KInt (*com_example_kmpoh_ui_theme_AppColors$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppColors_WorkOrderList$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppDimens$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppFontSize$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppColors$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppColors_WorkOrderList$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppDimens$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppFontSize$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppColors$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppColors_WorkOrderList$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppDimens$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_ui_theme_AppFontSize$stableprop_getter__)();
              } theme;
            } ui;
            struct {
              struct {
                libkn_kref_kotlinx_datetime_LocalDate (*todayDate)();
                libkn_kref_kotlinx_datetime_YearMonth (*yearMonthOf)(libkn_kref_kotlinx_datetime_LocalDate date);
              } date;
              libkn_KInt (*com_example_kmpoh_utils_UiState$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_utils_UiState_Empty$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_utils_UiState_Error$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_utils_UiState_Idle$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_utils_UiState_Loading$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_utils_UiState_NoPermission$stableprop_getter)();
              libkn_KInt (*com_example_kmpoh_utils_UiState_Success$stableprop_getter)();
            } utils;
            struct {
              libkn_KType* (*_type)(void);
              const char* (*get_name)(libkn_kref_com_example_kmpoh_Platform thiz);
            } Platform;
            struct {
              libkn_KType* (*_type)(void);
              libkn_kref_com_example_kmpoh_OhosPlatform (*OhosPlatform)();
              const char* (*get_name)(libkn_kref_com_example_kmpoh_OhosPlatform thiz);
            } OhosPlatform;
            libkn_KInt (*com_example_kmpoh_OhosPlatform$stableprop_getter)();
            libkn_KInt (*com_example_kmpoh_OhosPlatform$stableprop_getter_)();
            void* (*MainArkUIViewController_)(void* env);
            libkn_KInt (*com_example_kmpoh_OhosPlatform$stableprop_getter__)();
            libkn_KInt (*com_example_kmpoh_OhosPlatform$stableprop_getter___)();
            libkn_kref_com_example_kmpoh_Platform (*getPlatform)();
          } kmpoh;
        } example;
      } com;
      struct {
        struct {
          struct {
            struct {
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_array$stableprop_getter)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_drawable$stableprop_getter)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_font$stableprop_getter)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_plurals$stableprop_getter)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_string$stableprop_getter)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_array$stableprop_getter_)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_drawable$stableprop_getter_)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_font$stableprop_getter_)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_plurals$stableprop_getter_)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_string$stableprop_getter_)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_array$stableprop_getter__)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_drawable$stableprop_getter__)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_font$stableprop_getter__)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_plurals$stableprop_getter__)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_string$stableprop_getter__)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_array$stableprop_getter___)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_drawable$stableprop_getter___)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_font$stableprop_getter___)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_plurals$stableprop_getter___)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_string$stableprop_getter___)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_array$stableprop_getter____)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_drawable$stableprop_getter____)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_font$stableprop_getter____)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_plurals$stableprop_getter____)();
              libkn_KInt (*kmpoh_composeapp_generated_resources_Res_string$stableprop_getter____)();
            } resources;
          } generated;
        } composeapp;
      } kmpoh;
      struct {
        struct {
          struct {
            struct {
              struct {
                void (*InitJsRenderNodeContext_)(void* env, void* nodeConstructor, void* statusModifyConstructor, libkn_KDouble ratio, libkn_KBoolean fixed);
                void (*_Export_ArkUIViewController_aboutToAppear)(void* controllerRef);
                void (*_Export_ArkUIViewController_aboutToDisappear)(void* controllerRef);
                void (*_Export_ArkUIViewController_cancelSyncRefresh)(void* controllerRef, libkn_KInt refreshId);
                void (*_Export_ArkUIViewController_dispatchHoverEvent)(void* controllerRef);
                void (*_Export_ArkUIViewController_dispatchMouseEvent)(void* controllerRef);
                libkn_KBoolean (*_Export_ArkUIViewController_dispatchTouchEvent)(void* controllerRef, void* nativeTouchEvent, libkn_KBoolean ignoreInteropView);
                void (*_Export_ArkUIViewController_draw)(void* controllerRef, void* canvas);
                libkn_KInt (*_Export_ArkUIViewController_findNodeIdAt)(void* controllerRef, libkn_KFloat x, libkn_KFloat y);
                const char* (*_Export_ArkUIViewController_getId)(void* controllerRef);
                void* (*_Export_ArkUIViewController_getJsNode)(void* controllerRef);
                libkn_KInt (*_Export_ArkUIViewController_getRendererTypeId)();
                void* (*_Export_ArkUIViewController_getXComponentRender)(void* controllerRef);
                void (*_Export_ArkUIViewController_initFusionRendererNode)(void* controllerRef, libkn_KBoolean enableCApi, void* rootContent, void* frameMgr);
                void (*_Export_ArkUIViewController_keyboardWillHide)(void* controllerRef);
                void (*_Export_ArkUIViewController_keyboardWillShow)(void* controllerRef, libkn_KFloat keyboardHeight);
                libkn_KBoolean (*_Export_ArkUIViewController_onBackPress)(void* controllerRef);
                void (*_Export_ArkUIViewController_onConfigurationUpdate)(void* controllerRef);
                void (*_Export_ArkUIViewController_onFinalize)(void* controllerRef);
                void (*_Export_ArkUIViewController_onFocusEvent)(void* controllerRef);
                void (*_Export_ArkUIViewController_onFrame)(void* controllerRef, libkn_KLong timestamp, libkn_KLong targetTimestamp);
                void (*_Export_ArkUIViewController_onIdle)(void* controllerRef, libkn_KLong timeLeft);
                void (*_Export_ArkUIViewController_onKeyEvent)(void* controllerRef);
                void (*_Export_ArkUIViewController_onPageHide)(void* controllerRef);
                void (*_Export_ArkUIViewController_onPageShow)(void* controllerRef);
                void (*_Export_ArkUIViewController_onSurfaceChanged)(void* controllerRef, libkn_KInt width, libkn_KInt height);
                void (*_Export_ArkUIViewController_onSurfaceCreated)(void* controllerRef, void* xcomponentPtr, libkn_KInt width, libkn_KInt height);
                void (*_Export_ArkUIViewController_onSurfaceDestroyed)(void* controllerRef);
                void (*_Export_ArkUIViewController_onSurfaceHide)(void* controllerRef);
                void (*_Export_ArkUIViewController_onSurfaceShow)(void* controllerRef);
                libkn_KInt (*_Export_ArkUIViewController_requestSyncRefresh)(void* controllerRef);
                const char* (*_Export_ArkUIViewController_sendMessage)(void* controllerRef, const char* type, const char* message);
                void (*_Export_ArkUIViewController_setContext)(void* controllerRef, void* context);
                void (*_Export_ArkUIViewController_setEnv)(void* controllerRef, void* env);
                void (*_Export_ArkUIViewController_setId)(void* controllerRef, const char* id);
                void (*_Export_ArkUIViewController_setLocaleAndStringProvider)(void* controllerRef, void* provider);
                void (*_Export_ArkUIViewController_setMessenger)(void* controllerRef, void* messenger);
                void (*_Export_ArkUIViewController_setRendererBackendId)(void* controllerRef, libkn_KInt backendId);
                void (*_Export_ArkUIViewController_setRootView)(void* controllerRef, void* backRootView, void* foreRootView, void* touchableRootView);
                void (*_Export_ArkUIViewController_setUIContext)(void* controllerRef, void* uiContext);
                void (*_Export_ArkUIViewController_setXComponentRender)(void* controllerRef, void* render);
                libkn_KLong (*getCurrentTimeNanos)();
                void (*_Export_ArkUIViewInitializer_init)(void* env, void* exports);
              } arkui;
            } ui;
          } export_;
        } compose;
      } androidx;
    } root;
  } kotlin;
} libkn_ExportedSymbols;
extern libkn_ExportedSymbols* libkn_symbols(void);
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* KONAN_LIBKN_H */
