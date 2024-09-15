// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/ActionComponent/ActionTask.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActionTask() {}
// Cross Module References
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionTask_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionTask();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SomeTool, nullptr, "TickEventDelegate__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
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
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_BeginPlay_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_BeginPlay_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "BeginPlay", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_BeginPlay_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_BeginPlay_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionTask_BeginPlay()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionTask_BeginPlay_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_EndTask_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_EndTask_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_EndTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "EndTask", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_EndTask_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_EndTask_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionTask_EndTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionTask_EndTask_Statics::FuncParams);
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ActionTask_eventGetActionComponent_Parms, ReturnValue), Z_Construct_UClass_UActionComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "GetActionComponent", nullptr, nullptr, sizeof(ActionTask_eventGetActionComponent_Parms), Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionTask_GetActionComponent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionTask_GetActionComponent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_GetOwner_Statics
	{
		struct ActionTask_eventGetOwner_Parms
		{
			AActor* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UActionTask_GetOwner_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ActionTask_eventGetOwner_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionTask_GetOwner_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_GetOwner_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_GetOwner_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "GetOwner", nullptr, nullptr, sizeof(ActionTask_eventGetOwner_Parms), Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetOwner_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_GetOwner_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_GetOwner_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionTask_GetOwner()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionTask_GetOwner_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "OnTaskEnd", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C020800, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionTask_OnTaskEnd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionTask_OnTaskEnd_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionTask_OnTaskStart_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionTask, nullptr, "OnTaskStart", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C020800, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionTask_OnTaskStart()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionTask_OnTaskStart_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UActionTask_NoRegister()
	{
		return UActionTask::StaticClass();
	}
	struct Z_Construct_UClass_UActionTask_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnTickEventDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTickEventDelegate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UActionTask_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UActionTask_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UActionTask_BeginPlay, "BeginPlay" }, // 4175680468
		{ &Z_Construct_UFunction_UActionTask_EndTask, "EndTask" }, // 946155617
		{ &Z_Construct_UFunction_UActionTask_GetActionComponent, "GetActionComponent" }, // 2817161690
		{ &Z_Construct_UFunction_UActionTask_GetOwner, "GetOwner" }, // 1774590062
		{ &Z_Construct_UFunction_UActionTask_OnTaskEnd, "OnTaskEnd" }, // 3834737460
		{ &Z_Construct_UFunction_UActionTask_OnTaskStart, "OnTaskStart" }, // 1063781266
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionTask_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEvent)\n" },
		{ "IncludePath", "ActionComponent/ActionTask.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
		{ "ToolTip", "DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTickEvent)" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate_MetaData[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionTask.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate = { "OnTickEventDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UActionTask, OnTickEventDelegate), Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UActionTask_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionTask_Statics::NewProp_OnTickEventDelegate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UActionTask_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActionTask>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UActionTask_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UActionTask_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UActionTask_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UActionTask()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UActionTask_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UActionTask, 3240973334);
	template<> SOMETOOL_API UClass* StaticClass<UActionTask>()
	{
		return UActionTask::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UActionTask(Z_Construct_UClass_UActionTask, &UActionTask::StaticClass, TEXT("/Script/SomeTool"), TEXT("UActionTask"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UActionTask);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
