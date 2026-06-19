// Copyright Bartschi Creative 2025. All rights reserved.

#include "Widgets/Helpers/SBCVisualAttachmentBox.h"

void SBCVisualAttachmentBox::Construct(const FArguments& InArgs)
{
	SBox::Construct(InArgs);
}

void SBCVisualAttachmentBox::SetContentAnchor(FVector2D InContentAnchor)
{
	if (InContentAnchor != ContentAnchor)
	{
		ContentAnchor = InContentAnchor;
		Invalidate(EInvalidateWidget::Layout);
	}
}

void SBCVisualAttachmentBox::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	const FGeometry NewGeometry = AllottedGeometry.MakeChild(InnerDesiredSize, FSlateLayoutTransform(-(ContentAnchor * AllottedGeometry.GetLocalSize())));
	SBox::OnArrangeChildren(NewGeometry, ArrangedChildren);
}

FVector2D SBCVisualAttachmentBox::ComputeDesiredSize(float InScale) const
{
	InnerDesiredSize = SBox::ComputeDesiredSize(InScale);
	return FVector2D(0, 0);
}

int32 SBCVisualAttachmentBox::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	LayerId = SBox::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	return LayerId;
}
