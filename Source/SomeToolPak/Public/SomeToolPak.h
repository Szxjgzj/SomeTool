#pragma once

#include "Modules/ModuleManager.h"

class FSomeToolPakModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
