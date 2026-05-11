#include "SomeToolPakEditor.h"

#include "Styling/AppStyle.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SSomeToolPakManifestBuilder.h"

namespace
{
const FName SomeToolPakManifestBuilderTabName = TEXT("SomeToolPakManifestBuilder");

void OpenSomeToolPakManifestBuilder()
{
	FGlobalTabmanager::Get()->TryInvokeTab(SomeToolPakManifestBuilderTabName);
}
}

void FSomeToolPakEditorModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		SomeToolPakManifestBuilderTabName,
		FOnSpawnTab::CreateRaw(this, &FSomeToolPakEditorModule::SpawnManifestBuilderTab))
		.SetDisplayName(NSLOCTEXT("SomeToolPakEditor", "ManifestBuilderTab", "SomeTool Pak 构建工具"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSomeToolPakEditorModule::RegisterMenus));
}

void FSomeToolPakEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	if (UObjectInitialized())
	{
		UToolMenus::UnregisterOwner(this);
	}

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SomeToolPakManifestBuilderTabName);
}

TSharedRef<SDockTab> FSomeToolPakEditorModule::SpawnManifestBuilderTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SSomeToolPakManifestBuilder)
		];
}

void FSomeToolPakEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.MainMenu.Tools"));
	FToolMenuSection& Section = Menu->FindOrAddSection(TEXT("SomeTool"));
	Section.AddMenuEntry(
		TEXT("SomeToolPakManifestBuilder"),
		NSLOCTEXT("SomeToolPakEditor", "ManifestBuilderMenuLabel", "SomeTool Pak 构建工具"),
		NSLOCTEXT("SomeToolPakEditor", "ManifestBuilderMenuTooltip", "按 PakId 生成 Pak 清单并构建 Pak 文件。"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateStatic(&OpenSomeToolPakManifestBuilder)));

	UToolMenu* PlayToolBar = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.LevelEditorToolBar.PlayToolBar"));
	FToolMenuSection& PlaySection = PlayToolBar->FindOrAddSection(TEXT("Play"));
	FToolMenuEntry PakToolbarEntry = FToolMenuEntry::InitToolBarButton(
		TEXT("SomeToolPakManifestBuilderToolbar"),
		FUIAction(FExecuteAction::CreateStatic(&OpenSomeToolPakManifestBuilder)),
		NSLOCTEXT("SomeToolPakEditor", "ManifestBuilderToolbarLabel", "打包"),
		NSLOCTEXT("SomeToolPakEditor", "ManifestBuilderToolbarTooltip", "打开 SomeTool Pak 构建工具。"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("MainFrame.PackageProject")));
	PakToolbarEntry.StyleNameOverride = TEXT("AssetEditorToolbar");
	PlaySection.AddEntry(PakToolbarEntry);
}

IMPLEMENT_MODULE(FSomeToolPakEditorModule, SomeToolPakEditor)
