#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecordingPluginSubsystem.h"
#include "SomeToolRecordingBlueprintLibrary.generated.h"

UCLASS()
class SOMETOOLRECORDING_API USomeToolRecordingBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Get SomeTool Recording Subsystem"))
	static URecordingPluginSubsystem* GetSomeToolRecordingSubsystem(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Start Recording", Keywords="SomeTool recorder capture video mp4"))
	static bool StartSomeToolRecording(const UObject* WorldContextObject, const FString& OutputPath, int32 FPS = 60, int32 BitrateMbps = 8);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Stop Recording", Keywords="SomeTool recorder capture video mp4"))
	static void StopSomeToolRecording(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Is Recording", Keywords="SomeTool recorder capture video mp4"))
	static bool IsSomeToolRecording(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Get Recording Resolution"))
	static FIntPoint GetSomeToolRecordingResolution(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Get Recording Frame Count"))
	static int32 GetSomeToolRecordingFrameCount(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Get Recorded Seconds"))
	static float GetSomeToolRecordedSeconds(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Get Recording Output Path"))
	static FString GetSomeToolRecordingOutputPath(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Recording|Perf", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Open Recording Performance Monitor"))
	static bool OpenSomeToolRecordingPerformanceMonitorWindow(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Recording|Perf", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Close Recording Performance Monitor"))
	static void CloseSomeToolRecordingPerformanceMonitorWindow(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="SomeTool|Recording|Perf", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Toggle Recording Performance Monitor"))
	static void ToggleSomeToolRecordingPerformanceMonitorWindow(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording|Perf", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Is Recording Performance Monitor Open"))
	static bool IsSomeToolRecordingPerformanceMonitorWindowOpen(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="SomeTool|Recording|Perf", meta=(WorldContext="WorldContextObject", DefaultToSelf="WorldContextObject", DisplayName="Get Recording Performance Stats"))
	static FRecordingPerformanceStats GetSomeToolRecordingPerformanceStats(const UObject* WorldContextObject);
};
