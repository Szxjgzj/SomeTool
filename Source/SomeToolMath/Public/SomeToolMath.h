#pragma once

#include "Modules/ModuleManager.h"

class FSomeToolMathModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
