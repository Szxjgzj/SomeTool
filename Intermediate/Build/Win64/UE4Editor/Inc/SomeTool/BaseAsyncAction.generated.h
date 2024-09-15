// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UCurveFloat;
class UBaseAsyncAction;
#ifdef SOMETOOL_BaseAsyncAction_generated_h
#error "BaseAsyncAction.generated.h already included, missing '#pragma once' in BaseAsyncAction.h"
#endif
#define SOMETOOL_BaseAsyncAction_generated_h

#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_6_DELEGATE \
struct _Script_SomeTool_eventAsyncDelegate_Parms \
{ \
	float Time; \
	float CurveValue; \
	float A; \
	float B; \
}; \
static inline void FAsyncDelegate_DelegateWrapper(const FMulticastScriptDelegate& AsyncDelegate, float Time, float CurveValue, float A, float B) \
{ \
	_Script_SomeTool_eventAsyncDelegate_Parms Parms; \
	Parms.Time=Time; \
	Parms.CurveValue=CurveValue; \
	Parms.A=A; \
	Parms.B=B; \
	AsyncDelegate.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA
#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnUpdate); \
	DECLARE_FUNCTION(execAsyncAction);


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnUpdate); \
	DECLARE_FUNCTION(execAsyncAction);


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBaseAsyncAction(); \
	friend struct Z_Construct_UClass_UBaseAsyncAction_Statics; \
public: \
	DECLARE_CLASS(UBaseAsyncAction, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UBaseAsyncAction)


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_INCLASS \
private: \
	static void StaticRegisterNativesUBaseAsyncAction(); \
	friend struct Z_Construct_UClass_UBaseAsyncAction_Statics; \
public: \
	DECLARE_CLASS(UBaseAsyncAction, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UBaseAsyncAction)


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBaseAsyncAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseAsyncAction) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseAsyncAction); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseAsyncAction); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseAsyncAction(UBaseAsyncAction&&); \
	NO_API UBaseAsyncAction(const UBaseAsyncAction&); \
public:


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseAsyncAction(UBaseAsyncAction&&); \
	NO_API UBaseAsyncAction(const UBaseAsyncAction&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseAsyncAction); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseAsyncAction); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseAsyncAction)


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_PRIVATE_PROPERTY_OFFSET
#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_8_PROLOG
#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_RPC_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_INCLASS \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_INCLASS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class UBaseAsyncAction>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID P_555_Plugins_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
