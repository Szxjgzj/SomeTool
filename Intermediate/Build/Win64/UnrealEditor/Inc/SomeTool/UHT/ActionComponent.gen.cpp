// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/ActionComponent/ActionComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActionComponent() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionComponent();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionComponent_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionTask_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	DEFINE_FUNCTION(UActionComponent::execGetCurtTask)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UActionTask**)Z_Param__Result=P_THIS->GetCurtTask();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UActionComponent::execExcuteTask)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ExcuteTask(Z_Param_Index);
		P_NATIVE_END;
	}
	void UActionComponent::StaticRegisterNativesUActionComponent()
	{
		UClass* Class = UActionComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ExcuteTask", &UActionComponent::execExcuteTask },
			{ "GetCurtTask", &UActionComponent::execGetCurtTask },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics
	{
		struct ActionComponent_eventExcuteTask_Parms
		{
			int32 Index;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ActionComponent_eventExcuteTask_Parms, Index), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::NewProp_Index,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_Index", "0" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionComponent, nullptr, "ExcuteTask", nullptr, nullptr, Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers), sizeof(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::ActionComponent_eventExcuteTask_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::ActionComponent_eventExcuteTask_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UActionComponent_ExcuteTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics
	{
		struct ActionComponent_eventGetCurtTask_Parms
		{
			UActionTask* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ActionComponent_eventGetCurtTask_Parms, ReturnValue), Z_Construct_UClass_UActionTask_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionComponent, nullptr, "GetCurtTask", nullptr, nullptr, Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers), sizeof(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::ActionComponent_eventGetCurtTask_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::Function_MetaDataParams), Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::ActionComponent_eventGetCurtTask_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UActionComponent_GetCurtTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UActionComponent);
	UClass* Z_Construct_UClass_UActionComponent_NoRegister()
	{
		return UActionComponent::StaticClass();
	}
	struct Z_Construct_UClass_UActionComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_TasksClass_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TasksClass_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_TasksClass;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Tasks_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tasks_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Tasks;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsAuto_MetaData[];
#endif
		static void NewProp_bIsAuto_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsAuto;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UActionComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UActionComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UActionComponent_ExcuteTask, "ExcuteTask" }, // 3435853707
		{ &Z_Construct_UFunction_UActionComponent_GetCurtTask, "GetCurtTask" }, // 2252802635
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "ActionComponent/ActionComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_Inner = { "TasksClass", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_UActionTask_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_MetaData[] = {
		{ "Category", "ActionComponent" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass = { "TasksClass", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UActionComponent, TasksClass), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_MetaData), Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_Inner = { "Tasks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UActionTask_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_MetaData[] = {
		{ "Category", "ActionComponent" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks = { "Tasks", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UActionComponent, Tasks), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_MetaData), Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_MetaData[] = {
		{ "Category", "ActionComponent" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	void Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_SetBit(void* Obj)
	{
		((UActionComponent*)Obj)->bIsAuto = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto = { "bIsAuto", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UActionComponent), &Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_MetaData), Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UActionComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UActionComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActionComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UActionComponent_Statics::ClassParams = {
		&UActionComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UActionComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UActionComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UActionComponent()
	{
		if (!Z_Registration_Info_UClass_UActionComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UActionComponent.OuterSingleton, Z_Construct_UClass_UActionComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UActionComponent.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<UActionComponent>()
	{
		return UActionComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UActionComponent);
	UActionComponent::~UActionComponent() {}
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UActionComponent, UActionComponent::StaticClass, TEXT("UActionComponent"), &Z_Registration_Info_UClass_UActionComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UActionComponent), 2945310616U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionComponent_h_93230216(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_ActionComponent_ActionComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
