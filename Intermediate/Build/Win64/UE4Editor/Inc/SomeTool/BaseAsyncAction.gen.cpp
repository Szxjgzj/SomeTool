// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/Async/BaseAsyncAction.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseAsyncAction() {}
// Cross Module References
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
	SOMETOOL_API UClass* Z_Construct_UClass_UBaseAsyncAction_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UBaseAsyncAction();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintAsyncActionBase();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics
	{
		struct _Script_SomeTool_eventAsyncDelegate_Parms
		{
			float Time;
			float CurveValue;
			float A;
			float B;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Time;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurveValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_A;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventAsyncDelegate_Parms, Time), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_CurveValue = { "CurveValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventAsyncDelegate_Parms, CurveValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventAsyncDelegate_Parms, A), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventAsyncDelegate_Parms, B), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_Time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_CurveValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::NewProp_B,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SomeTool, nullptr, "AsyncDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_SomeTool_eventAsyncDelegate_Parms), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
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
		P_GET_OBJECT(UCurveFloat,Z_Param_CurveFloat);
		P_GET_PROPERTY(FFloatProperty,Z_Param_CurveValue);
		P_GET_UBOOL(Z_Param_bIsUseCurve);
		P_GET_PROPERTY(FFloatProperty,Z_Param_A);
		P_GET_PROPERTY(FFloatProperty,Z_Param_B);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaSeconds);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Time);
		P_GET_PROPERTY(FFloatProperty,Z_Param_FirstDelay);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBaseAsyncAction**)Z_Param__Result=UBaseAsyncAction::AsyncAction(Z_Param_worldContext,Z_Param_CurveFloat,Z_Param_CurveValue,Z_Param_bIsUseCurve,Z_Param_A,Z_Param_B,Z_Param_DeltaSeconds,Z_Param_Time,Z_Param_FirstDelay);
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
			UCurveFloat* CurveFloat;
			float CurveValue;
			bool bIsUseCurve;
			float A;
			float B;
			float DeltaSeconds;
			float Time;
			float FirstDelay;
			UBaseAsyncAction* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_worldContext;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CurveFloat;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurveValue;
		static void NewProp_bIsUseCurve_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsUseCurve;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_A;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_B;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DeltaSeconds;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Time;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FirstDelay;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_worldContext = { "worldContext", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, worldContext), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_CurveFloat = { "CurveFloat", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, CurveFloat), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_CurveValue = { "CurveValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, CurveValue), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_bIsUseCurve_SetBit(void* Obj)
	{
		((BaseAsyncAction_eventAsyncAction_Parms*)Obj)->bIsUseCurve = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_bIsUseCurve = { "bIsUseCurve", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(BaseAsyncAction_eventAsyncAction_Parms), &Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_bIsUseCurve_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_A = { "A", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, A), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_B = { "B", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, B), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_DeltaSeconds = { "DeltaSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, DeltaSeconds), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, Time), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_FirstDelay = { "FirstDelay", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, FirstDelay), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseAsyncAction_eventAsyncAction_Parms, ReturnValue), Z_Construct_UClass_UBaseAsyncAction_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_worldContext,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_CurveFloat,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_CurveValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_bIsUseCurve,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_A,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_B,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_DeltaSeconds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_Time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_FirstDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "UIAsyncTask" },
		{ "CPP_Default_DeltaSeconds", "1.000000" },
		{ "CPP_Default_FirstDelay", "0.000000" },
		{ "CPP_Default_Time", "5.000000" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAsyncAction, nullptr, "AsyncAction", nullptr, nullptr, sizeof(BaseAsyncAction_eventAsyncAction_Parms), Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseAsyncAction_AsyncAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBaseAsyncAction_AsyncAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAsyncAction, nullptr, "OnUpdate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseAsyncAction_OnUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBaseAsyncAction_OnUpdate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UBaseAsyncAction_NoRegister()
	{
		return UBaseAsyncAction::StaticClass();
	}
	struct Z_Construct_UClass_UBaseAsyncAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnStartDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnStartDelegate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnUpdateDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnUpdateDelegate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCompleteDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCompleteDelegate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBaseAsyncAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintAsyncActionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBaseAsyncAction_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBaseAsyncAction_AsyncAction, "AsyncAction" }, // 1440090941
		{ &Z_Construct_UFunction_UBaseAsyncAction_OnUpdate, "OnUpdate" }, // 1735297124
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncDelegateTwo,float,RestTime,UObject*,Object);\n" },
		{ "IncludePath", "Async/BaseAsyncAction.h" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAsyncDelegateTwo,float,RestTime,UObject*,Object);" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate_MetaData[] = {
		{ "DisplayName", "OnStart" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate = { "OnStartDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseAsyncAction, OnStartDelegate), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate_MetaData[] = {
		{ "DisplayName", "OnUpdate" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate = { "OnUpdateDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseAsyncAction, OnUpdateDelegate), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate_MetaData[] = {
		{ "DisplayName", "OnComplete" },
		{ "ModuleRelativePath", "Async/BaseAsyncAction.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate = { "OnCompleteDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseAsyncAction, OnCompleteDelegate), Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBaseAsyncAction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnStartDelegate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnUpdateDelegate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAsyncAction_Statics::NewProp_OnCompleteDelegate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBaseAsyncAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseAsyncAction>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBaseAsyncAction_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UBaseAsyncAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAsyncAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBaseAsyncAction()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBaseAsyncAction_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBaseAsyncAction, 4273370932);
	template<> SOMETOOL_API UClass* StaticClass<UBaseAsyncAction>()
	{
		return UBaseAsyncAction::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBaseAsyncAction(Z_Construct_UClass_UBaseAsyncAction, &UBaseAsyncAction::StaticClass, TEXT("/Script/SomeTool"), TEXT("UBaseAsyncAction"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBaseAsyncAction);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
