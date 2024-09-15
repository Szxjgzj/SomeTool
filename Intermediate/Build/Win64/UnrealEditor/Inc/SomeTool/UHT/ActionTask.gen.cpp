// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/ActionComponent/ActionTask.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActionTask() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionComponent_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionTask();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionTask_NoRegister();
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SomeTool, nullptr, "TickEventDelegate__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FTickEventDelegate_DelegateWrapper(const FMulticastScriptDelegate& TickEventDelegate)
{
	TickEventDelegate.ProcessMulticastDelegate<UObject>(NULL);
}
	DEFINE_FUNCTION(UActionTask::execBeginPlay)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->BeginPlay_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UActionTask::execGetOwner)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(AActor**)Z_Param__Result=P_THIS->GetOwner();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UActionTask::execGetActionComponent)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UActionComponent**)Z_Param__Result=P_THIS->GetActionComponent();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UActionTask::execEndTask)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndTask();
		P_NATIVE_END;
	}
	static FName NAME_UActionTask_BeginPlay = FName(TEXT("BeginPlay"));
	void UActionTask::BeginPlay()
	{
		ProcessEvent(FindFunctionChecked(NAME_UActionTask_BeginPlay),NULL);
	}
	static FName NAME_UActionTask_OnTaskEnd = FName(TEXT("OnTaskEnd"));
	void UActionTask::OnTaskEnd()
	{
		ProcessEvent(FindFunctionChecked(NAME_UActionTask_OnTaskEnd),NULL);
	}
	static FName NAME_UActionTask_OnTaskStart = FName(TEXT("OnTaskStart"));
	void UActionTask::OnTaskStart()
	{
		ProcessEvent(FindFunctionChecked(NAME_UActionTask_OnTaskStart),NULL);
	}
	void UActionTask::StaticRegisterNativesUActionTask()
	{
		UClass* Class = UActionTask::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "BeginPlay", &UActionTask::execBeginPlay },
			{ "EndTask", &UActionTask::execEndTask },
			{ "GetActionComponent", &UActionTask::execGetActionComponent },
			{ "GetOwner", &UActionTask::execGetOwner },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UActionTask_BeginPlay_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_BeginPlay_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_BeginPlay_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "BeginPlay", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_BeginPlay_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionTask_BeginPlay_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UActionTask_BeginPlay()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionTask_BeginPlay_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_EndTask_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_EndTask_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_EndTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "EndTask", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_EndTask_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionTask_EndTask_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UActionTask_EndTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionTask_EndTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_GetActionComponent_Statics
	{
		struct ActionTask_eventGetActionComponent_Parms
		{
			UActionComponent* ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ActionTask_eventGetActionComponent_Parms, ReturnValue), Z_Construct_UClass_UActionComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue_MetaData), Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "GetActionComponent", nullptr, nullptr, Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::ActionTask_eventGetActionComponent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::ActionTask_eventGetActionComponent_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UActionTask_GetActionComponent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_GetOwner_Statics
	{
		struct ActionTask_eventGetOwner_Parms
		{
			AActor* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UActionTask_GetOwner_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ActionTask_eventGetOwner_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionTask_GetOwner_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_GetOwner_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_GetOwner_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "GetOwner", nullptr, nullptr, Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers), sizeof(Z_Construct_UFunction_UActionTask_GetOwner_Statics::ActionTask_eventGetOwner_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetOwner_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionTask_GetOwner_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UActionTask_GetOwner_Statics::ActionTask_eventGetOwner_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UActionTask_GetOwner()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionTask_GetOwner_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "OnTaskEnd", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UActionTask_OnTaskEnd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_OnTaskStart_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "OnTaskStart", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UActionTask_OnTaskStart()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UActionTask);
	UClass* Z_Construct_UClass_UActionTask_NoRegister()
	{
		return UActionTask::StaticClass();
	}
	struct Z_Construct_UClass_UActionTask_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnTickEventDelegate_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTickEventDelegate;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UActionTask_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UActionTask_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UActionTask_BeginPlay, "BeginPlay" }, // 4244976715
		{ &Z_Construct_UFunction_UActionTask_EndTask, "EndTask" }, // 1276961685
		{ &Z_Construct_UFunction_UActionTask_GetActionComponent, "GetActionComponent" }, // 2862141552
		{ &Z_Construct_UFunction_UActionTask_GetOwner, "GetOwner" }, // 7082675
		{ &Z_Construct_UFunction_UActionTask_OnTaskEnd, "OnTaskEnd" }, // 273472335
		{ &Z_Construct_UFunction_UActionTask_OnTaskStart, "OnTaskStart" }, // 3845895830
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionTask_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEvent)\n" },
#endif
		{ "IncludePath", "ActionComponent/ActionTask.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEvent)" },
#endif
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate_MetaData[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate = { "OnTickEventDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UActionTask, OnTickEventDelegate), Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate_MetaData), Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate_MetaData) }; // 1754969836
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UActionTask_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UActionTask_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActionTask>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UActionTask_Statics::ClassParams = {
		&UActionTask::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UActionTask_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::Class_MetaDataParams), Z_Construct_UClass_UActionTask_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UActionTask()
	{
		if (!Z_Registration_Info_UClass_UActionTask.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UActionTask.OuterSingleton, Z_Construct_UClass_UActionTask_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UActionTask.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<UActionTask>()
	{
		return UActionTask::StaticClass();
	}
	UActionTask::UActionTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UActionTask);
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UActionTask, UActionTask::StaticClass, TEXT("UActionTask"), &Z_Registration_Info_UClass_UActionTask, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UActionTask), 2788032915U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_236617747(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionTask_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
