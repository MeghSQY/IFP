// Copyright Bartschi Creative 2025. All rights reserved.


#include "Customizations/BCMAMPanelComponentSlotExtension.h"

#include "WidgetBlueprint.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Widgets/Components/BCMAMPanelComponent.h"
#include "Widgets/Components/Slots/BCMAMPanelComponentSlot.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "UMG"

FBCMAMPanelComponentSlotExtension::FBCMAMPanelComponentSlotExtension()
{
	ExtensionId = FName(TEXT("BCMAMPanelComponentSlot"));
}

bool FBCMAMPanelComponentSlotExtension::CanExtendSelection(const TArray<FWidgetReference>& Selection) const
{
	for ( const FWidgetReference& Widget : Selection )
	{
		if ( !Widget.GetTemplate()->Slot || !Widget.GetTemplate()->Slot->IsA(UBCMAMPanelComponentSlot::StaticClass()) )
		{
			return false;
		}
	}

	return Selection.Num() == 1;
}

void FBCMAMPanelComponentSlotExtension::ExtendSelection(const TArray<FWidgetReference>& Selection,
	TArray<TSharedRef<FDesignerSurfaceElement>>& SurfaceElements)
{
	SelectionCache = Selection;

	TSharedRef<SButton> UpArrow = SNew(SButton)
		.Text(LOCTEXT("UpArrow", "\u2191"))
		.ContentPadding(FMargin(6, 2))
		.IsEnabled(this, &FBCMAMPanelComponentSlotExtension::CanShift, -1)
		.OnClicked(this, &FBCMAMPanelComponentSlotExtension::HandleShiftVertical, -1);

	TSharedRef<SButton> DownArrow = SNew(SButton)
		.Text(LOCTEXT("DownArrow", "\u2193"))
		.ContentPadding(FMargin(6, 2))
		.IsEnabled(this, &FBCMAMPanelComponentSlotExtension::CanShift, 1)
		.OnClicked(this, &FBCMAMPanelComponentSlotExtension::HandleShiftVertical, 1);

	UpArrow->SlatePrepass();
	DownArrow->SlatePrepass();

	SurfaceElements.Add(MakeShareable(new FDesignerSurfaceElement(UpArrow, EExtensionLayoutLocation::TopCenter, FVector2D(UpArrow->GetDesiredSize().X * -0.5f, -UpArrow->GetDesiredSize().Y))));
	SurfaceElements.Add(MakeShareable(new FDesignerSurfaceElement(DownArrow, EExtensionLayoutLocation::BottomCenter, FVector2D(DownArrow->GetDesiredSize().X * -0.5f, 0))));
}

bool FBCMAMPanelComponentSlotExtension::CanShift(int32 ShiftAmount) const
{
	return true;
}

FReply FBCMAMPanelComponentSlotExtension::HandleShiftVertical(int32 ShiftAmount)
{
	BeginTransaction(LOCTEXT("MoveWidget", "Move Widget"));

	for ( FWidgetReference& Selection : SelectionCache )
	{
		ShiftVertical(Selection.GetPreview(), ShiftAmount);
		ShiftVertical(Selection.GetTemplate(), ShiftAmount);
	}

	EndTransaction();

	if (UWidgetBlueprint* BlueprintPtr = Blueprint.Get())
	{
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(BlueprintPtr);
	}

	return FReply::Handled();
}

void FBCMAMPanelComponentSlotExtension::ShiftVertical(UWidget* Widget, int32 ShiftAmount)
{
	UBCMAMPanelComponent* Parent = CastChecked<UBCMAMPanelComponent>(Widget->GetParent());

	Parent->Modify();
	int32 CurrentIndex = Parent->GetChildIndex(Widget);
	Parent->ShiftChild(CurrentIndex + ShiftAmount, Widget);
}

#undef LOCTEXT_NAMESPACE
