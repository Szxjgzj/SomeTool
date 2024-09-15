// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
class UActorComponent;
struct FTransform;
struct FHitResult;
struct FLinearColor;
#ifdef SOMETOOL_RotateWeaponComponet_generated_h
#error "RotateWeaponComponet.generated.h already included, missing '#pragma once' in RotateWeaponComponet.h"
#endif
#define SOMETOOL_RotateWeaponComponet_generated_h

#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_9_DELEGATE \
struct _Script_SomeTool_eventOnRotateDelegate_Parms \
{ \
	int32 Index; \
	FVector CurtLocation; \
	float LastAngle; \
	float CurtAngle; \
}; \
static inline void FOnRotateDelegate_DelegateWrapper(const FMulticastScriptDelegate& OnRotateDelegate, int32 Index, FVector CurtLocation, float LastAngle, float CurtAngle) \
{ \
	_Script_SomeTool_eventOnRotateDelegate_Parms Parms; \
	Parms.Index=Index; \
	Parms.CurtLocation=CurtLocation; \
	Parms.LastAngle=LastAngle; \
	Parms.CurtAngle=CurtAngle; \
	OnRotateDelegate.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_8_DELEGATE \
struct _Script_SomeTool_eventOnHitDelegate_Parms \
{ \
	UActorComponent* ActorComp; \
	int32 Index; \
	FVector HitLocation; \
	FVector InstanceLocation; \
}; \
static inline void FOnHitDelegate_DelegateWrapper(const FMulticastScriptDelegate& OnHitDelegate, UActorComponent* ActorComp, int32 Index, FVector HitLocation, FVector InstanceLocation) \
{ \
	_Script_SomeTool_eventOnHitDelegate_Parms Parms; \
	Parms.ActorComp=ActorComp; \
	Parms.Index=Index; \
	Parms.HitLocation=HitLocation; \
	Parms.InstanceLocation=InstanceLocation; \
	OnHitDelegate.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_SPARSE_DATA
#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_RPC_WRAPPERS \
	virtual void BeHit_Implementation(UActorComponent* Component, int32 const& Index, FVector const& HitLocation, FVector const& InstanceLocation); \
	virtual void WeaponTrace_Implementation(float Length, float Radius, ETraceTypeQuery TraceChannel, TArray<FHitResult>& OutHits, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime); \
	virtual void OnRotate_Implementation(); \
 \
	DECLARE_FUNCTION(execUpdateTransform); \
	DECLARE_FUNCTION(execReduceWeapon); \
	DECLARE_FUNCTION(execAddRotateWeapon); \
	DECLARE_FUNCTION(execBeHit); \
	DECLARE_FUNCTION(execEndRotate); \
	DECLARE_FUNCTION(execStartRotate); \
	DECLARE_FUNCTION(execWeaponTrace); \
	DECLARE_FUNCTION(execOnRotate); \
	DECLARE_FUNCTION(execInitCacheWeapons);


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void BeHit_Implementation(UActorComponent* Component, int32 const& Index, FVector const& HitLocation, FVector const& InstanceLocation); \
	virtual void WeaponTrace_Implementation(float Length, float Radius, ETraceTypeQuery TraceChannel, TArray<FHitResult>& OutHits, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime); \
	virtual void OnRotate_Implementation(); \
 \
	DECLARE_FUNCTION(execUpdateTransform); \
	DECLARE_FUNCTION(execReduceWeapon); \
	DECLARE_FUNCTION(execAddRotateWeapon); \
	DECLARE_FUNCTION(execBeHit); \
	DECLARE_FUNCTION(execEndRotate); \
	DECLARE_FUNCTION(execStartRotate); \
	DECLARE_FUNCTION(execWeaponTrace); \
	DECLARE_FUNCTION(execOnRotate); \
	DECLARE_FUNCTION(execInitCacheWeapons);


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_EVENT_PARMS \
	struct RotateWeaponComponet_eventBeHit_Parms \
	{ \
		UActorComponent* Component; \
		int32 Index; \
		FVector HitLocation; \
		FVector InstanceLocation; \
	}; \
	struct RotateWeaponComponet_eventWeaponTrace_Parms \
	{ \
		float Length; \
		float Radius; \
		TEnumAsByte<ETraceTypeQuery> TraceChannel; \
		TArray<FHitResult> OutHits; \
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType; \
		FLinearColor TraceColor; \
		FLinearColor TraceHitColor; \
		float DrawTime; \
	};


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_CALLBACK_WRAPPERS
#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURotateWeaponComponet(); \
	friend struct Z_Construct_UClass_URotateWeaponComponet_Statics; \
public: \
	DECLARE_CLASS(URotateWeaponComponet, UInstancedStaticMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(URotateWeaponComponet)


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_INCLASS \
private: \
	static void StaticRegisterNativesURotateWeaponComponet(); \
	friend struct Z_Construct_UClass_URotateWeaponComponet_Statics; \
public: \
	DECLARE_CLASS(URotateWeaponComponet, UInstancedStaticMeshComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SomeTool"), NO_API) \
	DECLARE_SERIALIZER(URotateWeaponComponet)


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URotateWeaponComponet(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URotateWeaponComponet) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URotateWeaponComponet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URotateWeaponComponet); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URotateWeaponComponet(URotateWeaponComponet&&); \
	NO_API URotateWeaponComponet(const URotateWeaponComponet&); \
public:


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URotateWeaponComponet(URotateWeaponComponet&&); \
	NO_API URotateWeaponComponet(const URotateWeaponComponet&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URotateWeaponComponet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URotateWeaponComponet); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(URotateWeaponComponet)


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_PRIVATE_PROPERTY_OFFSET
#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_11_PROLOG \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_EVENT_PARMS


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_RPC_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_CALLBACK_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_INCLASS \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_PRIVATE_PROPERTY_OFFSET \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_SPARSE_DATA \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_CALLBACK_WRAPPERS \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_INCLASS_NO_PURE_DECLS \
	P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOMETOOL_API UClass* StaticClass<class URotateWeaponComponet>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID P_555_Plugins_SomeTool_Source_SomeTool_RotateWeapon_RotateWeaponComponet_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
