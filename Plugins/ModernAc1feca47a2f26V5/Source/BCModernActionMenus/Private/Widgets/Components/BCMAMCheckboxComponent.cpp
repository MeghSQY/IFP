// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMCheckboxComponent.h"

#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Helpers/SBCLeafButton.h"
#include "Widgets/Images/SImage.h"

UBCMAMCheckboxComponent::UBCMAMCheckboxComponent()
{
	bIsChecked = true;
}

void UBCMAMCheckboxComponent::SetIsChecked(bool bInIsChecked)
{
	bIsChecked = bInIsChecked;
	
	if (LeafButton && LeafButton->GetIcon())
 	{
		const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);
		
		LeafButton->GetIcon()->SetImage(bIsChecked ? &Style.CheckmarkBrush : &Style.EmptyCheckmarkBrush);
		LeafButton->GetIcon()->SetColorAndOpacity(FLinearColor::White);
		LeafButton->GetIcon()->SetVisibility(EVisibility::SelfHitTestInvisible);
 	}
}

FReply UBCMAMCheckboxComponent::HandleButtonClicked()
{
	SetIsChecked(!bIsChecked);

	OnChecked.Broadcast(bIsChecked);

	return FReply::Handled();
}

bool UBCMAMCheckboxComponent::ProcessMenuInputChord(const FInputChord& InChord)
{
	if (InChord == Shortcut)
	{
		HandleButtonClicked();
		
		return true;
	}

	return false;
}

void UBCMAMCheckboxComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	SetIsChecked(bIsChecked);
}
