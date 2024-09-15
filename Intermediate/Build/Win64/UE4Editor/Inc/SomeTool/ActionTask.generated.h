// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UActionComponent;
#ifdef SOMETOOL_ActionTask_generated_h
#error "ActionTask.generated.h already included, missing '#pragma once' in ActionTask.h"
#endif
#define SOMETOOL_ActionTask_generated_h

#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_13_DELEGATE \
static inline void FTickEventDelegate_DelegateWrapper(const FMulticastScriptDelegate& TickEventDelegate) \
{ \
	TickEventDelegate.ProcessMulticastDelegate<UObject>(NULL); \
}


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_SPARSE_DATA
#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_RPC_WRAPPERS \
	virtual void BeginPlay_Implementation(); \
 \
	DECLARE_FUNCTION(execBeginPlay); \
	DECLARE_FUNCTION(execGetOwner); \
	DECLARE_FUNCTION(execGetActionComponent); \
	DECLARE_FUNCTION(execEndTask);


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void BeginPlay_Implementation(); \
 \
	DECLARE_FUNCTION(execBeginPlay); \
	DECLARE_FUNCTION(execGetOwner); \
	DECLARE_FUNCTION(execGetActionComponent); \
	DECLARE_FUNCTION(execEndTask);


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_EVENT_PARMS
#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_CALLBACK_WRAPPERS
#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUActionTask(); \
	friend struct Z_Construct_UClass_UActionTask_Statics; \
public: \
	DECLARE_CLASS(UActionTask, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UActionTask)


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_INCLASS \
private: \
	static void StaticRegisterNativesUActionTask(); \
	friend struct Z_Construct_UClass_UActionTask_Statics; \
public: \
	DECLARE_CLASS(UActionTask, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UActionTask)


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UActionTask(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UActionTask) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UActionTask); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UActionTask); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UActionTask(UActionTask&&); \
	NO_API UActionTask(const UActionTask&); \
public:


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UActionTask(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UActionTask(UActionTask&&); \
	NO_API UActionTask(const UActionTask&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UActionTask); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UActionTask); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UActionTask)


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_PRIVATE_PROPERTY_OFFSET
#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_15_PROLOG \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_EVENT_PARMS


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_RPC_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_CALLBACK_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_INCLASS \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_CALLBACK_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_INCLASS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class UActionTask>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID P_555_Plugins_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
