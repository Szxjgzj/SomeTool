// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Async/BaseAsyncAction.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UBaseAsyncAction;
class UObject;
#ifdef SOMETOOL_BaseAsyncAction_generated_h
#error "BaseAsyncAction.generated.h already included, missing '#pragma once' in BaseAsyncAction.h"
#endif
#define SOMETOOL_BaseAsyncAction_generated_h

#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_6_DELEGATE \
SOMETOOL_API void FAsyncDelegate_DelegateWrapper(const FMulticastScriptDelegate& AsyncDelegate, float Time);


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnUpdate); \
	DECLARE_FUNCTION(execAsyncAction);


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBaseAsyncAction(); \
	friend struct Z_Construct_UClass_UBaseAsyncAction_Statics; \
public: \
	DECLARE_CLASS(UBaseAsyncAction, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UBaseAsyncAction)


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseAsyncAction(UBaseAsyncAction&&); \
	NO_API UBaseAsyncAction(const UBaseAsyncAction&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseAsyncAction); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseAsyncAction); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseAsyncAction)


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_8_PROLOG
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_INCLASS_NO_PURE_DECLS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class UBaseAsyncAction>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
