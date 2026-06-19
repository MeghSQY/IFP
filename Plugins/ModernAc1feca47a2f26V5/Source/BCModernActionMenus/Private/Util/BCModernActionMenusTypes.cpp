// Copyright Bartschi Creative 2025. All rights reserved.

#include "Util/BCModernActionMenusTypes.h"

FBCModernActionMenuStyle::FBCModernActionMenuStyle()
{
	MenuWidth = 240.f;
	MenuPadding = FMargin(4.f);
	ShadowOffset = FMargin(-20.f ,-6.f, -20.f, -26.f);
	ItemPadding = FMargin(12.f, 4.f);
	IconSize = FVector2D(16.f);
	ColumnPadding = 12.f;
	bMaintainLeftColumnWidth = false;
	TransitionDuration = 0.25f;
	SeparatorThickness = 1.f;
	SeparatorPadding = FMargin(-4.f, 4.f);
	SeparatorColor = FLinearColor(0.177f, 0.177f, 0.177f, 1.f);
}

void FBCModernActionMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	OutBrushes.Add(&BackgroundBrush);
	OutBrushes.Add(&ShadowBrush);
	ItemButtonStyle.GetResources(OutBrushes);
	
	HighlightedItemButtonStyle.GetResources(OutBrushes);
	BaseTextStyle.GetResources(OutBrushes);
	SectionTextStyle.GetResources(OutBrushes);
	ShortcutTextStyle.GetResources(OutBrushes);
	OutBrushes.Add(&CheckmarkBrush);
	OutBrushes.Add(&EmptyCheckmarkBrush);
	OutBrushes.Add(&RadioBrush);
	OutBrushes.Add(&EmptyRadioBrush);
	OutBrushes.Add(&ArrowBrush);
}

const FName FBCModernActionMenuStyle::TypeName(TEXT("FBCModernActionMenuStyle"));

const FBCModernActionMenuStyle& FBCModernActionMenuStyle::GetDefault()
{
	static FBCModernActionMenuStyle Default;
	return Default;
}
