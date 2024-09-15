// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/ActionComponent/ActionComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActionComponent() {}
// Cross Module References
	SOMETOOL_API UClass* Z_Construct_UClass_UActionComponent_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
	SOMETOOL_API UClass* Z_Construct_UClass_UActionTask_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
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
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ActionComponent_eventExcuteTask_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::NewProp_Index,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_Index", "0" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionComponent, nullptr, "ExcuteTask", nullptr, nullptr, sizeof(ActionComponent_eventExcuteTask_Parms), Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionComponent_ExcuteTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionComponent_ExcuteTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics
	{
		struct ActionComponent_eventGetCurtTask_Parms
		{
			UActionTask* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ActionComponent_eventGetCurtTask_Parms, ReturnValue), Z_Construct_UClass_UActionTask_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UActionComponent, nullptr, "GetCurtTask", nullptr, nullptr, sizeof(ActionComponent_eventGetCurtTask_Parms), Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UActionComponent_GetCurtTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UActionComponent_GetCurtTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UActionComponent_NoRegister()
	{
		return UActionComponent::StaticClass();
	}
	struct Z_Construct_UClass_UActionComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_TasksClass_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TasksClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_TasksClass;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Tasks_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Tasks_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Tasks;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsAuto_MetaData[];
#endif
		static void NewProp_bIsAuto_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsAuto;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UActionComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UActionComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UActionComponent_ExcuteTask, "ExcuteTask" }, // 691873232
		{ &Z_Construct_UFunction_UActionComponent_GetCurtTask, "GetCurtTask" }, // 902254062
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "ActionComponent/ActionComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_Inner = { "TasksClass", nullptr, (EPropertyFlags)0x0004000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UActionTask_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_MetaData[] = {
		{ "Category", "ActionComponent" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass = { "TasksClass", nullptr, (EPropertyFlags)0x0014000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UActionComponent, TasksClass), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_Inner = { "Tasks", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UActionTask_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_MetaData[] = {
		{ "Category", "ActionComponent" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks = { "Tasks", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UActionComponent, Tasks), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_MetaData[] = {
		{ "Category", "ActionComponent" },
		{ "ModuleRelativePath", "ActionComponent/ActionComponent.h" },
	};
#endif
	void Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_SetBit(void* Obj)
	{
		((UActionComponent*)Obj)->bIsAuto = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto = { "bIsAuto", nullptr, (EPropertyFlags)0x0010000000010001, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UActionComponent), &Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_SetBit, METADATA_PARAMS(Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UActionComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_TasksClass,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_Tasks,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UActionComponent_Statics::NewProp_bIsAuto,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UActionComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActionComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UActionComponent_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UActionComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UActionComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UActionComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UActionComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UActionComponent, 2920130804);
	template<> SOMETOOL_API UClass* StaticClass<UActionComponent>()
	{
		return UActionComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UActionComponent(Z_Construct_UClass_UActionComponent, &UActionComponent::StaticClass, TEXT("/Script/SomeTool"), TEXT("UActionComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UActionComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
