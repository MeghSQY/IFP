// Copyright Bartschi Creative 2025. All rights reserved.


#include "Settings/BCModernActionMenusEditorSettings.h"

#include "StyleAssets/BCModernActionMenuStyleAsset_Dark.h"

UBCModernActionMenusEditorSettings::UBCModernActionMenusEditorSettings()
{
	DefaultMenuStyle = UBCModernActionMenuStyleAsset_Dark::StaticClass();
}

FName UBCModernActionMenusEditorSettings::GetCategoryName() const
{
	return "Plugins";
}
