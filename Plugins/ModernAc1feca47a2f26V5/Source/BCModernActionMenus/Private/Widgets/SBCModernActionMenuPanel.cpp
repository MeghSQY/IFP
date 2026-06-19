// Copyright Bartschi Creative 2025. All rights reserved.

#include "Widgets/SBCModernActionMenuPanel.h"

#include "Framework/Application/SlateApplication.h"
#include "Layout/WidgetPath.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBox.h"

SBCModernActionMenuPanel::SBCModernActionMenuPanel(): Style(nullptr), CurrentItemIndex(0)
{
}

void SBCModernActionMenuPanel::Construct(const FArguments& InArgs)
{
	Style = InArgs._Style;
	OnFocusLost = InArgs._OnFocusLost;
	
	SAssignNew(Root, SOverlay)
	.Visibility(EVisibility::SelfHitTestInvisible)
	+ SOverlay::Slot()
	.Padding(Style->ShadowOffset)
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SAssignNew(ShadowImage, SImage).Image(&Style->ShadowBrush)
	]
	+ SOverlay::Slot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SAssignNew(FocusButton, SButton)
		.ButtonStyle(FAppStyle::Get(), "InvisibleButton")
		.ContentPadding(FMargin(0.f))
		[
			SNew(SBox)
			.WidthOverride(Style->MenuWidth)
			[
				SNew(SBorder).BorderImage(&Style->BackgroundBrush).Padding(Style->MenuPadding)
				[
					InArgs._Content ? InArgs._Content.ToSharedRef() : SNullWidget::NullWidget
				]
			]
		]
	];

	SetUseShadow(InArgs._UseShadow);

	this->ChildSlot
	[
		Root.ToSharedRef()
	];
}

void SBCModernActionMenuPanel::OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath,
	const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
{
	SCompoundWidget::OnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);
	
	const bool bDecendantNewlyFocused = NewWidgetPath.ContainsWidget(this);
	if (!bDecendantNewlyFocused)
	{
		OnFocusLost.ExecuteIfBound();
	}
}

void SBCModernActionMenuPanel::SetUseShadow(bool bInUseShadow)
{
	bUseShadow = bInUseShadow;
	ShadowImage->SetVisibility(bUseShadow ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
}

void SBCModernActionMenuPanel::FocusMenu()
{
	if (FocusButton.IsValid())
	{
		FSlateApplication::Get().SetUserFocus(0, FocusButton, EFocusCause::SetDirectly);
	}
}
