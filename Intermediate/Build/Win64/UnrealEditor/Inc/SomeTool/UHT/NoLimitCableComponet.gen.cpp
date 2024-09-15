// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/NotNativeUeClass/NoLimitCableComponet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNoLimitCableComponet() {}
// Cross Module References
	CABLECOMPONENT_API UClass* Z_Construct_UClass_UCableComponent();
	SOMETOOL_API UClass* Z_Construct_UClass_UNoLimitCableComponet();
	SOMETOOL_API UClass* Z_Construct_UClass_UNoLimitCableComponet_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	void UNoLimitCableComponet::StaticRegisterNativesUNoLimitCableComponet()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNoLimitCableComponet);
	UClass* Z_Construct_UClass_UNoLimitCableComponet_NoRegister()
	{
		return UNoLimitCableComponet::StaticClass();
	}
	struct Z_Construct_UClass_UNoLimitCableComponet_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxNumSegments_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxNumSegments;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNoLimitCableComponet_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCableComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNoLimitCableComponet_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNoLimitCableComponet_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Object Physics Activation Components|Activation Mobility Trigger" },
		{ "IncludePath", "NotNativeUeClass/NoLimitCableComponet.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "NotNativeUeClass/NoLimitCableComponet.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNoLimitCableComponet_Statics::NewProp_MaxNumSegments_MetaData[] = {
		{ "Category", "AACable" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "NotNativeUeClass/NoLimitCableComponet.h" },
		{ "UIMax", "1000" },
		{ "UIMin", "1" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNoLimitCableComponet_Statics::NewProp_MaxNumSegments = { "MaxNumSegments", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNoLimitCableComponet, MaxNumSegments), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNoLimitCableComponet_Statics::NewProp_MaxNumSegments_MetaData), Z_Construct_UClass_UNoLimitCableComponet_Statics::NewProp_MaxNumSegments_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNoLimitCableComponet_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNoLimitCableComponet_Statics::NewProp_MaxNumSegments,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNoLimitCableComponet_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNoLimitCableComponet>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UNoLimitCableComponet_Statics::ClassParams = {
		&UNoLimitCableComponet::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UNoLimitCableComponet_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UNoLimitCableComponet_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNoLimitCableComponet_Statics::Class_MetaDataParams), Z_Construct_UClass_UNoLimitCableComponet_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNoLimitCableComponet_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UNoLimitCableComponet()
	{
		if (!Z_Registration_Info_UClass_UNoLimitCableComponet.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNoLimitCableComponet.OuterSingleton, Z_Construct_UClass_UNoLimitCableComponet_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UNoLimitCableComponet.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<UNoLimitCableComponet>()
	{
		return UNoLimitCableComponet::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNoLimitCableComponet);
	UNoLimitCableComponet::~UNoLimitCableComponet() {}
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoLimitCableComponet_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoLimitCableComponet_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UNoLimitCableComponet, UNoLimitCableComponet::StaticClass, TEXT("UNoLimitCableComponet"), &Z_Registration_Info_UClass_UNoLimitCableComponet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNoLimitCableComponet), 3146580616U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoLimitCableComponet_h_357831046(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoLimitCableComponet_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoLimitCableComponet_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
