// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMSingleAnchorBase.h"
#include "BCMAMDropdownMenuAnchor.generated.h"

/**
 * An anchor that opens a dropdown menu.
 *
 * Opens a dropdown menu relative to the target content. By default, opens
 * when left-clicking the target content, but can be manually controlled with `SetIsOpen()`.
 *
 * Must be manually controlled if the target content consumes mouse input.
 */

UCLASS(DisplayName="Modern Dropdown Menu Anchor")
class BCMODERNACTIONMENUS_API UBCMAMDropdownMenuAnchor : public UBCMAMSingleAnchorBase
{
	GENERATED_BODY()
	
protected:
	
	virtual FReply HandleMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override; 
};
