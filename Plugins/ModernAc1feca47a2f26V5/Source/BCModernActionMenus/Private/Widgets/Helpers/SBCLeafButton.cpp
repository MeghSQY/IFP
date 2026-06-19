// Copyright Bartschi Creative 2025. All rights reserved.

#include "Widgets/Helpers/SBCLeafButton.h"

#include "Components/HorizontalBox.h"
#include "Framework/Commands/InputChord.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

SBCLeafButton::SBCLeafButton(): Style(nullptr)
{
}

void SBCLeafButton::Construct(const FArguments& InArgs)
{
	this->ChildSlot
	[
		SAssignNew(Button, SButton)
        		.HAlign(HAlign_Fill)
        		.OnClicked(InArgs._OnClicked)
        		.OnHovered(InArgs._OnHovered)
				.OnUnhovered(InArgs._OnUnhovered)
        		[
        			SAssignNew(HorizontalBox, SHorizontalBox)
        			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
        			[
        				SAssignNew(Icon, SImage)
        			]
        			+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
        			[
        				SAssignNew(Label, STextBlock)
        			]
        			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
        			[
        				SAssignNew(Shortcut, STextBlock)
        			]
        		]
	];
}

void SBCLeafButton::SetStyle(const FBCModernActionMenuStyle* InStyle,
                             const TSubclassOf<UBCModernActionMenuItemButtonStyleAsset>& InButtonStyleOverride)
{
	Style = InStyle;
	ButtonStyleOverride = InButtonStyleOverride;
	
	if (Button.IsValid())
	{
		Button->SetContentPadding(Style->ItemPadding);
		Button->SetButtonStyle(ButtonStyleOverride
        		                             ? &ButtonStyleOverride->GetDefaultObject<
        			                             UBCModernActionMenuItemButtonStyleAsset>()->Style
        		                             : &Style->ItemButtonStyle);
	}
	
	if (Icon.IsValid())
	{
		Icon->SetDesiredSizeOverride(Style->IconSize);
		Icon->SetColorAndOpacity(InButtonStyleOverride ? FLinearColor::White : Style->BaseTextStyle.ColorAndOpacity);
	}

	if (Label.IsValid())
	{
		Label->SetTextStyle(InButtonStyleOverride ? &ButtonStyleOverride->GetDefaultObject<UBCModernActionMenuItemButtonStyleAsset>()->TextStyle : &Style->BaseTextStyle);
	}

	if (Shortcut.IsValid())
	{
		Shortcut->SetTextStyle(&Style->ShortcutTextStyle);
	}

	if (HorizontalBox)
	{
		HorizontalBox->GetSlot(0).SetPadding(
			FMargin(0.f, 0.f, Style->ColumnPadding, 0.f));

		HorizontalBox->GetSlot(2).SetPadding(
			FMargin(Style->ColumnPadding, 0.f, 0.f, 0.f));
	}
}

void SBCLeafButton::SetLabel(const FText& InLabel)
{
	if (Label.IsValid())
	{
		Label->SetText(InLabel);
	}
}

void SBCLeafButton::SetIconBrush(const FSlateBrush* InBrush)
{
	if (Icon.IsValid())
	{
		Icon->SetImage(InBrush);
	}
}

void SBCLeafButton::SetShortcut(const FInputChord& InShortcut)
{
	if (Shortcut.IsValid())
	{
		Shortcut->SetText(InShortcut.GetInputText(true));
		Shortcut->SetVisibility(InShortcut.Key.IsValid()
			                        ? EVisibility::SelfHitTestInvisible
			                        : EVisibility::Collapsed);
	}
}
