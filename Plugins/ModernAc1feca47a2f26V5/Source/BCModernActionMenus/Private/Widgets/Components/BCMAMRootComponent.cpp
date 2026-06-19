// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMRootComponent.h"

#include "Widgets/SBCModernActionMenuPanel.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"

UBCMAMRootComponent::UBCMAMRootComponent()
{
	bUseShadow = true;
}

void UBCMAMRootComponent::SetUseShadow(bool bInUseShadow)
{
	bUseShadow = bInUseShadow;

	if (Panel.IsValid())
	{
		Panel->SetUseShadow(bInUseShadow);
	}
}

void UBCMAMRootComponent::FocusMenu()
{
	if (Panel.IsValid())
	{
		Panel->FocusMenu();
	}
}

TSharedRef<SWidget> UBCMAMRootComponent::RebuildWidget()
{
	TSharedRef<SWidget> Result = Super::RebuildWidget();

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	return SAssignNew(Panel, SBCModernActionMenuPanel).Content(Result).Style(&Style).UseShadow(bUseShadow);
}

void UBCMAMRootComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Panel.Reset();
}

void UBCMAMRootComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetUseShadow(bUseShadow);
}
