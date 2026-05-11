#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "HAL/PlatformProcess.h"
#include "Widgets/SCompoundWidget.h"

class SMultiLineEditableTextBox;
class SEditableTextBox;
class SVerticalBox;
class SWidget;

class SSomeToolPakManifestBuilder : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSomeToolPakManifestBuilder) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	enum class EBuildMode : uint8
	{
		GamePak,
		MainPackage
	};

	struct FMainPackagePluginOption
	{
		FString Name;
		FString DisplayName;
		FString SourceText;
		FString Note;
		bool bEnabled = false;
		bool bRecommended = false;
	};

	FReply BuildPak();
	FReply BuildMainPackage();
	void HandlePakEntryChanged(const FAssetData& AssetData);
	FString GetPakEntryObjectPath() const;
	FString GetSelectedPakId() const;
	void RefreshMainPackagePluginOptions();
	TSharedRef<SWidget> MakeMainPackagePluginList();
	ECheckBoxState IsMainPackagePluginChecked(FString PluginName) const;
	void HandleMainPackagePluginChecked(ECheckBoxState NewState, FString PluginName);
	TArray<FString> GetSelectedMainPackagePlugins() const;
	FString GetSelectedMainPackagePluginsText() const;
	bool ApplyMainPackagePluginWhitelist(const FString& ProjectFilePath, const TArray<FString>& EnabledPlugins, FString& OutOriginalProjectText, FString& OutErrorText) const;
	bool RestoreMainPackageProjectFile(FString& OutErrorText);
	FString GetBuildTaskDisplayName() const;
	EActiveTimerReturnType TickBuildProcess(double InCurrentTime, float InDeltaTime);
	void FinishBuildProcess(int32 ReturnCode);
	void ResetBuildProcess();
	bool IsBuildRunning() const;
	FText GetLogText() const;
	FText GetUnrealPakLogText() const;
	TOptional<float> GetBuildProgressPercent() const;
	FText GetBuildProgressText() const;
	void SetBuildProgress(float Percent, const FString& StatusText);
	void UpdateBuildProgressFromLog(const FString& BuildLogText);

	TSharedPtr<SEditableTextBox> OutputDirectoryTextBox;
	TSharedPtr<SVerticalBox> MainPackagePluginListBox;

	FAssetData SelectedPakEntryAsset;
	TArray<FMainPackagePluginOption> MainPackagePlugins;
	EBuildMode BuildMode = EBuildMode::GamePak;
	FProcHandle BuildProcHandle;
	uint32 BuildProcessId = 0;
	FString BuildPakId;
	FString BuildOutputDirectory;
	FString BuildLogFilePath;
	FString BuildProjectFilePath;
	FString BuildOriginalProjectText;
	double BuildStartTime = 0.0;
	float BuildProgress = 0.0f;
	FString BuildProgressText;

	FString LogText;
	FString UnrealPakLogText;
};
