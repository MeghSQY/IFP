// Copyright (C) Varian Daemon 2023. All Rights Reserved.


#include "Core/Fragments/CF_CompatibilitySettings.h"

#include "InventoryFrameworkPlugin.h"
#include "Core/Data/FL_InventoryFramework.h"
#include "Core/Fragments/FL_IFP_FragmentHelpers.h"

bool FCompatibilitySettingsFragment::PassesCompatibilityCheck(FS_ContainerSettings Container, FS_InventoryItem Item)
{
	const FGameplayTagContainer ItemTags = UFL_InventoryFramework::GetItemsTags(Item, true);

	if(RequiredTags.IsValidIndex(0))
	{
		if(!ItemTags.HasAnyExact(RequiredTags))
		{
			return false;
		}
	}

	if(BlockingTags.IsValidIndex(0))
	{		    
		if(ItemTags.HasAnyExact(BlockingTags))
		{
			return false;
		}	
	}

	if(!ItemTypes.IsEmpty())
	{
		if(!Item.ItemAsset->ItemType.MatchesAny(ItemTypes))
		{
			return false;
		}
	}
		
	//Whitelist check.
	if(ItemWhitelist.IsValidIndex(0))
	{
		if(!ItemWhitelist.Contains(Item.ItemAssetSoftReference))
		{
			return false;
		}
	}

	//Blacklist check.
	if(ItemBlacklist.IsValidIndex(0))
	{
		if(ItemBlacklist.Contains(Item.ItemAssetSoftReference))
		{
			return false;
		}
	}

	return true;
}

bool FTagQueryCompatibilitySettings::PassesCompatibilityCheck(FS_ContainerSettings Container, FS_InventoryItem Item)
{
	const FGameplayTagContainer ItemTags = UFL_InventoryFramework::GetItemsTags(Item, true);

	if(ItemTagQuery.IsEmpty())
	{
		UE_LOG(LogInventoryFramework, Log, TEXT("Using TagQueryCompatibilitySettings, but the query was empty"));
		return true;
	}
	
	return ItemTagQuery.Matches(ItemTags);
}

FCompatibilitySettingsFragment UCF_CompatibilitySettings::GetLegacyCompatibilitySettingsFragmentFromContainer(
	FS_ContainerSettings Container)
{
	FCompatibilitySettingsFragment* CompatibilitySettingsFragment = FindFragment<FCompatibilitySettingsFragment>(Container.ContainerFragments);
	return CompatibilitySettingsFragment ? *CompatibilitySettingsFragment : FCompatibilitySettingsFragment();
}

FCompatibilitySettingsFragment UCF_CompatibilitySettings::ToLegacyCompatibilitySettingsFragment(FInstancedStruct Struct)
{
	if(const FCompatibilitySettingsFragment* CompatibilitySettingsFragment = Struct.GetPtr<FCompatibilitySettingsFragment>())
	{
		return *CompatibilitySettingsFragment;
	}

	return FCompatibilitySettingsFragment();
}

FTagQueryCompatibilitySettings UCF_CompatibilitySettings::GetTagQueryCompatibilitySettingsFragmentFromContainer(
	FS_ContainerSettings Container)
{
	FTagQueryCompatibilitySettings* CompatibilitySettingsFragment = FindFragment<FTagQueryCompatibilitySettings>(Container.ContainerFragments);
	return CompatibilitySettingsFragment ? *CompatibilitySettingsFragment : FTagQueryCompatibilitySettings();
}

FTagQueryCompatibilitySettings UCF_CompatibilitySettings::ToTagQueryCompatibilitySettingsFragment(
	FInstancedStruct Struct)
{
	if(const FTagQueryCompatibilitySettings* CompatibilitySettingsFragment = Struct.GetPtr<FTagQueryCompatibilitySettings>())
	{
		return *CompatibilitySettingsFragment;
	}

	return FTagQueryCompatibilitySettings();
}
