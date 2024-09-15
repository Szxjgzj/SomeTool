// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "FuncLibrary/FunctionLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UShapeComponent;
#ifdef SOMETOOL_FunctionLibrary_generated_h
#error "FunctionLibrary.generated.h already included, missing '#pragma once' in FunctionLibrary.h"
#endif
#define SOMETOOL_FunctionLibrary_generated_h

#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_SPARSE_DATA
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetPointsByShape); \
	DECLARE_FUNCTION(execGetBezierPoint);


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFunctionLibrary(); \
	friend struct Z_Construct_UClass_UFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UFunctionLibrary)


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFunctionLibrary(UFunctionLibrary&&); \
	NO_API UFunctionLibrary(const UFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFunctionLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFunctionLibrary) \
	NO_API virtual ~UFunctionLibrary();


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_11_PROLOG
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_SPARSE_DATA \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_INCLASS_NO_PURE_DECLS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class UFunctionLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_FuncLibrary_FunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
