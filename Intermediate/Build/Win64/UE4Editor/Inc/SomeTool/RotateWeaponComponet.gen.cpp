// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/RotateWeapon/RotateWeaponComponet.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRotateWeaponComponet() {}
// Cross Module References
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_URotateWeaponComponet_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_URotateWeaponComponet();
	ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_ETraceTypeQuery();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_EDrawDebugTrace();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
	SOMETOOL_API UClass* Z_Construct_UClass_AWeaponActor_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics
	{
		struct _Script_SomeTool_eventOnRotateDelegate_Parms
		{
			int32 Index;
			FVector CurtLocation;
			float LastAngle;
			float CurtAngle;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CurtLocation;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LastAngle;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurtAngle;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnRotateDelegate_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_CurtLocation = { "CurtLocation", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnRotateDelegate_Parms, CurtLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_LastAngle = { "LastAngle", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnRotateDelegate_Parms, LastAngle), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_CurtAngle = { "CurtAngle", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnRotateDelegate_Parms, CurtAngle), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_CurtLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_LastAngle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::NewProp_CurtAngle,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SomeTool, nullptr, "OnRotateDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_SomeTool_eventOnRotateDelegate_Parms), Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics
	{
		struct _Script_SomeTool_eventOnHitDelegate_Parms
		{
			UActorComponent* ActorComp;
			int32 Index;
			FVector HitLocation;
			FVector InstanceLocation;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActorComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ActorComp;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_HitLocation;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_InstanceLocation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_ActorComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_ActorComp = { "ActorComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnHitDelegate_Parms, ActorComp), Z_Construct_UClass_UActorComponent_NoRegister, METADATA_PARAMS(Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_ActorComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_ActorComp_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnHitDelegate_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_HitLocation = { "HitLocation", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnHitDelegate_Parms, HitLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_InstanceLocation = { "InstanceLocation", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SomeTool_eventOnHitDelegate_Parms, InstanceLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_ActorComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_HitLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::NewProp_InstanceLocation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SomeTool, nullptr, "OnHitDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_SomeTool_eventOnHitDelegate_Parms), Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execUpdateTransform)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Radius);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Angle);
		P_GET_STRUCT(FVector,Z_Param_Size);
		P_GET_PROPERTY(FFloatProperty,Z_Param_YawDelta);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FTransform*)Z_Param__Result=P_THIS->UpdateTransform(Z_Param_Index,Z_Param_Radius,Z_Param_Angle,Z_Param_Size,Z_Param_YawDelta);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execReduceWeapon)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReduceWeapon(Z_Param_Index);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execAddRotateWeapon)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Count);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Radius);
		P_GET_STRUCT(FVector,Z_Param_Size);
		P_GET_PROPERTY(FFloatProperty,Z_Param_YawDelta);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddRotateWeapon(Z_Param_Count,Z_Param_Radius,Z_Param_Size,Z_Param_YawDelta);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execBeHit)
	{
		P_GET_OBJECT(UActorComponent,Z_Param_Component);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_Index);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_HitLocation);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_InstanceLocation);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->BeHit_Implementation(Z_Param_Component,Z_Param_Out_Index,Z_Param_Out_HitLocation,Z_Param_Out_InstanceLocation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execEndRotate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndRotate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execStartRotate)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_InRate);
		P_GET_PROPERTY(FFloatProperty,Z_Param_rotateSpeed);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartRotate(Z_Param_InRate,Z_Param_rotateSpeed);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execWeaponTrace)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Length);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Radius);
		P_GET_PROPERTY(FByteProperty,Z_Param_TraceChannel);
		P_GET_TARRAY_REF(FHitResult,Z_Param_Out_OutHits);
		P_GET_PROPERTY(FByteProperty,Z_Param_DrawDebugType);
		P_GET_STRUCT(FLinearColor,Z_Param_TraceColor);
		P_GET_STRUCT(FLinearColor,Z_Param_TraceHitColor);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DrawTime);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->WeaponTrace_Implementation(Z_Param_Length,Z_Param_Radius,ETraceTypeQuery(Z_Param_TraceChannel),Z_Param_Out_OutHits,EDrawDebugTrace::Type(Z_Param_DrawDebugType),Z_Param_TraceColor,Z_Param_TraceHitColor,Z_Param_DrawTime);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execOnRotate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRotate_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URotateWeaponComponet::execInitCacheWeapons)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitCacheWeapons();
		P_NATIVE_END;
	}
	static FName NAME_URotateWeaponComponet_BeHit = FName(TEXT("BeHit"));
	void URotateWeaponComponet::BeHit(UActorComponent* Component, int32 const& Index, FVector const& HitLocation, FVector const& InstanceLocation)
	{
		RotateWeaponComponet_eventBeHit_Parms Parms;
		Parms.Component=Component;
		Parms.Index=Index;
		Parms.HitLocation=HitLocation;
		Parms.InstanceLocation=InstanceLocation;
		ProcessEvent(FindFunctionChecked(NAME_URotateWeaponComponet_BeHit),&Parms);
	}
	static FName NAME_URotateWeaponComponet_OnRotate = FName(TEXT("OnRotate"));
	void URotateWeaponComponet::OnRotate()
	{
		ProcessEvent(FindFunctionChecked(NAME_URotateWeaponComponet_OnRotate),NULL);
	}
	static FName NAME_URotateWeaponComponet_WeaponTrace = FName(TEXT("WeaponTrace"));
	void URotateWeaponComponet::WeaponTrace(float Length, float Radius, ETraceTypeQuery TraceChannel, TArray<FHitResult>& OutHits, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
	{
		RotateWeaponComponet_eventWeaponTrace_Parms Parms;
		Parms.Length=Length;
		Parms.Radius=Radius;
		Parms.TraceChannel=TraceChannel;
		Parms.OutHits=OutHits;
		Parms.DrawDebugType=DrawDebugType;
		Parms.TraceColor=TraceColor;
		Parms.TraceHitColor=TraceHitColor;
		Parms.DrawTime=DrawTime;
		ProcessEvent(FindFunctionChecked(NAME_URotateWeaponComponet_WeaponTrace),&Parms);
		OutHits=Parms.OutHits;
	}
	void URotateWeaponComponet::StaticRegisterNativesURotateWeaponComponet()
	{
		UClass* Class = URotateWeaponComponet::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddRotateWeapon", &URotateWeaponComponet::execAddRotateWeapon },
			{ "BeHit", &URotateWeaponComponet::execBeHit },
			{ "EndRotate", &URotateWeaponComponet::execEndRotate },
			{ "InitCacheWeapons", &URotateWeaponComponet::execInitCacheWeapons },
			{ "OnRotate", &URotateWeaponComponet::execOnRotate },
			{ "ReduceWeapon", &URotateWeaponComponet::execReduceWeapon },
			{ "StartRotate", &URotateWeaponComponet::execStartRotate },
			{ "UpdateTransform", &URotateWeaponComponet::execUpdateTransform },
			{ "WeaponTrace", &URotateWeaponComponet::execWeaponTrace },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics
	{
		struct RotateWeaponComponet_eventAddRotateWeapon_Parms
		{
			int32 Count;
			float Radius;
			FVector Size;
			float YawDelta;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Count;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Radius;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Size;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_YawDelta;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventAddRotateWeapon_Parms, Count), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventAddRotateWeapon_Parms, Radius), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventAddRotateWeapon_Parms, Size), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_YawDelta = { "YawDelta", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventAddRotateWeapon_Parms, YawDelta), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_Count,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_Radius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_Size,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::NewProp_YawDelta,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_Size", "1.000000,1.000000,1.000000" },
		{ "CPP_Default_YawDelta", "0.000000" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "AddRotateWeapon", nullptr, nullptr, sizeof(RotateWeaponComponet_eventAddRotateWeapon_Parms), Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Component_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Component;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HitLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_HitLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InstanceLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_InstanceLocation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Component_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Component = { "Component", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventBeHit_Parms, Component), Z_Construct_UClass_UActorComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Component_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Component_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventBeHit_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_HitLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_HitLocation = { "HitLocation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventBeHit_Parms, HitLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_HitLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_HitLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_InstanceLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_InstanceLocation = { "InstanceLocation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventBeHit_Parms, InstanceLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_InstanceLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_InstanceLocation_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Component,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_HitLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::NewProp_InstanceLocation,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_HitLocation", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_InstanceLocation", "0.000000,0.000000,0.000000" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "BeHit", nullptr, nullptr, sizeof(RotateWeaponComponet_eventBeHit_Parms), Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0CC20C00, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_BeHit()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_BeHit_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_EndRotate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_EndRotate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_EndRotate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "EndRotate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_EndRotate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_EndRotate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_EndRotate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_EndRotate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "InitCacheWeapons", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_OnRotate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_OnRotate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_OnRotate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "OnRotate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C020C00, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_OnRotate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_OnRotate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_OnRotate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_OnRotate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics
	{
		struct RotateWeaponComponet_eventReduceWeapon_Parms
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
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventReduceWeapon_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::NewProp_Index,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "ReduceWeapon", nullptr, nullptr, sizeof(RotateWeaponComponet_eventReduceWeapon_Parms), Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics
	{
		struct RotateWeaponComponet_eventStartRotate_Parms
		{
			float InRate;
			float rotateSpeed;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_InRate;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_rotateSpeed;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::NewProp_InRate = { "InRate", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventStartRotate_Parms, InRate), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::NewProp_rotateSpeed = { "rotateSpeed", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventStartRotate_Parms, rotateSpeed), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::NewProp_InRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::NewProp_rotateSpeed,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_InRate", "0.016600" },
		{ "CPP_Default_rotateSpeed", "5.000000" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "StartRotate", nullptr, nullptr, sizeof(RotateWeaponComponet_eventStartRotate_Parms), Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_StartRotate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_StartRotate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics
	{
		struct RotateWeaponComponet_eventUpdateTransform_Parms
		{
			int32 Index;
			float Radius;
			float Angle;
			FVector Size;
			float YawDelta;
			FTransform ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Radius;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Angle;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Size;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_YawDelta;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventUpdateTransform_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventUpdateTransform_Parms, Radius), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Angle = { "Angle", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventUpdateTransform_Parms, Angle), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventUpdateTransform_Parms, Size), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_YawDelta = { "YawDelta", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventUpdateTransform_Parms, YawDelta), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventUpdateTransform_Parms, ReturnValue), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Radius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Angle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_Size,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_YawDelta,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_Angle", "0.000000" },
		{ "CPP_Default_Radius", "500.000000" },
		{ "CPP_Default_Size", "1.000000,1.000000,1.000000" },
		{ "CPP_Default_YawDelta", "0.000000" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "UpdateTransform", nullptr, nullptr, sizeof(RotateWeaponComponet_eventUpdateTransform_Parms), Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics
	{
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Length;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Radius;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_TraceChannel;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_OutHits_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutHits;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DrawDebugType;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_TraceColor;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_TraceHitColor;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DrawTime;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_Length = { "Length", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, Length), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, Radius), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_TraceChannel = { "TraceChannel", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, TraceChannel), Z_Construct_UEnum_Engine_ETraceTypeQuery, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_OutHits_Inner = { "OutHits", nullptr, (EPropertyFlags)0x0000008000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_OutHits = { "OutHits", nullptr, (EPropertyFlags)0x0010008000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, OutHits), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_DrawDebugType = { "DrawDebugType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, DrawDebugType), Z_Construct_UEnum_Engine_EDrawDebugTrace, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_TraceColor = { "TraceColor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, TraceColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_TraceHitColor = { "TraceHitColor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, TraceHitColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_DrawTime = { "DrawTime", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(RotateWeaponComponet_eventWeaponTrace_Parms, DrawTime), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_Length,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_Radius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_TraceChannel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_OutHits_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_OutHits,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_DrawDebugType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_TraceColor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_TraceHitColor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::NewProp_DrawTime,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_DrawDebugType", "ForOneFrame" },
		{ "CPP_Default_DrawTime", "5.000000" },
		{ "CPP_Default_TraceColor", "(R=1.000000,G=0.000000,B=0.000000,A=1.000000)" },
		{ "CPP_Default_TraceHitColor", "(R=0.000000,G=1.000000,B=0.000000,A=1.000000)" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URotateWeaponComponet, nullptr, "WeaponTrace", nullptr, nullptr, sizeof(RotateWeaponComponet_eventWeaponTrace_Parms), Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0CC20C00, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_URotateWeaponComponet_NoRegister()
	{
		return URotateWeaponComponet::StaticClass();
	}
	struct Z_Construct_UClass_URotateWeaponComponet_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HitDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_HitDelegate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RotateDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_RotateDelegate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EndDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_EndDelegate;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Weapons_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Weapons_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Weapons;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CacheWeapons_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CacheWeapons_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_CacheWeapons;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WeaponsActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_WeaponsActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URotateWeaponComponet_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInstancedStaticMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_URotateWeaponComponet_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_URotateWeaponComponet_AddRotateWeapon, "AddRotateWeapon" }, // 2789983463
		{ &Z_Construct_UFunction_URotateWeaponComponet_BeHit, "BeHit" }, // 2259218566
		{ &Z_Construct_UFunction_URotateWeaponComponet_EndRotate, "EndRotate" }, // 4121273323
		{ &Z_Construct_UFunction_URotateWeaponComponet_InitCacheWeapons, "InitCacheWeapons" }, // 1451858105
		{ &Z_Construct_UFunction_URotateWeaponComponet_OnRotate, "OnRotate" }, // 3333148665
		{ &Z_Construct_UFunction_URotateWeaponComponet_ReduceWeapon, "ReduceWeapon" }, // 4084701837
		{ &Z_Construct_UFunction_URotateWeaponComponet_StartRotate, "StartRotate" }, // 3293962582
		{ &Z_Construct_UFunction_URotateWeaponComponet_UpdateTransform, "UpdateTransform" }, // 3040611730
		{ &Z_Construct_UFunction_URotateWeaponComponet_WeaponTrace, "WeaponTrace" }, // 1473200189
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Object Activation Components|Activation Trigger" },
		{ "IncludePath", "RotateWeapon/RotateWeaponComponet.h" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_HitDelegate_MetaData[] = {
		{ "Category", "Weapon Hit Events" },
		{ "DisplayName", "On Weapon Hit" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_HitDelegate = { "HitDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URotateWeaponComponet, HitDelegate), Z_Construct_UDelegateFunction_SomeTool_OnHitDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_HitDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_HitDelegate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_RotateDelegate_MetaData[] = {
		{ "Category", "Weapon Start Events" },
		{ "DisplayName", "On Weapon Add" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_RotateDelegate = { "RotateDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URotateWeaponComponet, RotateDelegate), Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_RotateDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_RotateDelegate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_EndDelegate_MetaData[] = {
		{ "Category", "Weapon Start Events" },
		{ "DisplayName", "On Weapon End" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_EndDelegate = { "EndDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URotateWeaponComponet, EndDelegate), Z_Construct_UDelegateFunction_SomeTool_OnRotateDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_EndDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_EndDelegate_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons_Inner = { "Weapons", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AWeaponActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons_MetaData[] = {
		{ "Category", "RotateWeaponComponet" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons = { "Weapons", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URotateWeaponComponet, Weapons), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons_Inner = { "CacheWeapons", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AWeaponActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons_MetaData[] = {
		{ "Category", "RotateWeaponComponet" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons = { "CacheWeapons", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URotateWeaponComponet, CacheWeapons), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_WeaponsActor_MetaData[] = {
		{ "Category", "RotateWeaponComponet" },
		{ "ModuleRelativePath", "RotateWeapon/RotateWeaponComponet.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_WeaponsActor = { "WeaponsActor", nullptr, (EPropertyFlags)0x0014000000000005, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(URotateWeaponComponet, WeaponsActor), Z_Construct_UClass_AWeaponActor_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_WeaponsActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_WeaponsActor_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URotateWeaponComponet_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_HitDelegate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_RotateDelegate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_EndDelegate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_Weapons,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_CacheWeapons,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URotateWeaponComponet_Statics::NewProp_WeaponsActor,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URotateWeaponComponet_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URotateWeaponComponet>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_URotateWeaponComponet_Statics::ClassParams = {
		&URotateWeaponComponet::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_URotateWeaponComponet_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_URotateWeaponComponet_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_URotateWeaponComponet_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_URotateWeaponComponet()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_URotateWeaponComponet_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(URotateWeaponComponet, 871704629);
	template<> SOMETOOL_API UClass* StaticClass<URotateWeaponComponet>()
	{
		return URotateWeaponComponet::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_URotateWeaponComponet(Z_Construct_UClass_URotateWeaponComponet, &URotateWeaponComponet::StaticClass, TEXT("/Script/SomeTool"), TEXT("URotateWeaponComponet"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(URotateWeaponComponet);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
