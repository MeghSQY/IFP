// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Anchors/BCMAMContextMenuAnchor.h"

#include "Framework/Application/SlateApplication.h"
#include "Widgets/Helpers/SBCMenuAnchor.h"

void UBCMAMContextMenuAnchor::SetContextMenuPosition(FVector2D Position)
{
	if (TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor())
	{
		ActiveAnchor->SetContextMenuPosition(Position);
	}
}

void UBCMAMContextMenuAnchor::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor())
	{
		ActiveAnchor->SetIsContextMenu(true);
	}
}

FReply UBCMAMContextMenuAnchor::HandleMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		FVector2D Coords = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());

		SetContextMenuPosition(Coords);

		OpenMenu();	
	
		return FReply::Handled().ReleaseMouseCapture();
	}
 	
	return FReply::Unhandled();	
}

FReply UBCMAMContextMenuAnchor::HandleMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		return FReply::Handled();
	}
	
	return FReply::Unhandled();	
}
