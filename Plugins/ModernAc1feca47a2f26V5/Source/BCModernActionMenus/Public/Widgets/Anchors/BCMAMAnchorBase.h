// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/SOverlay.h"
#include "BCMAMAnchorBase.generated.h"

class UBCModernActionMenu;
class SBCMenuAnchor;

/**
 * The base class for all anchors. An anchor is a widget that opens a menu.
 */
UCLASS(Abstract, DisplayName="BCMAM Anchor Base")
class BCMODERNACTIONMENUS_API UBCMAMAnchorBase : public UWidget
{
	GENERATED_BODY()

public:

	UBCMAMAnchorBase();
	
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	/** Open or close the menu. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetIsOpen(bool bOpen);

	/** Toggle the open state of the menu. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void ToggleOpen();

	/** Returns true if the menu is open. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	bool IsOpen() const;

	/** Called when the menu is opened. */
	UPROPERTY(BlueprintAssignable)
	FBCMAMMenuDelegate OnMenuOpened;

	/** Called when the menu is closed. */
	UPROPERTY(BlueprintAssignable)
	FBCMAMMenuDelegate OnMenuClosed;
	
protected:

	/** The desired placement of the menu relative to the anchor. Other placements will be attempted if this placement has no room.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	TEnumAsByte<EMenuPlacement> Placement;

	/** If true, closing the menu plays the fade-out animation. If false, the menu closes immediately. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu")
	bool bFadeOutOnClose = true;

	/** Might be null if the menu is not being displayed. */
	UPROPERTY(Transient)
	TObjectPtr<UBCModernActionMenu> ActionMenu;
	
	UFUNCTION()
	void HandleActionExecuted(UBCMAMActionComponent* ActionComponent);
	
	void OnGlobalFocusChanging(const FFocusEvent& InFocusEvent
	                           , const FWeakWidgetPath& InOldFocusedWidgetPath,
	                           const TSharedPtr<SWidget>& InOldFocusedWidget
	                           , const FWidgetPath& InNewFocusedWidgetPath,
	                           const TSharedPtr<SWidget>& InNewFocusedWidget);
	
	virtual void OpenMenu();
	virtual void CloseMenu();

	TSharedPtr<SBCMenuAnchor> GetActiveMenuAnchor() const;

	TArray<TSharedPtr<SBCMenuAnchor>> MenuAnchors;

	void SetActiveAnchorIndex(int32 Index);
	
	int32 ActiveAnchorIndex;

	/** True if we are switching to a new active menu index and there was another menu active . */
	bool bWasAnotherMenuActive;
};
