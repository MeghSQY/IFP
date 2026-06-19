// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Helpers/SBCLine.h"

#include "Widgets/Layout/SBox.h"


int32 SBCLine::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
                            FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
                            bool bParentEnabled) const
{
	TArray<FVector2D> LinePoints;
	LinePoints.AddUninitialized(2);

	LinePoints[0] = FVector2D(0.0f, 0.0f);
	LinePoints[1] = FVector2D(AllottedGeometry.GetLocalSize().X, 0.0f);
	
	const float ScaleFactor = AllottedGeometry.GetAccumulatedRenderTransform().GetMatrix().GetScale().GetVector().X;

	FLinearColor FinalColor = Color;
	FinalColor.A *= InWidgetStyle.GetColorAndOpacityTint().A;
	
	FSlateDrawElement::MakeLines(
						OutDrawElements,
						LayerId,
						AllottedGeometry.ToPaintGeometry(),
						LinePoints,
						ESlateDrawEffect::None,
						FinalColor,
						true,
						Thickness * ScaleFactor
					);
	
	return LayerId;
}

FVector2D SBCLine::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(0.f, 0.f);
}


void SBCLine::Construct(const FArguments& InArgs)
{
	Thickness = InArgs._Thickness;
	Color = InArgs._Color;
}
