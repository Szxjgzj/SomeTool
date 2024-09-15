// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SomeTool/RotateWeapon/WeaponActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWeaponActor() {}
// Cross Module References
	SOMETOOL_API UClass* Z_Construct_UClass_AWeaponActor_NoRegister();
	SOMETOOL_API UClass* Z_Construct_UClass_AWeaponActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_SomeTool();
// End Cross Module References
	void AWeaponActor::StaticRegisterNativesAWeaponActor()
	{
	}
	UClass* Z_Construct_UClass_AWeaponActor_NoRegister()
	{
		return AWeaponActor::StaticClass();
	}
	struct Z_Construct_UClass_AWeaponActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWeaponActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SomeTool,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "RotateWeapon/WeaponActor.h" },
		{ "ModuleRelativePath", "RotateWeapon/WeaponActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWeaponActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWeaponActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AWeaponActor_Statics::ClassParams = {
		&AWeaponActor::StaticClass,
		"Engine",
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
		METADATA_PARAMS(Z_Construct_UClass_AWeaponActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AWeaponActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AWeaponActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AWeaponActor, 2665193378);
	template<> SOMETOOL_API UClass* StaticClass<AWeaponActor>()
	{
		return AWeaponActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AWeaponActor(Z_Construct_UClass_AWeaponActor, &AWeaponActor::StaticClass, TEXT("/Script/SomeTool"), TEXT("AWeaponActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWeaponActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
