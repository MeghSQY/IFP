// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "Framework/SlateDelegates.h"
#include "Templates/SubclassOf.h"
#include "Widgets/SCompoundWidget.h"

class SHorizontalBox;
class STextBlock;
class SImage;
class SButton;
class UBCModernActionMenuItemButtonStyleAsset;
struct FBCModernActionMenuStyle;

/**
 * A simple leaf button that has an icon, label, and shortcut text to the right.
 */
class BCMODERNACTIONMENUS_API SBCLeafButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SBCLeafButton)
		{
		}
		SLATE_EVENT(FOnClicked, OnClicked)
		SLATE_EVENT(FSimpleDelegate, OnHovered)
		SLATE_EVENT(FSimpleDelegate, OnUnhovered)
	SLATE_END_ARGS()

	SBCLeafButton();

	void Construct(const FArguments& InArgs);

	void SetStyle(const FBCModernActionMenuStyle* InStyle, const TSubclassOf<UBCModernActionMenuItemButtonStyleAsset>& InButtonStyleOverride);
	
	TSharedPtr<SButton> GetButton() const { return Button; }

	TSharedPtr<SImage> GetIcon() const { return Icon; }

	TSharedPtr<STextBlock> GetLabel() const { return Label; }

	void SetLabel(const FText& InLabel);
	void SetIconBrush(const FSlateBrush* InBrush);
	void SetShortcut(const FInputChord& InShortcut);

protected:

	TSharedPtr<SButton> Button;
	TSharedPtr<SImage> Icon;
	TSharedPtr<STextBlock> Label;
	TSharedPtr<STextBlock> Shortcut;
	TSharedPtr<SHorizontalBox> HorizontalBox;

	const FBCModernActionMenuStyle* Style;
	TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> ButtonStyleOverride;
	
	FOnClicked OnClicked;
	FSimpleDelegate OnHovered;
	FSimpleDelegate OnUnhovered;
	
};
