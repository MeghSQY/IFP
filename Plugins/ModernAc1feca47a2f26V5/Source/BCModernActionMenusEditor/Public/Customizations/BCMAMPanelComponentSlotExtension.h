// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "WidgetReference.h"
#include "DesignerExtension.h"

class FBCMAMPanelComponentSlotExtension : public FDesignerExtension
{
public:
	FBCMAMPanelComponentSlotExtension();

	virtual ~FBCMAMPanelComponentSlotExtension() {}

	virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;
	
	virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;

private:

	bool CanShift(int32 ShiftAmount) const;

	FReply HandleShiftVertical(int32 ShiftAmount);

	void ShiftVertical(UWidget* Widget, int32 ShiftAmount);
};
