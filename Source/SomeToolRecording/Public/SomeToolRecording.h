#pragma once

#include "Modules/ModuleManager.h"

class FSomeToolRecordingModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
