// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelSlot.h"
#include "Components/VerticalBox.h"
#include "BCMAMPanelComponentSlot.generated.h"

/**
 * Uses a vertical box slot within the UBCMAMPanelComponent class
 */
UCLASS()
class BCMODERNACTIONMENUS_API UBCMAMPanelComponentSlot : public UPanelSlot
{
	GENERATED_BODY()
	
	SVerticalBox::FSlot* Slot;

public:

	// UPanelSlot interface
	virtual void SynchronizeProperties() override;
	// End of UPanelSlot interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	/** Builds the underlying FSlot for the Slate layout panel. */
	 void BuildSlot(TSharedRef<SVerticalBox> InVerticalBox);

#if WITH_EDITOR
	virtual bool NudgeByDesigner(const FVector2D& NudgeDirection, const TOptional<int32>& GridSnapSize) override;
	virtual void SynchronizeFromTemplate(const UPanelSlot* const TemplateSlot) override;
#endif //WITH_EDITOR
};
