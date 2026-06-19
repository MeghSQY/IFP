// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMSeparatorComponent.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Helpers/SBCSeparator.h"
#include "Widgets/Layout/SBox.h"

void UBCMAMSeparatorComponent::SetStyleOverride(TSubclassOf<UBCModernActionMenuSeparatorStyleAsset> InStyleOverride)
{
	StyleOverride = InStyleOverride;

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	if (Separator.IsValid())
	{
		Separator->SetThickness(StyleOverride ? StyleOverride->GetDefaultObject<UBCModernActionMenuSeparatorStyleAsset>()->Thickness : Style.SeparatorThickness);
		Separator->SetColor(StyleOverride ? StyleOverride->GetDefaultObject<UBCModernActionMenuSeparatorStyleAsset>()->Color : Style.SeparatorColor);
		Separator->SetPadding(StyleOverride ? StyleOverride->GetDefaultObject<UBCModernActionMenuSeparatorStyleAsset>()->Padding : Style.SeparatorPadding);
	}

}

TSharedRef<SWidget> UBCMAMSeparatorComponent::RebuildWidget()
{
	return SAssignNew(Separator, SBCSeparator);
}

void UBCMAMSeparatorComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Separator.Reset();
}

void UBCMAMSeparatorComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetStyleOverride(StyleOverride);
}
