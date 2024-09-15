// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/Async/BaseAsyncAction.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseAsyncAction() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintAsyncActionBase();
	SOMETOOL_API UClass* Z_Construct_UClass_UBaseAsyncAction();
	SOMETOOL_API UClass* Z_Construct_UClass_UBaseAsyncAction_NoRegister();
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics
	{
		struct _Script_SomeTool_eventAsyncDelegate_Parms
		{
			float Time;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SomeTool_eventAsyncDelegate_Parms, Time), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_Time,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SomeTool, nullptr, "AsyncDelegate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::_Script_SomeTool_eventAsyncDelegate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::_Script_SomeTool_eventAsyncDelegate_Parms) < MAX_uint16);
	UFunction* Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FAsyncDelegate_DelegateWrapper(const FMulticastScriptDelegate& AsyncDelegate, float Time)
{
	struct _Script_SomeTool_eventAsyncDelegate_Parms
	{
		float Time;
	};
	_Script_SomeTool_eventAsyncDelegate_Parms Parms;
	Parms.Time=Time;
	AsyncDelegate.ProcessMulticastDelegate<UObject>(&Parms);
}
	DEFINE_FUNCTION(UBaseAsyncAction::execOnUpdate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnUpdate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseAsyncAction::execAsyncAction)
	{
		P_GET_OBJECT(UObject,Z_Param_worldContext);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaSeconds);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Time);
		P_GET_PROPERTY(FFloatProperty,Z_Param_FirstDelay);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBaseAsyncAction**)Z_Param__Result=UBaseAsyncAction::AsyncAction(Z_Param_worldContext,Z_Param_DeltaSeconds,Z_Param_Time,Z_Param_FirstDelay);
		P_NATIVE_END;
	}
	void UBaseAsyncAction::StaticRegisterNativesUBaseAsyncAction()
	{
		UClass* Class = UBaseAsyncAction::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AsyncAction", &UBaseAsyncAction::execAsyncAction },
			{ "OnUpdate", &UBaseAsyncAction::execOnUpdate },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics
	{
		struct BaseAsyncAction_eventAsyncAction_Parms
		{
			UObject* worldContext;
			float DeltaSeconds;
			float Time;
			float FirstDelay;
			UBaseAsyncAction* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContext;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaSeconds;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FirstDelay;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_worldContext = { "worldContext", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, worldContext), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_DeltaSeconds = { "DeltaSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, DeltaSeconds), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, Time), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_FirstDelay = { "FirstDelay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, FirstDelay), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, ReturnValue), Z_Construct_UClass_UBaseAsyncAction_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_worldContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_DeltaSeconds,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_Time,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_FirstDelay,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "UIAsyncTask" },
		{ "CPP_Default_DeltaSeconds", "1.000000" },
		{ "CPP_Default_FirstDelay", "0.000000" },
		{ "CPP_Default_Time", "5.000000" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAsyncAction, nullptr, "AsyncAction", nullptr, nullptr, Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::BaseAsyncAction_eventAsyncAction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::BaseAsyncAction_eventAsyncAction_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UBaseAsyncAction_AsyncAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAsyncAction, nullptr, "OnUpdate", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UBaseAsyncAction_OnUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBaseAsyncAction);
	UClass* Z_Construct_UClass_UBaseAsyncAction_NoRegister()
	{
		return UBaseAsyncAction::StaticClass();
	}
	struct Z_Construct_UClass_UBaseAsyncAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnStartDelegate_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnStartDelegate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnUpdateDelegate_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnUpdateDelegate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnCompleteDelegate_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCompleteDelegate;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBaseAsyncAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintAsyncActionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UBaseAsyncAction_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBaseAsyncAction_AsyncAction, "AsyncAction" }, // 1569604004
		{ &Z_Construct_UFunction_UBaseAsyncAction_OnUpdate, "OnUpdate" }, // 1573754130
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncDelegateTwo,float,RestTime,UObject*,Object);\n" },
#endif
		{ "IncludePath", "Async/BaseAsyncAction.h" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncDelegateTwo,float,RestTime,UObject*,Object);" },
#endif
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate_MetaData[] = {
		{ "DisplayName", "OnStart" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate = { "OnStartDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBaseAsyncAction, OnStartDelegate), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate_MetaData), Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate_MetaData) }; // 3787267727
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate_MetaData[] = {
		{ "DisplayName", "OnUpdate" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate = { "OnUpdateDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBaseAsyncAction, OnUpdateDelegate), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate_MetaData), Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate_MetaData) }; // 3787267727
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate_MetaData[] = {
		{ "DisplayName", "OnComplete" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate = { "OnCompleteDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBaseAsyncAction, OnCompleteDelegate), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate_MetaData), Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate_MetaData) }; // 3787267727
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBaseAsyncAction_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBaseAsyncAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseAsyncAction>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBaseAsyncAction_Statics::ClassParams = {
		&UBaseAsyncAction::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBaseAsyncAction_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::Class_MetaDataParams), Z_Construct_UClass_UBaseAsyncAction_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UBaseAsyncAction()
	{
		if (!Z_Registration_Info_UClass_UBaseAsyncAction.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBaseAsyncAction.OuterSingleton, Z_Construct_UClass_UBaseAsyncAction_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBaseAsyncAction.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<UBaseAsyncAction>()
	{
		return UBaseAsyncAction::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBaseAsyncAction);
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBaseAsyncAction, UBaseAsyncAction::StaticClass, TEXT("UBaseAsyncAction"), &Z_Registration_Info_UClass_UBaseAsyncAction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBaseAsyncAction), 2065881090U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_2648839627(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_Async_BaseAsyncAction_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
