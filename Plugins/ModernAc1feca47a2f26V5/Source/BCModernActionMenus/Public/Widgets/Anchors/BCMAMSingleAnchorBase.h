// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMAnchorBase.h"
#include "Components/NamedSlotInterface.h"
#include "Components/Widget.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/SOverlay.h"
#include "BCMAMSingleAnchorBase.generated.h"

class SBCMenuAnchor;
class SBox;
class UBCModernActionMenu;

/**
 * Base class for anchors that summon a single menu relative to a target widget.
 */
UCLASS(Abstract, DisplayName="BCMAM Single Anchor Base")
class BCMODERNACTIONMENUS_API UBCMAMSingleAnchorBase : public UBCMAMAnchorBase, public INamedSlotInterface
{
	GENERATED_BODY()

public:

	UBCMAMSingleAnchorBase();
	
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	
	virtual void BeginDestroy() override;
	
	// Begin INamedSlotInterface
	virtual void GetSlotNames(TArray<FName>& SlotNames) const override;
	virtual UWidget* GetContentForSlot(FName SlotName) const override;
	virtual void SetContentForSlot(FName SlotName, UWidget* Content) override;
	// End INamedSlotInterface
	
protected:

	/** The class of the menu that will be summoned. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	TSubclassOf<UBCModernActionMenu> ActionMenuClass;
	
	UPROPERTY()
	TObjectPtr<UWidget> TargetContent;
	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	virtual FReply HandleMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	virtual FReply HandleMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);


};
