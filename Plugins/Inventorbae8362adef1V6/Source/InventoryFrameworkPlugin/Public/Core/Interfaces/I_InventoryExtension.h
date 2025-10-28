// Copyright (C) Varian Daemon 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_InventoryExtension.generated.h"

class UAC_Inventory;
// This class does not need to be modified.
UINTERFACE()
class UI_InventoryExtension : public UInterface
{
	GENERATED_BODY()
};

/**Actor components with this interface will automatically receive special events
 * from the inventory component.
 * This is only used for actor components.
 *
 * Important: BeginPlay is not always consistent when it comes to actor components
 * and I have not found a way to control the order of BeginPlay calls.
 * Since some may be called before the inventory component is initialized,
 * and some may be called after, it has prompted the creation of this interface.
 *
 * Instead of using BeginPlay, you can use the event @PreInventoryComponentInitialized
 * and @PostInventoryComponentInitialized
 * Note, these can happen before or after BeginPlay. With this interface, you shouldn't
 * be using BeginPlay at all if the logic is related to the inventory component,
 * but instead, use these events for that logic.
 *
 * This is used for the helper components in the example project and is
 * usable for your own helper components.*/
class INVENTORYFRAMEWORKPLUGIN_API II_InventoryExtension
{
	GENERATED_BODY()

	
public:

	/**StartComponent has been called, but we haven't
	 * started processing anything.
	 * This is extremely early in the initialization process.
	 * So you should realistically only be setting up delegates */
	UFUNCTION(Category = "Inventory Extension", BlueprintNativeEvent)
	void PreInventoryComponentInitialized(UAC_Inventory* Inventory);

	/**StartComponent has been called, and we have finished
	 * processing all the items. */
	UFUNCTION(Category = "Inventory Extension", BlueprintNativeEvent)
	void PostInventoryComponentInitialized(UAC_Inventory* Inventory);
};
