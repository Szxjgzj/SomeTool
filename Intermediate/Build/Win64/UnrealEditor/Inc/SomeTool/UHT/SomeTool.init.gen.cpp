// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSomeTool_init() {}
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature();
	SOMETOOL_API UFunction* Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SomeTool;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SomeTool()
	{
		if (!Z_Registration_Info_UPackage__Script_SomeTool.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SomeTool_AsyncDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SomeTool_TickEventDelegate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SomeTool",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x5AC866E1,
				0x3F970BC5,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SomeTool.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SomeTool.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SomeTool(Z_Construct_UPackage__Script_SomeTool, TEXT("/Script/SomeTool"), Z_Registration_Info_UPackage__Script_SomeTool, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x5AC866E1, 0x3F970BC5));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
