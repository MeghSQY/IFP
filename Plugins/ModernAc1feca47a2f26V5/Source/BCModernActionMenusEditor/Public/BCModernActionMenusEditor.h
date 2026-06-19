// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBCModernActionMenusGraphPanelPinFactory;

class FBCModernActionMenusEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
	
private:
    
	TSharedPtr<FBCModernActionMenusGraphPanelPinFactory> GraphPanelPinFactory;
	void OnNewBlueprintCreated(class UBlueprint* InBlueprint);
};

