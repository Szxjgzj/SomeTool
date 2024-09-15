// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/FuncLibrary/FunctionLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFunctionLibrary() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UShapeComponent_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UFunctionLibrary();
	SOMETOOL_API UClass* Z_Construct_UClass_UFunctionLibrary_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	DEFINE_FUNCTION(UFunctionLibrary::execGetPointsByShape)
	{
		P_GET_OBJECT(UShapeComponent,Z_Param_Shape);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Distance);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Noise);
		P_GET_UBOOL(Z_Param_bIsUseLookAtOrigin);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_A);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_B);
		P_GET_UBOOL(Z_Param_bIsUseRandomRotation);
		P_GET_STRUCT(FVector,Z_Param_Size_A);
		P_GET_STRUCT(FVector,Z_Param_Size_B);
		P_GET_UBOOL(Z_Param_bIsUseRandomSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTransform>*)Z_Param__Result=UFunctionLibrary::GetPointsByShape(Z_Param_Shape,Z_Param_Distance,Z_Param_Noise,Z_Param_bIsUseLookAtOrigin,Z_Param_Rotator_A,Z_Param_Rotator_B,Z_Param_bIsUseRandomRotation,Z_Param_Size_A,Z_Param_Size_B,Z_Param_bIsUseRandomSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFunctionLibrary::execGetBezierPoint)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Points);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Progress);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=UFunctionLibrary::GetBezierPoint(Z_Param_Out_Points,Z_Param_Progress);
		P_NATIVE_END;
	}
	void UFunctionLibrary::StaticRegisterNativesUFunctionLibrary()
	{
		UClass* Class = UFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetBezierPoint", &UFunctionLibrary::execGetBezierPoint },
			{ "GetPointsByShape", &UFunctionLibrary::execGetPointsByShape },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics
	{
		struct FunctionLibrary_eventGetBezierPoint_Parms
		{
			TArray<FVector> Points;
			float Progress;
			FVector ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_Points_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Points_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Points;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Progress;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_Inner = { "Points", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points = { "Points", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetBezierPoint_Parms, Points), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_MetaData), Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_MetaData) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Progress = { "Progress", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetBezierPoint_Parms, Progress), METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000582, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetBezierPoint_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue_MetaData), Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Progress,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::Function_MetaDataParams[] = {
		{ "Category", "Some Tool Func" },
		{ "ModuleRelativePath", "FuncLibrary/FunctionLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFunctionLibrary, nullptr, "GetBezierPoint", nullptr, nullptr, Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers), sizeof(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::FunctionLibrary_eventGetBezierPoint_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::FunctionLibrary_eventGetBezierPoint_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics
	{
		struct FunctionLibrary_eventGetPointsByShape_Parms
		{
			UShapeComponent* Shape;
			float Distance;
			float Noise;
			bool bIsUseLookAtOrigin;
			FRotator Rotator_A;
			FRotator Rotator_B;
			bool bIsUseRandomRotation;
			FVector Size_A;
			FVector Size_B;
			bool bIsUseRandomSize;
			TArray<FTransform> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Shape_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Shape;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Distance;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Noise;
		static void NewProp_bIsUseLookAtOrigin_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUseLookAtOrigin;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Rotator_A;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Rotator_B;
		static void NewProp_bIsUseRandomRotation_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUseRandomRotation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Size_A;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Size_B;
		static void NewProp_bIsUseRandomSize_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUseRandomSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Shape_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Shape = { "Shape", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Shape), Z_Construct_UClass_UShapeComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Shape_MetaData), Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Shape_MetaData) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Distance = { "Distance", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Distance), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Noise = { "Noise", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Noise), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin_SetBit(void* Obj)
	{
		((FunctionLibrary_eventGetPointsByShape_Parms*)Obj)->bIsUseLookAtOrigin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin = { "bIsUseLookAtOrigin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FunctionLibrary_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Rotator_A = { "Rotator_A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Rotator_A), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Rotator_B = { "Rotator_B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Rotator_B), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation_SetBit(void* Obj)
	{
		((FunctionLibrary_eventGetPointsByShape_Parms*)Obj)->bIsUseRandomRotation = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation = { "bIsUseRandomRotation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FunctionLibrary_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Size_A = { "Size_A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Size_A), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Size_B = { "Size_B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, Size_B), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomSize_SetBit(void* Obj)
	{
		((FunctionLibrary_eventGetPointsByShape_Parms*)Obj)->bIsUseRandomSize = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomSize = { "bIsUseRandomSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FunctionLibrary_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomSize_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FunctionLibrary_eventGetPointsByShape_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Shape,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Distance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Noise,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Rotator_A,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Rotator_B,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Size_A,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_Size_B,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_bIsUseRandomSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::Function_MetaDataParams[] = {
		{ "Category", "Some Tool Func" },
		{ "CPP_Default_bIsUseLookAtOrigin", "false" },
		{ "CPP_Default_bIsUseRandomRotation", "false" },
		{ "CPP_Default_bIsUseRandomSize", "false" },
		{ "CPP_Default_Distance", "100.000000" },
		{ "CPP_Default_Noise", "0.000000" },
		{ "CPP_Default_Rotator_A", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Rotator_B", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Size_A", "1.000000,1.000000,1.000000" },
		{ "CPP_Default_Size_B", "1.000000,1.000000,1.000000" },
		{ "ModuleRelativePath", "FuncLibrary/FunctionLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFunctionLibrary, nullptr, "GetPointsByShape", nullptr, nullptr, Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::PropPointers), sizeof(Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::FunctionLibrary_eventGetPointsByShape_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04842401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::Function_MetaDataParams), Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::FunctionLibrary_eventGetPointsByShape_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFunctionLibrary);
	UClass* Z_Construct_UClass_UFunctionLibrary_NoRegister()
	{
		return UFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFunctionLibrary_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint, "GetBezierPoint" }, // 3657028296
		{ &Z_Construct_UFunction_UFunctionLibrary_GetPointsByShape, "GetPointsByShape" }, // 1748787878
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFunctionLibrary_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFunctionLibrary_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "FuncLibrary/FunctionLibrary.h" },
		{ "ModuleRelativePath", "FuncLibrary/FunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFunctionLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFunctionLibrary_Statics::ClassParams = {
		&UFunctionLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFunctionLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UFunctionLibrary_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UFunctionLibrary()
	{
		if (!Z_Registration_Info_UClass_UFunctionLibrary.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFunctionLibrary.OuterSingleton, Z_Construct_UClass_UFunctionLibrary_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFunctionLibrary.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<UFunctionLibrary>()
	{
		return UFunctionLibrary::StaticClass();
	}
	UFunctionLibrary::UFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFunctionLibrary);
	UFunctionLibrary::~UFunctionLibrary() {}
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFunctionLibrary, UFunctionLibrary::StaticClass, TEXT("UFunctionLibrary"), &Z_Registration_Info_UClass_UFunctionLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFunctionLibrary), 1556287199U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_327671497(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
