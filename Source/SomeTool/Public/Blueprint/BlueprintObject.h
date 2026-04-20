// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlueprintObject.generated.h"

class ULevel;
class UObject;

/**
 * 可在蓝图中使用的 UObject 基类。
 * 当对象绑定到一个真实且可 Tick 的 World 上下文时，可用于 Delay 等潜伏节点。
 * 对普通编辑器资源对象而言意义有限；更适合运行时对象或 Editor Utility 一类的 world-backed 对象。
 */
UCLASS(Blueprintable, BlueprintType)
class SOMETOOL_API UBlueprintObject : public UObject
{
	GENERATED_BODY()

public:
	UBlueprintObject();

	// 获取世界上下文（用于支持 Delay 等需要 World 的节点）
	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category="SomeTool|Blueprint")
	void SetWorldContextObject(UObject* WorldContextObject);

	ULevel* GetLevel() const;

protected:
	// 显式缓存的世界上下文，适合外部主动注入。
	UPROPERTY()
	TWeakObjectPtr<UWorld> CachedWorld;
};
