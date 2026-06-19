// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SButton.h"


class SImage;

/**
 * A single panel in a Modern Action Menu
 */
class BCMODERNACTIONMENUS_API SBCModernActionMenuPanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SBCModernActionMenuPanel)
			: _Content(),
			  _Style(&FBCModernActionMenuStyle::GetDefault()),
			  _Name(NAME_None),
			  _UseShadow(true)
		{
		}

		SLATE_ARGUMENT(TSharedPtr<SWidget>, Content)
		SLATE_STYLE_ARGUMENT(FBCModernActionMenuStyle, Style)
		SLATE_ARGUMENT(FName, Name)
		SLATE_ARGUMENT(bool, UseShadow)
		SLATE_EVENT(FSimpleDelegate, OnFocusLost)
	SLATE_END_ARGS()

	SBCModernActionMenuPanel();

	void Construct(const FArguments& InArgs);

	virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath,
	                             const FFocusEvent& InFocusEvent) override;

	void SetUseShadow(bool bUseShadow);
	
	TSharedPtr<SWidget> GetRoot()
	{
		return Root;
	}

	TSharedPtr<SWidget> GetFocusButton()
	{
		return FocusButton;
	}

	TSharedPtr<SVerticalBox> GetItemsContainer()
	{
		return ItemsContainer;
	}

	void FocusMenu();

protected:

	TSharedPtr<SWidget> Root;
	TSharedPtr<SButton> FocusButton;
	TSharedPtr<SVerticalBox> ItemsContainer;
	TSharedPtr<SImage> ShadowImage;

	const FBCModernActionMenuStyle* Style;

	FName CurrentSection;
	int32 CurrentItemIndex;

	bool bUseShadow;

	FSimpleDelegate OnFocusLost;
};
