// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMSingleButtonBaseComponent.h"

#include "Framework/Application/SlateApplication.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Helpers/SBCLeafButton.h"
#include "Widgets/Input/SButton.h"

UBCMAMSingleButtonBaseComponent::UBCMAMSingleButtonBaseComponent()
{
	Label = NSLOCTEXT("BCModernActionMenus", "LeafButtonLabel", "Label");
}

void UBCMAMSingleButtonBaseComponent::SetLabel(FText InLabel)
{
	Label = InLabel;
 
	if (LeafButton)
	{
		LeafButton->SetLabel(Label);
	}
}

void UBCMAMSingleButtonBaseComponent::SetShortcut(const FInputChord& InShortcut)
{
	Shortcut = InShortcut;

	if (LeafButton)
	{
		LeafButton->SetShortcut(Shortcut);
	}
}


void UBCMAMSingleButtonBaseComponent::SetButtonStyleOverride(
	TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> InButtonStyleOverride)
{
	ButtonStyleOverride = InButtonStyleOverride;

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	if (LeafButton)
	{
		LeafButton->SetStyle(&Style, InButtonStyleOverride);
	}
}

TSharedRef<SWidget> UBCMAMSingleButtonBaseComponent::RebuildWidget()
{
	return SAssignNew(LeafButton, SBCLeafButton)
		.OnClicked(FOnClicked::CreateUObject(this, &UBCMAMSingleButtonBaseComponent::HandleButtonClicked))
		.OnHovered(FSimpleDelegate::CreateUObject(this, &UBCMAMSingleButtonBaseComponent::HandleButtonHovered));
}

void UBCMAMSingleButtonBaseComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	LeafButton.Reset();
}

void UBCMAMSingleButtonBaseComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	SetButtonStyleOverride(ButtonStyleOverride);
	SetLabel(Label);
	SetShortcut(Shortcut);

	if (LeafButton)
	{
		LeafButton->SetStyle(&Style, ButtonStyleOverride);
	}
}

FReply UBCMAMSingleButtonBaseComponent::HandleButtonClicked()
{
	return FReply::Handled();
}

void UBCMAMSingleButtonBaseComponent::HandleButtonHovered()
{
	if (LeafButton && LeafButton->GetButton())
	{
		FSlateApplication::Get().SetUserFocus(0, LeafButton->GetButton(), EFocusCause::SetDirectly);
	}
}
