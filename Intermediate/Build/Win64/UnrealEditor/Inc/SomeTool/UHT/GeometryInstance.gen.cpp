// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/GeometryTool/GeometryInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGeometryInstance() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent();
	ENGINE_API UClass* Z_Construct_UClass_UShapeComponent_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_UGeometryInstance();
	SOMETOOL_API UClass* Z_Construct_UClass_UGeometryInstance_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	DEFINE_FUNCTION(UGeometryInstance::execGetPointsByCircle)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_InitCount);
		P_GET_PROPERTY(FFloatProperty,Z_Param_InitAngle);
		P_GET_PROPERTY(FIntProperty,Z_Param_Level);
		P_GET_PROPERTY(FFloatProperty,Z_Param_RadiusDelta);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTransform>*)Z_Param__Result=P_THIS->GetPointsByCircle(Z_Param_InitCount,Z_Param_InitAngle,Z_Param_Level,Z_Param_RadiusDelta);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeometryInstance::execGetPointsByShape)
	{
		P_GET_OBJECT(UShapeComponent,Z_Param_Shape);
		P_GET_UBOOL(Z_Param_bIsAddInstance);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Distance);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Noise);
		P_GET_UBOOL(Z_Param_bIsUseLookAtOrigin);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_A);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_B);
		P_GET_UBOOL(Z_Param_bIsUseRandomRotation);
		P_GET_STRUCT(FVector,Z_Param_Size_A);
		P_GET_STRUCT(FVector,Z_Param_Size_B);
		P_GET_UBOOL(Z_Param_bIsUseRandomSize);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_Delta);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTransform>*)Z_Param__Result=P_THIS->GetPointsByShape(Z_Param_Shape,Z_Param_bIsAddInstance,Z_Param_Distance,Z_Param_Noise,Z_Param_bIsUseLookAtOrigin,Z_Param_Rotator_A,Z_Param_Rotator_B,Z_Param_bIsUseRandomRotation,Z_Param_Size_A,Z_Param_Size_B,Z_Param_bIsUseRandomSize,Z_Param_Rotator_Delta);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeometryInstance::execGetPointsByCustomRect)
	{
		P_GET_STRUCT(FTransform,Z_Param_OriginTransform);
		P_GET_STRUCT(FVector,Z_Param_Counts3D);
		P_GET_STRUCT(FVector,Z_Param_Distance3D);
		P_GET_UBOOL(Z_Param_bIsUseWorldSpace);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_A);
		P_GET_STRUCT(FRotator,Z_Param_Rotator_B);
		P_GET_UBOOL(Z_Param_bIsUseRandomRotation);
		P_GET_STRUCT(FVector,Z_Param_Size_A);
		P_GET_STRUCT(FVector,Z_Param_Size_B);
		P_GET_UBOOL(Z_Param_bIsUseRandomSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetPointsByCustomRect(Z_Param_OriginTransform,Z_Param_Counts3D,Z_Param_Distance3D,Z_Param_bIsUseWorldSpace,Z_Param_Rotator_A,Z_Param_Rotator_B,Z_Param_bIsUseRandomRotation,Z_Param_Size_A,Z_Param_Size_B,Z_Param_bIsUseRandomSize);
		P_NATIVE_END;
	}
	void UGeometryInstance::StaticRegisterNativesUGeometryInstance()
	{
		UClass* Class = UGeometryInstance::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetPointsByCircle", &UGeometryInstance::execGetPointsByCircle },
			{ "GetPointsByCustomRect", &UGeometryInstance::execGetPointsByCustomRect },
			{ "GetPointsByShape", &UGeometryInstance::execGetPointsByShape },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics
	{
		struct GeometryInstance_eventGetPointsByCircle_Parms
		{
			int32 InitCount;
			float InitAngle;
			int32 Level;
			float RadiusDelta;
			TArray<FTransform> ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_InitCount;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_InitAngle;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Level;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RadiusDelta;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_InitCount = { "InitCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCircle_Parms, InitCount), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_InitAngle = { "InitAngle", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCircle_Parms, InitAngle), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_Level = { "Level", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCircle_Parms, Level), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_RadiusDelta = { "RadiusDelta", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCircle_Parms, RadiusDelta), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCircle_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_InitCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_InitAngle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_Level,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_RadiusDelta,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::Function_MetaDataParams[] = {
		{ "Category", "Geometry Instance Tool" },
		{ "CPP_Default_InitAngle", "0.000000" },
		{ "CPP_Default_InitCount", "5" },
		{ "CPP_Default_Level", "3" },
		{ "CPP_Default_RadiusDelta", "100.000000" },
		{ "ModuleRelativePath", "GeometryTool/GeometryInstance.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeometryInstance, nullptr, "GetPointsByCircle", nullptr, nullptr, Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::GeometryInstance_eventGetPointsByCircle_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::GeometryInstance_eventGetPointsByCircle_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics
	{
		struct GeometryInstance_eventGetPointsByCustomRect_Parms
		{
			FTransform OriginTransform;
			FVector Counts3D;
			FVector Distance3D;
			bool bIsUseWorldSpace;
			FRotator Rotator_A;
			FRotator Rotator_B;
			bool bIsUseRandomRotation;
			FVector Size_A;
			FVector Size_B;
			bool bIsUseRandomSize;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_OriginTransform;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Counts3D;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Distance3D;
		static void NewProp_bIsUseWorldSpace_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUseWorldSpace;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Rotator_A;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Rotator_B;
		static void NewProp_bIsUseRandomRotation_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUseRandomRotation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Size_A;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Size_B;
		static void NewProp_bIsUseRandomSize_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUseRandomSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_OriginTransform = { "OriginTransform", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, OriginTransform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Counts3D = { "Counts3D", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, Counts3D), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Distance3D = { "Distance3D", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, Distance3D), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseWorldSpace_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByCustomRect_Parms*)Obj)->bIsUseWorldSpace = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseWorldSpace = { "bIsUseWorldSpace", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByCustomRect_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseWorldSpace_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Rotator_A = { "Rotator_A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, Rotator_A), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Rotator_B = { "Rotator_B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, Rotator_B), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomRotation_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByCustomRect_Parms*)Obj)->bIsUseRandomRotation = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomRotation = { "bIsUseRandomRotation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByCustomRect_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomRotation_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Size_A = { "Size_A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, Size_A), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Size_B = { "Size_B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByCustomRect_Parms, Size_B), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomSize_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByCustomRect_Parms*)Obj)->bIsUseRandomSize = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomSize = { "bIsUseRandomSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByCustomRect_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomSize_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_OriginTransform,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Counts3D,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Distance3D,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseWorldSpace,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Rotator_A,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Rotator_B,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Size_A,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_Size_B,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::NewProp_bIsUseRandomSize,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::Function_MetaDataParams[] = {
		{ "Category", "Geometry Instance Tool" },
		{ "CPP_Default_bIsUseRandomRotation", "false" },
		{ "CPP_Default_bIsUseRandomSize", "false" },
		{ "CPP_Default_bIsUseWorldSpace", "true" },
		{ "CPP_Default_Counts3D", "5.000000,5.000000,1.000000" },
		{ "CPP_Default_Distance3D", "100.000000,100.000000,100.000000" },
		{ "CPP_Default_Rotator_A", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Rotator_B", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Size_A", "1.000000,1.000000,1.000000" },
		{ "CPP_Default_Size_B", "1.000000,1.000000,1.000000" },
		{ "ModuleRelativePath", "GeometryTool/GeometryInstance.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeometryInstance, nullptr, "GetPointsByCustomRect", nullptr, nullptr, Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::GeometryInstance_eventGetPointsByCustomRect_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::GeometryInstance_eventGetPointsByCustomRect_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics
	{
		struct GeometryInstance_eventGetPointsByShape_Parms
		{
			UShapeComponent* Shape;
			bool bIsAddInstance;
			float Distance;
			float Noise;
			bool bIsUseLookAtOrigin;
			FRotator Rotator_A;
			FRotator Rotator_B;
			bool bIsUseRandomRotation;
			FVector Size_A;
			FVector Size_B;
			bool bIsUseRandomSize;
			FRotator Rotator_Delta;
			TArray<FTransform> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Shape_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Shape;
		static void NewProp_bIsAddInstance_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsAddInstance;
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_Rotator_Delta;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Shape_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Shape = { "Shape", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Shape), Z_Construct_UClass_UShapeComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Shape_MetaData), Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Shape_MetaData) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsAddInstance_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByShape_Parms*)Obj)->bIsAddInstance = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsAddInstance = { "bIsAddInstance", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsAddInstance_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Distance = { "Distance", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Distance), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Noise = { "Noise", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Noise), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByShape_Parms*)Obj)->bIsUseLookAtOrigin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin = { "bIsUseLookAtOrigin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Rotator_A = { "Rotator_A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Rotator_A), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Rotator_B = { "Rotator_B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Rotator_B), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByShape_Parms*)Obj)->bIsUseRandomRotation = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation = { "bIsUseRandomRotation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Size_A = { "Size_A", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Size_A), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Size_B = { "Size_B", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Size_B), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomSize_SetBit(void* Obj)
	{
		((GeometryInstance_eventGetPointsByShape_Parms*)Obj)->bIsUseRandomSize = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomSize = { "bIsUseRandomSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GeometryInstance_eventGetPointsByShape_Parms), &Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomSize_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Rotator_Delta = { "Rotator_Delta", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, Rotator_Delta), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeometryInstance_eventGetPointsByShape_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Shape,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsAddInstance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Distance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Noise,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseLookAtOrigin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Rotator_A,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Rotator_B,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Size_A,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Size_B,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_bIsUseRandomSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_Rotator_Delta,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::Function_MetaDataParams[] = {
		{ "Category", "Geometry Instance Tool" },
		{ "CPP_Default_bIsAddInstance", "true" },
		{ "CPP_Default_bIsUseLookAtOrigin", "false" },
		{ "CPP_Default_bIsUseRandomRotation", "false" },
		{ "CPP_Default_bIsUseRandomSize", "false" },
		{ "CPP_Default_Distance", "100.000000" },
		{ "CPP_Default_Noise", "0.000000" },
		{ "CPP_Default_Rotator_A", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Rotator_B", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Rotator_Delta", "0.000000,0.000000,0.000000" },
		{ "CPP_Default_Size_A", "1.000000,1.000000,1.000000" },
		{ "CPP_Default_Size_B", "1.000000,1.000000,1.000000" },
		{ "ModuleRelativePath", "GeometryTool/GeometryInstance.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeometryInstance, nullptr, "GetPointsByShape", nullptr, nullptr, Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::GeometryInstance_eventGetPointsByShape_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::GeometryInstance_eventGetPointsByShape_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UGeometryInstance_GetPointsByShape()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGeometryInstance_GetPointsByShape_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGeometryInstance);
	UClass* Z_Construct_UClass_UGeometryInstance_NoRegister()
	{
		return UGeometryInstance::StaticClass();
	}
	struct Z_Construct_UClass_UGeometryInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGeometryInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInstancedStaticMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGeometryInstance_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UGeometryInstance_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGeometryInstance_GetPointsByCircle, "GetPointsByCircle" }, // 2053362142
		{ &Z_Construct_UFunction_UGeometryInstance_GetPointsByCustomRect, "GetPointsByCustomRect" }, // 1628725583
		{ &Z_Construct_UFunction_UGeometryInstance_GetPointsByShape, "GetPointsByShape" }, // 1400289159
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGeometryInstance_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGeometryInstance_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object Activation Components|Activation Trigger" },
		{ "IncludePath", "GeometryTool/GeometryInstance.h" },
		{ "ModuleRelativePath", "GeometryTool/GeometryInstance.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGeometryInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGeometryInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGeometryInstance_Statics::ClassParams = {
		&UGeometryInstance::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x00B010A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGeometryInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UGeometryInstance_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UGeometryInstance()
	{
		if (!Z_Registration_Info_UClass_UGeometryInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGeometryInstance.OuterSingleton, Z_Construct_UClass_UGeometryInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGeometryInstance.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<UGeometryInstance>()
	{
		return UGeometryInstance::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGeometryInstance);
	UGeometryInstance::~UGeometryInstance() {}
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGeometryInstance, UGeometryInstance::StaticClass, TEXT("UGeometryInstance"), &Z_Registration_Info_UClass_UGeometryInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGeometryInstance), 3200067632U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_2430942122(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
