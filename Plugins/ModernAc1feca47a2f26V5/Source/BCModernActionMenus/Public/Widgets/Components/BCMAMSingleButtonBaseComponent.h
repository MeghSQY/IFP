// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMLeafComponent.h"
#include "Framework/Commands/InputChord.h"
#include "BCMAMSingleButtonBaseComponent.generated.h"

class SBCLeafButton;
class UBCModernActionMenuItemButtonStyleAsset;

/**
 * Base class for leaf components that contain a single button, e.g. action components and checkbox components. 
 */
UCLASS(Abstract, DisplayName="BCMAM Single Button Base Component")
class BCMODERNACTIONMENUS_API UBCMAMSingleButtonBaseComponent : public UBCMAMLeafComponent
{
	GENERATED_BODY()
	
public:

	UBCMAMSingleButtonBaseComponent();

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetLabel(FText InLabel);

	/** Set the shortcut of the button, also used for processing menu input. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetShortcut(const FInputChord& InShortcut);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetButtonStyleOverride(TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> InButtonStyleOverride);

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

	/** The label text contained in the button. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	FText Label;

	/** The keyboard shortcut of the button, also used for processing menu input. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	FInputChord Shortcut;

	/** Optional override for the button style. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> ButtonStyleOverride;

	virtual FReply HandleButtonClicked();
	virtual void HandleButtonHovered();

protected:

	TSharedPtr<SBCLeafButton> LeafButton;
};
