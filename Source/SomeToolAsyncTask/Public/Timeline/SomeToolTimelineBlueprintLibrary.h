#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SomeToolTimelineBlueprintLibrary.generated.h"

class UCurveFloat;
class USomeToolFloatCurveTimelineHandle;

UCLASS()
class SOMETOOLASYNCTASK_API USomeToolTimelineBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		Category="SomeTool|Timeline",
		meta=(
			WorldContext="WorldContextObject",
			DefaultToSelf="WorldContextObject",
			DisplayName="Create Float Curve Timeline Handle"))
	static USomeToolFloatCurveTimelineHandle* CreateFloatCurveTimelineHandle(
		UObject* WorldContextObject,
		UCurveFloat* CurveAsset = nullptr);
};
