// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMSingleAnchorBase.h"
#include "Widgets/SOverlay.h"
#include "BCMAMContextMenuAnchor.generated.h"

class SMenuAnchor;
class SBox;

/**
 * An anchor that opens a context menu.
 *
 * Opens a context menu on the mouse position when right-clicking within the target content.
 */
UCLASS(DisplayName="Modern Context Menu Anchor")
class BCMODERNACTIONMENUS_API UBCMAMContextMenuAnchor : public UBCMAMSingleAnchorBase
{
	GENERATED_BODY()

public:

	/** Manually position the context menu relative to the target content. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetContextMenuPosition(FVector2D Position);

protected:
	virtual void OnWidgetRebuilt() override;
	
	virtual FReply HandleMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply HandleMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override; 

};
