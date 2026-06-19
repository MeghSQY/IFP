// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Anchors/BCMAMDropdownMenuAnchor.h"

FReply UBCMAMDropdownMenuAnchor::HandleMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		OpenMenu();	
	
		return FReply::Handled().ReleaseMouseCapture();
	}
 	
	return FReply::Unhandled();	
}
