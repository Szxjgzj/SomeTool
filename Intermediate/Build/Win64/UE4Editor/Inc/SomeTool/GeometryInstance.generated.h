// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UShapeComponent;
struct FRotator;
struct FVector;
struct FTransform;
#ifdef SOMETOOL_GeometryInstance_generated_h
#error "GeometryInstance.generated.h already included, missing '#pragma once' in GeometryInstance.h"
#endif
#define SOMETOOL_GeometryInstance_generated_h

#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA
#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetPointsByShape); \
	DECLARE_FUNCTION(execGetPointsByCustomRect);


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetPointsByShape); \
	DECLARE_FUNCTION(execGetPointsByCustomRect);


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGeometryInstance(); \
	friend struct Z_Construct_UClass_UGeometryInstance_Statics; \
public: \
	DECLARE_CLASS(UGeometryInstance, UInstancedStaticMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UGeometryInstance)


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUGeometryInstance(); \
	friend struct Z_Construct_UClass_UGeometryInstance_Statics; \
public: \
	DECLARE_CLASS(UGeometryInstance, UInstancedStaticMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(UGeometryInstance)


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGeometryInstance(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGeometryInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGeometryInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGeometryInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGeometryInstance(UGeometryInstance&&); \
	NO_API UGeometryInstance(const UGeometryInstance&); \
public:


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGeometryInstance(UGeometryInstance&&); \
	NO_API UGeometryInstance(const UGeometryInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGeometryInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGeometryInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGeometryInstance)


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_PRIVATE_PROPERTY_OFFSET
#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_13_PROLOG
#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_RPC_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_INCLASS \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_INCLASS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class UGeometryInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID P_555_Plugins_SomeTool_Source_SomeTool_GeometryTool_GeometryInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
