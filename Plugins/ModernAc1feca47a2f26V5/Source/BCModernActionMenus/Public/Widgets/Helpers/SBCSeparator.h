// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "Framework/SlateDelegates.h"
#include "Templates/SubclassOf.h"
#include "Widgets/SCompoundWidget.h"

class SBCLine;
class SBox;
/**
 * A simple leaf widget that draws a line
 */
class BCMODERNACTIONMENUS_API SBCSeparator : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SBCSeparator)
		:
		_Thickness(1.f),
		_Color(FLinearColor::White),
		_Padding(FMargin(0.f))
		{
		}
		
		SLATE_ARGUMENT(float, Thickness)
		SLATE_ARGUMENT(FLinearColor, Color)
		SLATE_ARGUMENT(FMargin, Padding)
	SLATE_END_ARGS()

	
	void Construct(const FArguments& InArgs);

	void SetThickness(float InThickness);
	void SetColor(FLinearColor InColor);
	void SetPadding(FMargin InPadding);

protected:

	TSharedPtr<SBox> Box;
	TSharedPtr<SBCLine> Line;

	FMargin Padding;
	float Thickness;
	FLinearColor Color;
};
