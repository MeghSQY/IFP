// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FBCModernActionMenusModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
