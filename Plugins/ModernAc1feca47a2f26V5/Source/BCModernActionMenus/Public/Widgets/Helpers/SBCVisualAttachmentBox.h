// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "Widgets/Layout/SBox.h"

/**
 * Helper visual attachment box for displaying menus in the UMG Designer canvas
 */
class BCMODERNACTIONMENUS_API SBCVisualAttachmentBox : public SBox
{
public:
	void Construct(const FArguments& InArgs);

	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	void SetContentAnchor(FVector2D InContentAnchor);

private:
	mutable FVector2D InnerDesiredSize;

	FVector2D ContentAnchor = FVector2D::ZeroVector;
};
