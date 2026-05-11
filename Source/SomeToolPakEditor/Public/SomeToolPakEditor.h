#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSpawnTabArgs;
class SDockTab;

class FSomeToolPakEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedRef<SDockTab> SpawnManifestBuilderTab(const FSpawnTabArgs& SpawnTabArgs);
	void RegisterMenus();
};
