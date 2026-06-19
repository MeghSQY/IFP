// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BCModernActionMenusEditorSettings.generated.h"

class UBCModernActionMenuStyleAsset;

/**
 * 
 */
UCLASS(Config=BCModernActionMenus, DefaultConfig, DisplayName="Modern Action Menus Editor Settings")
class BCMODERNACTIONMENUSEDITOR_API UBCModernActionMenusEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UBCModernActionMenusEditorSettings();

	virtual FName GetCategoryName() const override;
	
	UPROPERTY(Config, EditAnywhere, Category="Style", meta = (ToolTip="Default Action Menu Style applied to newly created Action Menus"))
    TSoftClassPtr<UBCModernActionMenuStyleAsset> DefaultMenuStyle;
};
