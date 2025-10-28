// Copyright (C) Varian Daemon 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Data/IFP_CoreData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CF_CompatibilitySettings.generated.h"

/**Parent struct for the compatibility settings system.
 * Make children of this struct to create your own rules
 * for what is allowed in a container and what is not. */
USTRUCT(BlueprintType, DisplayName = "Compatibility Settings (Base)")
struct INVENTORYFRAMEWORKPLUGIN_API FCompatibilitySettingsFragmentBase : public FContainerFragment
{
	GENERATED_BODY()

	virtual bool PassesCompatibilityCheck(FS_ContainerSettings Container, FS_InventoryItem Item) { return true; }
};

/**Allows the container to filter what is allowed and
 * what is not allowed inside of it.
 *
 * This is the legacy compatibility settings where everything
 * was in one place. Since the fragments update, this can
 * be modularized into several fragments and thus is now
 * labelled as "legacy", but is not being removed due to
 * many projects using this, and it can still be used as is. */
USTRUCT(BlueprintType, DisplayName = "🔒 Compatibility Settings (Legacy)")
struct FCompatibilitySettingsFragment : public FCompatibilitySettingsFragmentBase
{
	GENERATED_BODY()

	/**What tags must an item have for it to be allowed in this container?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compatibility")
	FGameplayTagContainer RequiredTags;

	/**If an item has any of these tags, they are not allowed in this container.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compatibility")
	FGameplayTagContainer BlockingTags;

	/**What item types are allowed? These are declared in the item asset.
	 * This will also check children tags, so adding Item.Type.Weapon
	 * will allow any item with the type tag Item.Type.Weapon.Gun and
	 * any other children tags of the tags you add here.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compatibility")
	FGameplayTagContainer ItemTypes;

	//Only these items are allowed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compatibility")
	TArray<TSoftObjectPtr<UDA_CoreItem>> ItemWhitelist;

	//These items are not allowed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compatibility")
	TArray<TSoftObjectPtr<UDA_CoreItem>> ItemBlacklist;

	virtual bool PassesCompatibilityCheck(FS_ContainerSettings Container, FS_InventoryItem Item) override;
};

/**Only allows items whose tag match a tag query.*/
USTRUCT(BlueprintType, DisplayName = "🔒 Tag Query Compatibility Settings")
struct FTagQueryCompatibilitySettings : public FCompatibilitySettingsFragmentBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compatibility")
	FGameplayTagQuery ItemTagQuery;

	virtual bool PassesCompatibilityCheck(FS_ContainerSettings Container, FS_InventoryItem Item) override;
};

/**
 * 
 */
UCLASS()
class INVENTORYFRAMEWORKPLUGIN_API UCF_CompatibilitySettings : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(Category = "IFP|Fragments|Compatibility Settings", BlueprintCallable)
	static FCompatibilitySettingsFragment GetLegacyCompatibilitySettingsFragmentFromContainer(FS_ContainerSettings Container);

	//Attempt to convert @Struct to TagFragment
	UFUNCTION(Category = "IFP|Fragments|Compatibility Settings", BlueprintCallable, BlueprintPure)
	static FCompatibilitySettingsFragment ToLegacyCompatibilitySettingsFragment(FInstancedStruct Struct);

	UFUNCTION(Category = "IFP|Fragments|Compatibility Settings", BlueprintCallable)
	static FTagQueryCompatibilitySettings GetTagQueryCompatibilitySettingsFragmentFromContainer(FS_ContainerSettings Container);

	//Attempt to convert @Struct to TagFragment
	UFUNCTION(Category = "IFP|Fragments|Compatibility Settings", BlueprintCallable, BlueprintPure)
	static FTagQueryCompatibilitySettings ToTagQueryCompatibilitySettingsFragment(FInstancedStruct Struct);
};
