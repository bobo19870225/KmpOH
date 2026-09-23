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
} libkn_kref_kotlin_Function0;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlin_Function1;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_login_FakeLoginRepository;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_com_example_kmpoh_page_login_LoginViewModel;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_coroutines_CoroutineScope;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_kotlinx_coroutines_flow_StateFlow;
typedef struct {
  libkn_KNativePtr pinned;
} libkn_kref_androidx_compose_ui_Modifier;
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
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_login_FakeLoginRepository (*FakeLoginRepository)();
                } FakeLoginRepository;
                struct {
                  libkn_KType* (*_type)(void);
                  libkn_kref_com_example_kmpoh_page_login_LoginViewModel (*LoginViewModel)(libkn_kref_com_example_kmpoh_page_login_FakeLoginRepository repository, libkn_kref_kotlinx_coroutines_CoroutineScope scope);
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
                libkn_KInt (*com_example_kmpoh_page_login_FakeLoginRepository$stableprop_getter)();
                libkn_KInt (*com_example_kmpoh_page_login_LoginViewModel$stableprop_getter)();
                void (*LoginPage)(libkn_kref_kotlin_Function0 onLoginSuccess, libkn_kref_kotlin_Function1 onToastMessage);
                libkn_KInt (*com_example_kmpoh_page_login_FakeLoginRepository$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_login_LoginViewModel$stableprop_getter_)();
                libkn_KInt (*com_example_kmpoh_page_login_FakeLoginRepository$stableprop_getter__)();
                libkn_KInt (*com_example_kmpoh_page_login_LoginViewModel$stableprop_getter__)();
              } login;
            } page;
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
