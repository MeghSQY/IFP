// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "Framework/SlateDelegates.h"
#include "Templates/SubclassOf.h"
#include "Widgets/SLeafWidget.h"

class SBox;
/**
 * A simple leaf widget that draws a line
 */
class BCMODERNACTIONMENUS_API SBCLine : public SLeafWidget
{
public:

	SLATE_BEGIN_ARGS(SBCLine)
		:
		_Thickness(1.f),
		_Color(FLinearColor::White)
		{
		}
		
		SLATE_ARGUMENT(float, Thickness)
		SLATE_ARGUMENT(FLinearColor, Color)
	SLATE_END_ARGS()

	
	void Construct(const FArguments& InArgs);


	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	                      FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                      bool bParentEnabled) const override;

	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	                      
	void SetThickness(float InThickness) { Thickness = InThickness; }
	void SetColor(FLinearColor InColor) { Color = InColor; }

protected:


	float Thickness;
	FLinearColor Color;
};
