// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BCMAMActionBase.generated.h"

class UBCModernActionMenu;

/**
 * Base action class for action menu items.
 */
UCLASS(DisplayName="BCMAM Action Base", Blueprintable, Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class BCMODERNACTIONMENUS_API UBCMAMActionBase : public UObject
{
	GENERATED_BODY()

public:

	/** Implement this function to execute the action */
	virtual void Execute(UBCModernActionMenu* ActionMenu);

	/** Implement this function to execute the action */
	UFUNCTION(BlueprintImplementableEvent, Category="Modern Action Menu")
	void OnExecute(UBCModernActionMenu* ActionMenu);
	
};
