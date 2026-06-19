// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once
 
#include "CoreMinimal.h"
#include "BCMAMFileMenuAnchor.h"
#include "UObject/Interface.h"
#include "IBCMAMFileMenuAnchorLabel.generated.h"

/*
 * Widgets can implement this interface to be used as a custom File Menu Anchor Label
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UBCMAMFileMenuAnchorLabel : public UInterface
{
	GENERATED_BODY()
};
 
class IBCMAMFileMenuAnchorLabel
{
	GENERATED_BODY()
 
public:

	/** Called when the tab is set */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Modern Action Menu")
	BCMODERNACTIONMENUS_API void OnTabSet(FBCMAMFileMenuAnchorTab Tab, UBCMAMFileMenuAnchor* FileMenuAnchor); 
};