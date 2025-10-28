// Copyright (C) Varian Daemon 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IFP_CoreData.h"
#include "Engine/DeveloperSettings.h"
#include "DS_InventoryFrameworkSettingsRuntime.generated.h"

/**IFP settings to modify how the plugin works and behaves */
UCLASS(DisplayName = "Inventory Framework (Runtime)", DefaultConfig, Config = Game)
class INVENTORYFRAMEWORKPLUGIN_API UDS_InventoryFrameworkSettingsRuntime : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	/**The rotations are allowed.
	 * For example, if you only want 0 and 90 degrees,
	 * you would remove 180 and 270. */
	UPROPERTY(Category = "Items", EditAnywhere, Config, BlueprintReadOnly)
	TArray<TEnumAsByte<ERotation>> AllowedItemRotations = { ERotation::Zero, ERotation::Ninety, ERotation::OneEighty, ERotation::TwoSeventy };

	/**Fragments that are removed from the dropdown and will cause an error when used.*/
	UPROPERTY(Category = "Fragments", EditAnywhere, Config)
	TArray<TSoftObjectPtr<const UScriptStruct>> DisabledFragments;

	/**IFP's default behavior for retrieving the local inventory component
	 * is to get the player pawn and finding the inventory component from there.
	 * Some projects prefer the controller. Checking this to true will alter
	 * how @GetLocalInventoryComponent works and will now retrieve the
	 * local inventory component from the player controller. */
	UPROPERTY(Category = "Fragments", EditAnywhere, Config)
	bool LocalComponentOnController = false;
	
	virtual FName GetCategoryName() const override { return FName("Plugins"); }
	
#if WITH_EDITOR
	virtual FText GetSectionText() const override { return INVTEXT("Inventory Framework (Runtime)"); }
#endif

	UFUNCTION(Category = "IFP|Settings", BlueprintCallable, BlueprintPure, DisplayName = "Get IFP Settings", meta = (CompactNodeTitle = "IFP Settings"))
	static UDS_InventoryFrameworkSettingsRuntime* GetIFPSettings()
	{
		return GetMutableDefault<UDS_InventoryFrameworkSettingsRuntime>();
	}
};
