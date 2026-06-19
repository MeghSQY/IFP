// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMSingleButtonBaseComponent.h"
#include "Util/BCModernActionMenusTypes.h"
#include "BCMAMCheckboxComponent.generated.h"

/**
 * A component that acts like a checkbox when clicked. Used to show boolean values as a menu button.
 */
UCLASS(DisplayName="Modern Checkbox Component")
class BCMODERNACTIONMENUS_API UBCMAMCheckboxComponent : public UBCMAMSingleButtonBaseComponent
{
	GENERATED_BODY()

public:

	UBCMAMCheckboxComponent();

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetIsChecked(bool bInIsChecked);

	/** Called when the checkbox is checked or unchecked. */
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBCMAMBoolDelegate OnChecked;

	virtual FReply HandleButtonClicked() override;
	virtual bool ProcessMenuInputChord(const FInputChord& InChord) override;
	
protected:

	virtual void SynchronizeProperties() override;

	/** Whether the checkbox is checked or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	bool bIsChecked;
};
