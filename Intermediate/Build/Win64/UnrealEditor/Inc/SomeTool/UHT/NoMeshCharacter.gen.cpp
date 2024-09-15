// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/NotNativeUeClass/NoMeshCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNoMeshCharacter() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	SOMETOOL_API UClass* Z_Construct_UClass_ANoMeshCharacter();
	SOMETOOL_API UClass* Z_Construct_UClass_ANoMeshCharacter_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	void ANoMeshCharacter::StaticRegisterNativesANoMeshCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANoMeshCharacter);
	UClass* Z_Construct_UClass_ANoMeshCharacter_NoRegister()
	{
		return ANoMeshCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ANoMeshCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANoMeshCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANoMeshCharacter_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANoMeshCharacter_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "NotNativeUeClass/NoMeshCharacter.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "NotNativeUeClass/NoMeshCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANoMeshCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANoMeshCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ANoMeshCharacter_Statics::ClassParams = {
		&ANoMeshCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANoMeshCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ANoMeshCharacter_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ANoMeshCharacter()
	{
		if (!Z_Registration_Info_UClass_ANoMeshCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANoMeshCharacter.OuterSingleton, Z_Construct_UClass_ANoMeshCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ANoMeshCharacter.OuterSingleton;
	}
	template<> SOMETOOL_API UClass* StaticClass<ANoMeshCharacter>()
	{
		return ANoMeshCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANoMeshCharacter);
	ANoMeshCharacter::~ANoMeshCharacter() {}
	struct Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoMeshCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoMeshCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ANoMeshCharacter, ANoMeshCharacter::StaticClass, TEXT("ANoMeshCharacter"), &Z_Registration_Info_UClass_ANoMeshCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANoMeshCharacter), 749712133U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoMeshCharacter_h_3676269772(TEXT("/Script/SomeTool"),
		Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoMeshCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_NotNativeUeClass_NoMeshCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
