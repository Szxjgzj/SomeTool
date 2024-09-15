// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/FuncLibrary/FunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFunctionLibrary() {}
// Cross Module References
	SOMETOOL_API UClass* Z_Construct_UClass_UFunctionLibrary_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
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
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Points_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Points_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Points;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Progress;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_Inner = { "Points", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points = { "Points", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FunctionLibrary_eventGetBezierPoint_Parms, Points), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Progress = { "Progress", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FunctionLibrary_eventGetBezierPoint_Parms, Progress), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000582, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FunctionLibrary_eventGetBezierPoint_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Points,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_Progress,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "FuncLibrary/FunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFunctionLibrary, nullptr, "GetBezierPoint", nullptr, nullptr, sizeof(FunctionLibrary_eventGetBezierPoint_Parms), Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFunctionLibrary_NoRegister()
	{
		return UFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFunctionLibrary_GetBezierPoint, "GetBezierPoint" }, // 2685671498
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "FuncLibrary/FunctionLibrary.h" },
		{ "ModuleRelativePath", "FuncLibrary/FunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFunctionLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFunctionLibrary_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UFunctionLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFunctionLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFunctionLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFunctionLibrary, 3089569156);
	template<> SOMETOOL_API UClass* StaticClass<UFunctionLibrary>()
	{
		return UFunctionLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFunctionLibrary(Z_Construct_UClass_UFunctionLibrary, &UFunctionLibrary::StaticClass, TEXT("/Script/SomeTool"), TEXT("UFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
