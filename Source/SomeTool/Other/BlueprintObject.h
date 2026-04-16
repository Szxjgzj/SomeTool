// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlueprintObject.generated.h"

class ULevel;

/**
 * 可在蓝图中使用的对象
 * 支持在蓝图图表中调用函数库、使用 Delay 等节点
 */
UCLASS(Blueprintable, BlueprintType)
class SOMETOOL_API UBlueprintObject : public UObject
{
	GENERATED_BODY()

public:
	UBlueprintObject();

	// 获取外部世界上下文（用于支持 Delay 等需要 World 的节点）
	virtual UWorld* GetWorld() const override;
	ULevel* GetLevel() const;

protected:
	// 存储世界上下文
	UPROPERTY()
	TWeakObjectPtr<UWorld> CachedWorld;
};
