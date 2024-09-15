// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GeometryTool/GeometryInstance.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UShapeComponent;
#ifdef SOMETOOL_GeometryInstance_generated_h
#error "GeometryInstance.generated.h already included, missing '#pragma once' in GeometryInstance.h"
#endif
#define SOMETOOL_GeometryInstance_generated_h

#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetPointsByCircle); \
	DECLARE_FUNCTION(execGetPointsByShape); \
	DECLARE_FUNCTION(execGetPointsByCustomRect);


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_ACCESSORS
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGeometryInstance(); \
	friend struct Z_Construct_UClass_UGeometryInstance_Statics; \
public: \
	DECLARE_CLASS(UGeometryInstance, UInstancedStaticMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UGeometryInstance)


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGeometryInstance(UGeometryInstance&&); \
	NO_API UGeometryInstance(const UGeometryInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGeometryInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGeometryInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGeometryInstance) \
	NO_API virtual ~UGeometryInstance();


#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_13_PROLOG
#define FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_ACCESSORS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_INCLASS_NO_PURE_DECLS \
	FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class UGeometryInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_P_53_b_Plugins_SpineTemp_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
