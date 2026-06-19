// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Helpers/SBCSeparator.h"
#include "Widgets/Helpers/SBCLine.h"
#include "Widgets/Layout/SBox.h"

void SBCSeparator::SetThickness(float InThickness) 
{
	Thickness = InThickness;

	if (Line)
	{
		Line->SetThickness(Thickness);
	}
}

void SBCSeparator::SetColor(FLinearColor InColor) 
{
	Color = InColor;

	if (Line)
	{
		Line->SetColor(Color);
	}
}

void SBCSeparator::SetPadding(FMargin InPadding)
{
	Padding = InPadding;

	if (Box)
	{
		Box->SetPadding(Padding);
	}
}

void SBCSeparator::Construct(const FArguments& InArgs)
{
	Padding = InArgs._Padding;
	Thickness = InArgs._Thickness;
	Color = InArgs._Color;

	this->ChildSlot
	[
		SAssignNew(Box, SBox)
		.Padding(Padding)
		[
			SAssignNew(Line, SBCLine)
			.Thickness(Thickness)
			.Color(Color)
		]
	];
}
