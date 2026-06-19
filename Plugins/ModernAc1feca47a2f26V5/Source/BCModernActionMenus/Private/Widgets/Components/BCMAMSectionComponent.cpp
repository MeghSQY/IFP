// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMSectionComponent.h"

#include "Components/VerticalBox.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Helpers/SBCSeparator.h"
#include "Widgets/Text/STextBlock.h"

UBCMAMSectionComponent::UBCMAMSectionComponent()
{
	Title = NSLOCTEXT("BCModernActionMenus", "SectionTitle", "Section");
	bShowSeparator = true;
}

void UBCMAMSectionComponent::SetTitle(const FText& InTitle)
{
	Title = InTitle;
	
	if (TextBlock.IsValid())
	{
		TextBlock->SetText(Title);
	}
}

void UBCMAMSectionComponent::SetShowSeparator(bool bInShowSeparator)
{
	bShowSeparator = bInShowSeparator;
	
	if (Separator.IsValid())
	{
		Separator->SetVisibility(bShowSeparator ? EVisibility::HitTestInvisible : EVisibility::Collapsed);
	}
}

void UBCMAMSectionComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	if (TextBlock.IsValid())
	{
		SetTitle(Title);
		TextBlock->SetTextStyle(&Style.SectionTextStyle);
	}

	SetShowSeparator(bShowSeparator);
	if (Separator.IsValid())
	{
		Separator->SetThickness(Style.SeparatorThickness);
		Separator->SetColor(Style.SeparatorColor);
		Separator->SetPadding(Style.SeparatorPadding);
	}
}

TSharedRef<SWidget> UBCMAMSectionComponent::RebuildWidget()
{
	TSharedRef<SWidget> VerticalBox = Super::RebuildWidget();

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	return SAssignNew(Root, SVerticalBox)
		+ SVerticalBox::Slot().Padding(Style.ItemPadding).AutoHeight()
		[
			SAssignNew(TextBlock, STextBlock)
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			VerticalBox
		]
		+ SVerticalBox::Slot().AutoHeight()
		[
			SAssignNew(Separator, SBCSeparator)
		];
}

void UBCMAMSectionComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Root.Reset();
	TextBlock.Reset();
}
