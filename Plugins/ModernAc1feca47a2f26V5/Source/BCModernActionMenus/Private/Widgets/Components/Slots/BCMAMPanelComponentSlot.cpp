// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/Slots/BCMAMPanelComponentSlot.h"

#include "Widgets/Components/BCMAMPanelComponent.h"

void UBCMAMPanelComponentSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UBCMAMPanelComponentSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	
	Slot = nullptr;
}

void UBCMAMPanelComponentSlot::BuildSlot(TSharedRef<SVerticalBox> InVerticalBox)
{
	InVerticalBox->AddSlot()
 		.AutoHeight()
 		.Expose(Slot)
 		[
 			Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()
 		];
}

#if WITH_EDITOR
bool UBCMAMPanelComponentSlot::NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize)
{
	if (NudgeDirection.Y == 0)
	{
		return false;
	}
	
	const FVector2D ClampedDirection = NudgeDirection.ClampAxes(-1, 1);
	UBCMAMPanelComponent* PanelParent = CastChecked<UBCMAMPanelComponent>(Parent);

	const int32 CurrentIndex = PanelParent->GetChildIndex(Content);

	if ((CurrentIndex == 0 && ClampedDirection.Y < 0.0f) ||
		(CurrentIndex + 1 >= PanelParent->GetChildrenCount() && ClampedDirection.Y > 0.0f))
	{
		return false;
	}

	PanelParent->Modify();
	PanelParent->ShiftChild(CurrentIndex + FMath::TruncToInt32(ClampedDirection.Y), Content);

	return true;
}

void UBCMAMPanelComponentSlot::SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot)
{
	const ThisClass* const TemplateVerticalBoxSlot = CastChecked<ThisClass>(TemplateSlot);
	const int32 CurrentIndex = TemplateVerticalBoxSlot->Parent->GetChildIndex(TemplateVerticalBoxSlot->Content);

	UBCMAMPanelComponent* PanelParent = CastChecked<UBCMAMPanelComponent>(Parent);
	PanelParent->ShiftChild(CurrentIndex, Content);
}
#endif
