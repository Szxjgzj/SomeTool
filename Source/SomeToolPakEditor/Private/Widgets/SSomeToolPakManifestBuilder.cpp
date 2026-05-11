#include "Widgets/SSomeToolPakManifestBuilder.h"

#include "DesktopPlatformModule.h"
#include "Dom/JsonObject.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "IDesktopPlatform.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "Pak/SomeToolPakEditorBlueprintLibrary.h"
#include "Pak/SomeToolPakPrimaryAsset.h"
#include "PropertyCustomizationHelpers.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SSomeToolPakManifestBuilder"

namespace
{
TSharedRef<SWidget> MakeLabeledTextBox(
	const FText& Label,
	const TSharedRef<SEditableTextBox>& TextBox)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(Label)
			.MinDesiredWidth(120.0f)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			TextBox
		];
}

TSharedRef<SWidget> MakeLabeledWidget(
	const FText& Label,
	const TSharedRef<SWidget>& Widget)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(Label)
			.MinDesiredWidth(120.0f)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			Widget
		];
}

FString QuoteSlateCommandArgument(const FString& Value)
{
	return FString::Printf(TEXT("\"%s\""), *Value);
}

FString MakeUniqueBuildLogFilePath(const FString& Directory, const FString& BaseName)
{
	const FString Timestamp = FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S"));
	return FPaths::Combine(Directory, FString::Printf(TEXT("%s.%s.log"), *BaseName, *Timestamp));
}

bool IsRuntimePluginForWin64Shipping(const TSharedRef<IPlugin>& Plugin)
{
	const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
	if (!Descriptor.SupportsTargetPlatform(TEXT("Win64")))
	{
		return false;
	}

	for (const FModuleDescriptor& Module : Descriptor.Modules)
	{
		if (Module.IsCompiledInConfiguration(
			TEXT("Win64"),
			EBuildConfiguration::Shipping,
			FString(),
			EBuildTargetType::Game,
			false,
			true))
		{
			return true;
		}
	}

	return Descriptor.Modules.IsEmpty() && Descriptor.bCanContainContent;
}

FString GetPluginSourceText(const TSharedRef<IPlugin>& Plugin)
{
	return Plugin->GetLoadedFrom() == EPluginLoadedFrom::Project ? TEXT("项目") : TEXT("引擎");
}

FString GetKnownMainPackagePluginNote(const FString& PluginName)
{
	if (PluginName == TEXT("SomeTool"))
	{
		return TEXT("项目工具 API，默认启用");
	}
	if (PluginName == TEXT("Angelscript"))
	{
		return TEXT("脚本运行时，默认启用");
	}
	if (PluginName == TEXT("AngelscriptEnhancedInput"))
	{
		return TEXT("Angelscript 的 EnhancedInput 绑定");
	}
	if (PluginName == TEXT("EnhancedInput"))
	{
		return TEXT("UE 增强输入，普通游戏默认启用");
	}
	if (PluginName == TEXT("HardwareEncoders"))
	{
		return TEXT("录制硬件编码，空主包默认关闭");
	}
	if (PluginName == TEXT("OpenImageDenoise"))
	{
		return TEXT("路径追踪降噪，空游戏不需要");
	}
	return FString();
}

bool IsRecommendedMainPackagePlugin(const FString& PluginName)
{
	return PluginName == TEXT("Angelscript")
		|| PluginName == TEXT("EnhancedInput")
		|| PluginName == TEXT("SomeTool");
}

bool ShouldAlwaysShowMainPackagePlugin(const FString& PluginName)
{
	static const TSet<FString> KnownPlugins =
	{
		TEXT("SomeTool"),
		TEXT("Angelscript"),
		TEXT("AngelscriptEnhancedInput"),
		TEXT("EnhancedInput"),
		TEXT("HardwareEncoders"),
		TEXT("OpenImageDenoise")
	};
	return KnownPlugins.Contains(PluginName);
}

FString JoinPluginNames(const TArray<FString>& PluginNames)
{
	return FString::Join(PluginNames, TEXT(","));
}

FString GetAutomationToolLogFilePath()
{
	const FString AppDataDirectory = FPlatformMisc::GetEnvironmentVariable(TEXT("APPDATA"));
	if (AppDataDirectory.IsEmpty())
	{
		return FString();
	}

	FString EngineRootDirectory = FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
	FPaths::NormalizeDirectoryName(EngineRootDirectory);
	EngineRootDirectory = FPaths::GetPath(EngineRootDirectory);

	FString SafeEngineRoot = EngineRootDirectory;
	SafeEngineRoot.ReplaceInline(TEXT(":"), TEXT(""));
	SafeEngineRoot.ReplaceInline(TEXT("\\"), TEXT("+"));
	SafeEngineRoot.ReplaceInline(TEXT("/"), TEXT("+"));
	while (SafeEngineRoot.EndsWith(TEXT("+")))
	{
		SafeEngineRoot.LeftChopInline(1);
	}

	return FPaths::Combine(
		AppDataDirectory,
		TEXT("Unreal Engine"),
		TEXT("AutomationTool"),
		TEXT("Logs"),
		SafeEngineRoot,
		TEXT("Log.txt"));
}

FString ParsePakIdFromEntryName(const FString& AssetName)
{
	static const FString Prefix = TEXT("DA_PakEntry_");
	return AssetName.StartsWith(Prefix) ? AssetName.RightChop(Prefix.Len()) : FString();
}

void DeleteWidgetBuildFilesByPattern(const FString& Directory, const FString& Pattern)
{
	TArray<FString> Filenames;
	IFileManager::Get().FindFiles(Filenames, *FPaths::Combine(Directory, Pattern), true, false);
	for (const FString& Filename : Filenames)
	{
		IFileManager::Get().Delete(*FPaths::Combine(Directory, Filename), false, true);
	}
}

void CleanWidgetSuccessfulBuildOutputs(const FString& OutputDirectory, const FString& PakIdString)
{
	const FString NormalizedOutputDirectory = FPaths::ConvertRelativePathToFull(OutputDirectory);
	const FString TempDirectory = FPaths::Combine(NormalizedOutputDirectory, TEXT(".BuildTemp"), PakIdString);
	IFileManager::Get().DeleteDirectory(*TempDirectory, false, true);
	IFileManager::Get().DeleteDirectory(*FPaths::Combine(NormalizedOutputDirectory, TEXT(".BuildTemp")), false, false);

	DeleteWidgetBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".build*.log"));
	DeleteWidgetBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".manual-build*.log"));
	DeleteWidgetBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".cook.log"));
	DeleteWidgetBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".unrealpak.log"));
	DeleteWidgetBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".resources.txt"));
	DeleteWidgetBuildFilesByPattern(NormalizedOutputDirectory, PakIdString + TEXT(".paklist.txt"));
}

FString GetGamePakBuildTempDirectory(const FString& OutputDirectory, const FString& PakIdString)
{
	return FPaths::Combine(OutputDirectory, TEXT(".BuildTemp"), PakIdString);
}

FString GetGamePakCookLogPath(const FString& OutputDirectory, const FString& PakIdString)
{
	return FPaths::Combine(GetGamePakBuildTempDirectory(OutputDirectory, PakIdString), PakIdString + TEXT(".cook.log"));
}

FString GetGamePakUnrealPakLogPath(const FString& OutputDirectory, const FString& PakIdString)
{
	return FPaths::Combine(GetGamePakBuildTempDirectory(OutputDirectory, PakIdString), PakIdString + TEXT(".unrealpak.log"));
}

bool LoadLogTail(const FString& FilePath, FString& OutText, const int32 MaxChars)
{
	OutText.Reset();
	if (FilePath.IsEmpty() || !FFileHelper::LoadFileToString(OutText, *FilePath))
	{
		return false;
	}

	if (OutText.Len() > MaxChars)
	{
		OutText = OutText.Right(MaxChars);
	}
	return true;
}

FString MakeStageLogText(const FString& StageName, const FString& FilePath, const FString& TailText)
{
	return FString::Printf(
		TEXT("%s 实时日志\n文件: %s\n\n%s"),
		*StageName,
		*FilePath,
		*TailText);
}
}

void SSomeToolPakManifestBuilder::Construct(const FArguments& InArgs)
{
	RefreshMainPackagePluginOptions();
	LogText = TEXT("分包：选择 Pak 入口后生成一个 Pak 和一个清单。\n主包：选择输出目录后按 Windows Shipping 构建完整主程序。");
	BuildProgressText = TEXT("未开始");

	ChildSlot
	[
		SNew(SBorder)
		.Padding(12.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Title", "SomeTool Pak 构建工具"))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 6.0f)
			[
				MakeLabeledWidget(
					LOCTEXT("PakEntryLabel", "Pak 入口"),
					SNew(SObjectPropertyEntryBox)
					.AllowedClass(USomeToolPakPrimaryAsset::StaticClass())
					.ObjectPath(this, &SSomeToolPakManifestBuilder::GetPakEntryObjectPath)
					.OnObjectChanged(this, &SSomeToolPakManifestBuilder::HandlePakEntryChanged)
					.AllowClear(true)
					.DisplayThumbnail(false))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				MakeLabeledTextBox(
					LOCTEXT("OutputDirectoryLabel", "输出目录"),
					SAssignNew(OutputDirectoryTextBox, SEditableTextBox)
					.HintText(LOCTEXT("OutputDirectoryHint", "留空 = Project/Saved/Paks")))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				SNew(SExpandableArea)
				.InitiallyCollapsed(false)
				.HeaderContent()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("MainPackagePluginsHeader", "主包插件白名单"))
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
				]
				.BodyContent()
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 4.0f, 0.0f, 6.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("MainPackagePluginsHelp", "构建主包时会关闭引擎默认插件，只启用这里勾选的插件。默认勾选普通游戏最小配置。"))
						.AutoWrapText(true)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						MakeMainPackagePluginList()
					]
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 12.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.0f, 0.0f, 8.0f, 0.0f)
				[
					SNew(SButton)
					.Text(LOCTEXT("BuildPakButton", "构建 Pak 分包"))
					.ToolTipText(LOCTEXT("BuildPakButtonTooltip", "根据选中的 Pak 入口生成清单、Cook 资源并输出 {PakId}.pak 与 {PakId}.manifest.json。"))
					.OnClicked(this, &SSomeToolPakManifestBuilder::BuildPak)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("BuildMainPackageButton", "构建主包"))
					.ToolTipText(LOCTEXT("BuildMainPackageButtonTooltip", "使用 RunUAT BuildCookRun 按 Windows Shipping 构建完整主程序。"))
					.OnClicked(this, &SSomeToolPakManifestBuilder::BuildMainPackage)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 0.0f, 0.0f, 4.0f)
				[
					SNew(STextBlock)
					.Text(this, &SSomeToolPakManifestBuilder::GetBuildProgressText)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SProgressBar)
					.Percent(this, &SSomeToolPakManifestBuilder::GetBuildProgressPercent)
				]
			]
			+ SVerticalBox::Slot()
			.FillHeight(0.35f)
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				SNew(SBorder)
				.Padding(8.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock).Text(LOCTEXT("LogLabel", "构建消息"))
					]
					+ SVerticalBox::Slot()
					.FillHeight(1.0f)
					[
						SNew(SMultiLineEditableTextBox)
						.Text(this, &SSomeToolPakManifestBuilder::GetLogText)
						.IsReadOnly(true)
					]
				]
			]
			+ SVerticalBox::Slot()
			.FillHeight(0.65f)
			[
				SNew(SBorder)
				.Padding(8.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock).Text(LOCTEXT("UnrealPakLogLabel", "UnrealPak 日志"))
					]
					+ SVerticalBox::Slot()
					.FillHeight(1.0f)
					[
						SNew(SMultiLineEditableTextBox)
						.Text(this, &SSomeToolPakManifestBuilder::GetUnrealPakLogText)
						.IsReadOnly(true)
					]
				]
			]
		]
	];
}

FReply SSomeToolPakManifestBuilder::BuildPak()
{
	if (IsBuildRunning())
	{
		LogText += TEXT("\n已有构建任务正在运行。");
		return FReply::Handled();
	}

	const FString PakIdString = GetSelectedPakId();
	if (PakIdString.IsEmpty())
	{
		LogText = TEXT("请选择命名为 DA_PakEntry_{PakId} 的 Pak 入口资产。");
		UnrealPakLogText.Reset();
		return FReply::Handled();
	}

	FString OutputDirectory = OutputDirectoryTextBox->GetText().ToString();
	if (OutputDirectory.IsEmpty())
	{
		OutputDirectory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Paks")));
	}

	if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get())
	{
		const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
		FString SelectedDirectory;
		if (!DesktopPlatform->OpenDirectoryDialog(
			ParentWindowHandle,
			TEXT("选择 SomeTool Pak 输出目录"),
			OutputDirectory,
			SelectedDirectory))
		{
			LogText = TEXT("已取消构建：没有选择输出目录。");
			return FReply::Handled();
		}

		OutputDirectory = SelectedDirectory;
		OutputDirectoryTextBox->SetText(FText::FromString(OutputDirectory));
	}

	const FString ConfirmMessage = FString::Printf(
		TEXT("现在构建清单、执行 Cook 并生成 Pak 吗？\n\nPakId：%s\n输出目录：%s\n\n构建会在后台 Commandlet 中执行，编辑器界面不会被阻塞。"),
		*PakIdString,
		*OutputDirectory);

	if (FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString(ConfirmMessage)) != EAppReturnType::Ok)
	{
		LogText = TEXT("已取消构建。");
		return FReply::Handled();
	}

	const FString EditorCmdPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::EngineDir(), TEXT("Binaries"), TEXT("Win64"), TEXT("UnrealEditor-Cmd.exe")));
	const FString ProjectFilePath = FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
	if (!FPaths::FileExists(EditorCmdPath) || !FPaths::FileExists(ProjectFilePath))
	{
		LogText = FString::Printf(
			TEXT("无法启动后台构建 Commandlet。\n编辑器命令行：%s\n工程文件：%s"),
			*EditorCmdPath,
			*ProjectFilePath);
		return FReply::Handled();
	}

	IFileManager::Get().MakeDirectory(*OutputDirectory, true);
	BuildMode = EBuildMode::GamePak;
	BuildPakId = PakIdString;
	BuildOutputDirectory = OutputDirectory;
	const FString BuildTempDirectory = FPaths::Combine(OutputDirectory, TEXT(".BuildTemp"), PakIdString);
	IFileManager::Get().MakeDirectory(*BuildTempDirectory, true);
	BuildLogFilePath = FPaths::Combine(BuildTempDirectory, FString::Printf(TEXT("%s.build.log"), *PakIdString));
	BuildStartTime = FPlatformTime::Seconds();
	SetBuildProgress(0.02f, TEXT("正在启动后台构建"));

	const FString Params = FString::Printf(
		TEXT("%s -run=SomeToolPakBuild -PakId=%s -OutputDirectory=%s -unattended -nop4 -UTF8Output -abslog=%s"),
		*QuoteSlateCommandArgument(ProjectFilePath),
		*PakIdString,
		*QuoteSlateCommandArgument(OutputDirectory),
		*QuoteSlateCommandArgument(BuildLogFilePath));

	BuildProcessId = 0;
	BuildProcHandle = FPlatformProcess::CreateProc(
		*EditorCmdPath,
		*Params,
		true,
		true,
		true,
		&BuildProcessId,
		0,
		*FPaths::ProjectDir(),
		nullptr);

	if (!BuildProcHandle.IsValid())
	{
		ResetBuildProcess();
		LogText = TEXT("启动后台构建 Commandlet 失败。");
		return FReply::Handled();
	}

	LogText.Reset();
	LogText += TEXT("后台构建已启动。\n");
	LogText += FString::Printf(TEXT("PakId: %s\n"), *BuildPakId);
	LogText += FString::Printf(TEXT("输出目录: %s\n"), *BuildOutputDirectory);
	LogText += FString::Printf(TEXT("日志: %s\n"), *BuildLogFilePath);
	LogText += FString::Printf(TEXT("进程ID: %u\n"), BuildProcessId);
	UnrealPakLogText = TEXT("等待 UnrealPak 阶段开始。");
	RegisterActiveTimer(0.5f, FWidgetActiveTimerDelegate::CreateSP(this, &SSomeToolPakManifestBuilder::TickBuildProcess));

	return FReply::Handled();
}

FReply SSomeToolPakManifestBuilder::BuildMainPackage()
{
	if (IsBuildRunning())
	{
		LogText += TEXT("\n已有构建任务正在运行。");
		return FReply::Handled();
	}

	FString OutputDirectory = OutputDirectoryTextBox->GetText().ToString();
	if (OutputDirectory.IsEmpty())
	{
		OutputDirectory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("MainPackage")));
	}

	if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get())
	{
		const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
		FString SelectedDirectory;
		if (!DesktopPlatform->OpenDirectoryDialog(
			ParentWindowHandle,
			TEXT("选择主包输出目录"),
			OutputDirectory,
			SelectedDirectory))
		{
			LogText = TEXT("已取消主包构建：没有选择输出目录。");
			return FReply::Handled();
		}

		OutputDirectory = SelectedDirectory;
		OutputDirectoryTextBox->SetText(FText::FromString(OutputDirectory));
	}

	const FString ConfirmMessage = FString::Printf(
		TEXT("现在构建 Windows Shipping 主包吗？\n\n输出目录：%s\n插件白名单：%s\n\n这会调用 RunUAT BuildCookRun，并在后台执行 Build、Cook、Stage、Pak、Archive。"),
		*OutputDirectory,
		*GetSelectedMainPackagePluginsText());

	if (FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString(ConfirmMessage)) != EAppReturnType::Ok)
	{
		LogText = TEXT("已取消主包构建。");
		return FReply::Handled();
	}

	FString RunUATPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::EngineDir(), TEXT("Build"), TEXT("BatchFiles"), TEXT("RunUAT.bat")));
	FString ProjectFilePath = FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
	if (!FPaths::FileExists(RunUATPath) || !FPaths::FileExists(ProjectFilePath))
	{
		LogText = FString::Printf(
			TEXT("无法启动主包构建。\nRunUAT：%s\n工程文件：%s"),
			*RunUATPath,
			*ProjectFilePath);
		return FReply::Handled();
	}

	FString ProjectWhitelistErrorText;
	if (!ApplyMainPackagePluginWhitelist(ProjectFilePath, GetSelectedMainPackagePlugins(), BuildOriginalProjectText, ProjectWhitelistErrorText))
	{
		LogText = ProjectWhitelistErrorText;
		return FReply::Handled();
	}

	IFileManager::Get().MakeDirectory(*OutputDirectory, true);
	BuildMode = EBuildMode::MainPackage;
	BuildPakId = TEXT("MainPackage");
	BuildOutputDirectory = OutputDirectory;
	BuildProjectFilePath = ProjectFilePath;
	const FString BuildLogDirectory = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SomeToolPakBuildLogs")));
	IFileManager::Get().MakeDirectory(*BuildLogDirectory, true);
	BuildLogFilePath = MakeUniqueBuildLogFilePath(BuildLogDirectory, TEXT("MainPackage.build"));
	BuildStartTime = FPlatformTime::Seconds();
	SetBuildProgress(0.02f, TEXT("正在启动主包构建"));

	const FString UATCommandLine = FString::Printf(
		TEXT("BuildCookRun -project=%s -target=P_Recording_53_AS -noP4 -utf8output -platform=Win64 -clientconfig=Shipping -build -nocompileeditor -cook -stage -package -pak -archive -archivedirectory=%s -nodebuginfo -ubtargs=\"-NoHotReload -NoHotReloadFromIDE\" > %s 2>&1"),
		*QuoteSlateCommandArgument(ProjectFilePath),
		*QuoteSlateCommandArgument(OutputDirectory),
		*QuoteSlateCommandArgument(BuildLogFilePath));

	FString ProcessPath = RunUATPath;
	FString Params = UATCommandLine;
	FString WorkingDirectory = FPaths::GetPath(RunUATPath);
#if PLATFORM_WINDOWS
	ProcessPath = TEXT("cmd.exe");
	Params = FString::Printf(TEXT("/c \"\"%s\" %s\""), *RunUATPath, *UATCommandLine);
#endif

	BuildProcessId = 0;
	BuildProcHandle = FPlatformProcess::CreateProc(
		*ProcessPath,
		*Params,
		true,
		true,
		true,
		&BuildProcessId,
		0,
		*WorkingDirectory,
		nullptr);

	if (!BuildProcHandle.IsValid())
	{
		ResetBuildProcess();
		LogText = TEXT("启动主包构建失败。");
		return FReply::Handled();
	}

	LogText.Reset();
	LogText += TEXT("主包构建已启动。\n");
	LogText += FString::Printf(TEXT("输出目录: %s\n"), *BuildOutputDirectory);
	LogText += FString::Printf(TEXT("插件白名单: %s\n"), *GetSelectedMainPackagePluginsText());
	LogText += FString::Printf(TEXT("工程文件: %s\n"), *BuildProjectFilePath);
	LogText += FString::Printf(TEXT("日志: %s\n"), *BuildLogFilePath);
	LogText += FString::Printf(TEXT("进程ID: %u\n"), BuildProcessId);
	UnrealPakLogText = TEXT("主包构建会使用 UAT/UnrealPak，日志会持续刷新。");
	RegisterActiveTimer(0.5f, FWidgetActiveTimerDelegate::CreateSP(this, &SSomeToolPakManifestBuilder::TickBuildProcess));

	return FReply::Handled();
}

void SSomeToolPakManifestBuilder::HandlePakEntryChanged(const FAssetData& AssetData)
{
	SelectedPakEntryAsset = AssetData;
	UnrealPakLogText.Reset();

	const FString PakIdString = GetSelectedPakId();
	if (PakIdString.IsEmpty())
	{
		LogText = TEXT("请选择命名为 DA_PakEntry_{PakId} 的 Pak 入口资产。");
		return;
	}

	LogText = FString::Printf(
		TEXT("已选择 Pak 入口。\nPakId: %s\n入口资产: %s"),
		*PakIdString,
		*SelectedPakEntryAsset.GetObjectPathString());
}

FString SSomeToolPakManifestBuilder::GetPakEntryObjectPath() const
{
	return SelectedPakEntryAsset.IsValid() ? SelectedPakEntryAsset.GetObjectPathString() : FString();
}

FString SSomeToolPakManifestBuilder::GetSelectedPakId() const
{
	return SelectedPakEntryAsset.IsValid()
		? ParsePakIdFromEntryName(SelectedPakEntryAsset.AssetName.ToString())
		: FString();
}

void SSomeToolPakManifestBuilder::RefreshMainPackagePluginOptions()
{
	TMap<FString, FMainPackagePluginOption> OptionsByName;
	for (const TSharedRef<IPlugin>& Plugin : IPluginManager::Get().GetDiscoveredPlugins())
	{
		const FString PluginName = Plugin->GetName();
		if (!ShouldAlwaysShowMainPackagePlugin(PluginName) && !IsRuntimePluginForWin64Shipping(Plugin))
		{
			continue;
		}

		FMainPackagePluginOption Option;
		Option.Name = PluginName;
		Option.DisplayName = Plugin->GetFriendlyName().IsEmpty() ? PluginName : Plugin->GetFriendlyName();
		Option.SourceText = GetPluginSourceText(Plugin);
		Option.Note = GetKnownMainPackagePluginNote(PluginName);
		Option.bRecommended = IsRecommendedMainPackagePlugin(PluginName);
		Option.bEnabled = Option.bRecommended;
		OptionsByName.Add(PluginName, MoveTemp(Option));
	}

	for (const FString& PluginName : { TEXT("SomeTool"), TEXT("Angelscript"), TEXT("AngelscriptEnhancedInput"), TEXT("EnhancedInput"), TEXT("HardwareEncoders"), TEXT("OpenImageDenoise") })
	{
		if (!OptionsByName.Contains(PluginName))
		{
			FMainPackagePluginOption Option;
			Option.Name = PluginName;
			Option.DisplayName = PluginName;
			Option.SourceText = TEXT("未发现");
			Option.Note = GetKnownMainPackagePluginNote(PluginName);
			Option.bRecommended = IsRecommendedMainPackagePlugin(PluginName);
			Option.bEnabled = false;
			OptionsByName.Add(PluginName, MoveTemp(Option));
		}
	}

	OptionsByName.GenerateValueArray(MainPackagePlugins);
	MainPackagePlugins.Sort([](const FMainPackagePluginOption& Left, const FMainPackagePluginOption& Right)
	{
		if (Left.bRecommended != Right.bRecommended)
		{
			return Left.bRecommended;
		}
		if (Left.SourceText != Right.SourceText)
		{
			return Left.SourceText > Right.SourceText;
		}
		return Left.Name < Right.Name;
	});
}

TSharedRef<SWidget> SSomeToolPakManifestBuilder::MakeMainPackagePluginList()
{
	TSharedRef<SScrollBox> ScrollBox = SNew(SScrollBox);
	SAssignNew(MainPackagePluginListBox, SVerticalBox);

	for (const FMainPackagePluginOption& Option : MainPackagePlugins)
	{
		const FString PluginName = Option.Name;
		const FString DetailText = FString::Printf(
			TEXT("%s | %s%s%s"),
			*Option.Name,
			*Option.SourceText,
			Option.bRecommended ? TEXT(" | 默认") : TEXT(""),
			Option.Note.IsEmpty() ? TEXT("") : *FString::Printf(TEXT(" | %s"), *Option.Note));

		ScrollBox->AddSlot()
		.Padding(0.0f, 1.0f)
		[
			SNew(SBorder)
			.Padding(6.0f, 4.0f)
			.BorderBackgroundColor(Option.bRecommended ? FLinearColor(0.08f, 0.12f, 0.08f, 1.0f) : FLinearColor(0.06f, 0.06f, 0.06f, 1.0f))
			[
				SNew(SCheckBox)
				.IsChecked(this, &SSomeToolPakManifestBuilder::IsMainPackagePluginChecked, PluginName)
				.OnCheckStateChanged(this, &SSomeToolPakManifestBuilder::HandleMainPackagePluginChecked, PluginName)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(FText::FromString(Option.DisplayName))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 2.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(DetailText))
						.ColorAndOpacity(FSlateColor(FLinearColor(0.62f, 0.62f, 0.62f, 1.0f)))
					]
				]
			]
		];
	}

	return SNew(SBox)
	.HeightOverride(220.0f)
	[
		ScrollBox
	];
}

ECheckBoxState SSomeToolPakManifestBuilder::IsMainPackagePluginChecked(FString PluginName) const
{
	for (const FMainPackagePluginOption& Option : MainPackagePlugins)
	{
		if (Option.Name == PluginName)
		{
			return Option.bEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		}
	}
	return ECheckBoxState::Unchecked;
}

void SSomeToolPakManifestBuilder::HandleMainPackagePluginChecked(const ECheckBoxState NewState, FString PluginName)
{
	for (FMainPackagePluginOption& Option : MainPackagePlugins)
	{
		if (Option.Name == PluginName)
		{
			Option.bEnabled = NewState == ECheckBoxState::Checked;
			break;
		}
	}
}

TArray<FString> SSomeToolPakManifestBuilder::GetSelectedMainPackagePlugins() const
{
	TArray<FString> SelectedPlugins;
	for (const FMainPackagePluginOption& Option : MainPackagePlugins)
	{
		if (Option.bEnabled && Option.SourceText != TEXT("未发现"))
		{
			SelectedPlugins.Add(Option.Name);
		}
	}
	SelectedPlugins.Sort();
	return SelectedPlugins;
}

FString SSomeToolPakManifestBuilder::GetSelectedMainPackagePluginsText() const
{
	const TArray<FString> SelectedPlugins = GetSelectedMainPackagePlugins();
	return SelectedPlugins.IsEmpty() ? TEXT("无") : JoinPluginNames(SelectedPlugins);
}

bool SSomeToolPakManifestBuilder::ApplyMainPackagePluginWhitelist(
	const FString& ProjectFilePath,
	const TArray<FString>& EnabledPlugins,
	FString& OutOriginalProjectText,
	FString& OutErrorText) const
{
	FString SourceJsonText;
	if (!FFileHelper::LoadFileToString(SourceJsonText, *ProjectFilePath))
	{
		OutErrorText = FString::Printf(TEXT("读取工程文件失败：%s"), *ProjectFilePath);
		return false;
	}
	OutOriginalProjectText = SourceJsonText;

	TSharedPtr<FJsonObject> ProjectObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(SourceJsonText);
	if (!FJsonSerializer::Deserialize(Reader, ProjectObject) || !ProjectObject.IsValid())
	{
		OutErrorText = FString::Printf(TEXT("解析工程文件失败：%s"), *ProjectFilePath);
		return false;
	}

	ProjectObject->SetBoolField(TEXT("DisableEnginePluginsByDefault"), true);

	TArray<TSharedPtr<FJsonValue>> PluginValues;
	for (const FString& PluginName : EnabledPlugins)
	{
		TSharedRef<FJsonObject> PluginObject = MakeShared<FJsonObject>();
		PluginObject->SetStringField(TEXT("Name"), PluginName);
		PluginObject->SetBoolField(TEXT("Enabled"), true);
		PluginValues.Add(MakeShared<FJsonValueObject>(PluginObject));
	}
	ProjectObject->SetArrayField(TEXT("Plugins"), MoveTemp(PluginValues));

	FString OutputJsonText;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputJsonText);
	if (!FJsonSerializer::Serialize(ProjectObject.ToSharedRef(), Writer))
	{
		OutErrorText = TEXT("序列化临时工程文件失败。");
		return false;
	}

	if (!FFileHelper::SaveStringToFile(OutputJsonText, *ProjectFilePath))
	{
		OutErrorText = FString::Printf(TEXT("写入工程插件白名单失败：%s"), *ProjectFilePath);
		return false;
	}

	return true;
}

bool SSomeToolPakManifestBuilder::RestoreMainPackageProjectFile(FString& OutErrorText)
{
	if (BuildProjectFilePath.IsEmpty() || BuildOriginalProjectText.IsEmpty())
	{
		return true;
	}

	if (!FFileHelper::SaveStringToFile(BuildOriginalProjectText, *BuildProjectFilePath))
	{
		OutErrorText = FString::Printf(TEXT("恢复工程文件失败：%s"), *BuildProjectFilePath);
		return false;
	}

	return true;
}

FString SSomeToolPakManifestBuilder::GetBuildTaskDisplayName() const
{
	return BuildMode == EBuildMode::MainPackage ? TEXT("主包") : BuildPakId;
}

EActiveTimerReturnType SSomeToolPakManifestBuilder::TickBuildProcess(double InCurrentTime, float InDeltaTime)
{
	if (!IsBuildRunning())
	{
		return EActiveTimerReturnType::Stop;
	}

	int32 ReturnCode = 0;
	if (!FPlatformProcess::GetProcReturnCode(BuildProcHandle, &ReturnCode))
	{
		FString TailText;
		if (LoadLogTail(BuildLogFilePath, TailText, 8000))
		{
			UpdateBuildProgressFromLog(TailText);
			if (BuildMode == EBuildMode::MainPackage && TailText.Contains(TEXT("BUILD FAILED")))
			{
				FString AutomationToolLogText;
				const FString AutomationToolLogFilePath = GetAutomationToolLogFilePath();
				if (!AutomationToolLogFilePath.IsEmpty() && FFileHelper::LoadFileToString(AutomationToolLogText, *AutomationToolLogFilePath))
				{
					TailText += TEXT("\n\n===== AutomationTool 详细日志 =====\n");
					TailText += AutomationToolLogText;
				}
			}

			LogText = FString::Printf(
				TEXT("正在构建...\n任务: %s\n输出目录: %s\n日志: %s\n进程ID: %u\n耗时: %.1f 秒\n阶段: %s\n\n%s"),
				*GetBuildTaskDisplayName(),
				*BuildOutputDirectory,
				*BuildLogFilePath,
				BuildProcessId,
				FPlatformTime::Seconds() - BuildStartTime,
				*BuildProgressText,
				*TailText);
		}

		if (BuildMode == EBuildMode::GamePak)
		{
			FString StageTailText;
			const FString UnrealPakLogFilePath = GetGamePakUnrealPakLogPath(BuildOutputDirectory, BuildPakId);
			const FString CookLogFilePath = GetGamePakCookLogPath(BuildOutputDirectory, BuildPakId);
			if (LoadLogTail(UnrealPakLogFilePath, StageTailText, 12000))
			{
				UnrealPakLogText = MakeStageLogText(TEXT("UnrealPak"), UnrealPakLogFilePath, StageTailText);
			}
			else if (LoadLogTail(CookLogFilePath, StageTailText, 12000))
			{
				UnrealPakLogText = MakeStageLogText(TEXT("Cook"), CookLogFilePath, StageTailText);
			}
			else
			{
				UnrealPakLogText = TEXT("等待 Cook 阶段开始。");
			}
		}
		else
		{
			UnrealPakLogText = TailText.IsEmpty()
				? TEXT("等待主包构建日志输出。")
				: MakeStageLogText(TEXT("主包"), BuildLogFilePath, TailText);
		}
		return EActiveTimerReturnType::Continue;
	}

	FinishBuildProcess(ReturnCode);
	return EActiveTimerReturnType::Stop;
}

void SSomeToolPakManifestBuilder::FinishBuildProcess(const int32 ReturnCode)
{
	FString FinalLogText;
	FFileHelper::LoadFileToString(FinalLogText, *BuildLogFilePath);
	if (BuildMode == EBuildMode::MainPackage)
	{
		FString AutomationToolLogText;
		const FString AutomationToolLogFilePath = GetAutomationToolLogFilePath();
		if (!AutomationToolLogFilePath.IsEmpty() && FFileHelper::LoadFileToString(AutomationToolLogText, *AutomationToolLogFilePath))
		{
			FinalLogText += TEXT("\n\n===== AutomationTool 详细日志 =====\n");
			FinalLogText += AutomationToolLogText;
		}
		if (FinalLogText.Contains(TEXT("Unable to build while Live Coding is active")))
		{
			FinalLogText = TEXT("检测到 Live Coding 正在运行。请关闭 Live CodingConsole，或在编辑器里按 Ctrl+Alt+F11 结束 Live Coding 后重试。\n\n") + FinalLogText;
		}
	}
	const int32 MaxLogChars = 12000;
	if (FinalLogText.Len() > MaxLogChars)
	{
		FinalLogText = FinalLogText.Right(MaxLogChars);
	}

	const FString FinalManifestFilePath = FPaths::Combine(BuildOutputDirectory, BuildPakId + TEXT(".manifest.json"));
	const FString FinalPakFilePath = FPaths::Combine(BuildOutputDirectory, BuildPakId + TEXT(".pak"));
	const FString TempUnrealPakLogFilePath = FPaths::Combine(BuildOutputDirectory, TEXT(".BuildTemp"), BuildPakId, BuildPakId + TEXT(".unrealpak.log"));

	LogText.Reset();
	LogText += ReturnCode == 0 ? TEXT("构建成功\n") : TEXT("构建失败\n");
	if (BuildMode == EBuildMode::MainPackage)
	{
		LogText += TEXT("任务: 主包\n");
		LogText += FString::Printf(TEXT("输出目录: %s\n"), *BuildOutputDirectory);
		LogText += FString::Printf(TEXT("工程文件: %s\n"), *BuildProjectFilePath);
		LogText += TEXT("说明: RunUAT 会按平台归档完整包体，Windows 主包通常在输出目录的 Windows 子目录下。\n");
	}
	else
	{
		LogText += FString::Printf(TEXT("PakId: %s\n"), *BuildPakId);
		LogText += FString::Printf(TEXT("清单文件: %s\n"), *FinalManifestFilePath);
		LogText += FString::Printf(TEXT("Pak 文件: %s\n"), *FinalPakFilePath);
	}
	if (ReturnCode == 0)
	{
		if (BuildMode == EBuildMode::MainPackage)
		{
			LogText += FString::Printf(TEXT("日志: %s\n"), *BuildLogFilePath);
		}
		else
		{
			LogText += TEXT("临时日志: 已清理\n");
		}
	}
	else
	{
		LogText += FString::Printf(TEXT("日志: %s\n"), *BuildLogFilePath);
	}
	LogText += FString::Printf(TEXT("返回码: %d\n\n"), ReturnCode);
	LogText += FinalLogText;
	SetBuildProgress(ReturnCode == 0 ? 1.0f : BuildProgress, ReturnCode == 0 ? TEXT("构建完成") : TEXT("构建失败"));

	UnrealPakLogText.Reset();
	if (BuildMode == EBuildMode::MainPackage)
	{
		UnrealPakLogText = FinalLogText.IsEmpty()
			? TEXT("没有读取到主包构建日志。")
			: FinalLogText;
	}
	else if (!FFileHelper::LoadFileToString(UnrealPakLogText, *TempUnrealPakLogFilePath))
	{
		UnrealPakLogText = ReturnCode == 0
			? TEXT("构建成功，但没有读取到 UnrealPak 日志文件。")
			: TEXT("构建失败，UnrealPak 可能没有启动。");
	}
	if (ReturnCode == 0 && BuildMode == EBuildMode::GamePak)
	{
		CleanWidgetSuccessfulBuildOutputs(BuildOutputDirectory, BuildPakId);
	}
	if (BuildMode == EBuildMode::MainPackage)
	{
		FString RestoreErrorText;
		if (!RestoreMainPackageProjectFile(RestoreErrorText))
		{
			LogText = RestoreErrorText + TEXT("\n\n") + LogText;
		}
	}

	ResetBuildProcess();
}

void SSomeToolPakManifestBuilder::ResetBuildProcess()
{
	if (BuildProcHandle.IsValid())
	{
		FPlatformProcess::CloseProc(BuildProcHandle);
		BuildProcHandle.Reset();
	}

	BuildProcessId = 0;
	BuildPakId.Reset();
	BuildOutputDirectory.Reset();
	BuildLogFilePath.Reset();
	BuildProjectFilePath.Reset();
	BuildOriginalProjectText.Reset();
	BuildMode = EBuildMode::GamePak;
	BuildStartTime = 0.0;
}

bool SSomeToolPakManifestBuilder::IsBuildRunning() const
{
	return BuildProcHandle.IsValid();
}

FText SSomeToolPakManifestBuilder::GetLogText() const
{
	return FText::FromString(LogText);
}

FText SSomeToolPakManifestBuilder::GetUnrealPakLogText() const
{
	return FText::FromString(UnrealPakLogText);
}

TOptional<float> SSomeToolPakManifestBuilder::GetBuildProgressPercent() const
{
	return BuildProgress;
}

FText SSomeToolPakManifestBuilder::GetBuildProgressText() const
{
	return FText::FromString(BuildProgressText);
}

void SSomeToolPakManifestBuilder::SetBuildProgress(const float Percent, const FString& StatusText)
{
	BuildProgress = FMath::Clamp(Percent, 0.0f, 1.0f);
	BuildProgressText = StatusText;
}

void SSomeToolPakManifestBuilder::UpdateBuildProgressFromLog(const FString& BuildLogText)
{
	struct FProgressMarker
	{
		const TCHAR* Token;
		float Percent;
		const TCHAR* StatusText;
	};

	static const FProgressMarker Markers[] =
	{
		{ TEXT("SOMETOOL_PAK_PROGRESS 10"), 0.10f, TEXT("正在生成资源清单") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 25"), 0.25f, TEXT("资源清单已生成，准备 Cook") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 40"), 0.40f, TEXT("正在 Cook 资源") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 65"), 0.65f, TEXT("Cook 完成，准备生成 Pak") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 78"), 0.78f, TEXT("正在生成 Pak 文件列表") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 88"), 0.88f, TEXT("正在执行 UnrealPak") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 95"), 0.95f, TEXT("正在复制最终输出") },
		{ TEXT("SOMETOOL_PAK_PROGRESS 100"), 1.00f, TEXT("构建完成") }
	};

	for (const FProgressMarker& Marker : Markers)
	{
		if (BuildLogText.Contains(Marker.Token) && Marker.Percent >= BuildProgress)
		{
			SetBuildProgress(Marker.Percent, Marker.StatusText);
		}
	}

	if (BuildMode == EBuildMode::MainPackage)
	{
		struct FMainPackageProgressMarker
		{
			const TCHAR* Token;
			float Percent;
			const TCHAR* StatusText;
		};

		static const FMainPackageProgressMarker MainPackageMarkers[] =
		{
			{ TEXT("BuildCookRun"), 0.08f, TEXT("主包构建已启动") },
			{ TEXT("********** BUILD COMMAND STARTED **********"), 0.18f, TEXT("正在编译主程序") },
			{ TEXT("********** COOK COMMAND STARTED **********"), 0.36f, TEXT("正在 Cook 主包资源") },
			{ TEXT("********** STAGE COMMAND STARTED **********"), 0.62f, TEXT("正在整理 Stage 目录") },
			{ TEXT("********** PACKAGE COMMAND STARTED **********"), 0.78f, TEXT("正在打包主包") },
			{ TEXT("********** ARCHIVE COMMAND STARTED **********"), 0.90f, TEXT("正在归档主包输出") },
			{ TEXT("BUILD SUCCESSFUL"), 1.00f, TEXT("构建完成") }
		};

		for (const FMainPackageProgressMarker& Marker : MainPackageMarkers)
		{
			if (BuildLogText.Contains(Marker.Token) && Marker.Percent >= BuildProgress)
			{
				SetBuildProgress(Marker.Percent, Marker.StatusText);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
