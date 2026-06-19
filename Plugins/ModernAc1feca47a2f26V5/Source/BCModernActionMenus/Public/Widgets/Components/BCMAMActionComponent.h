// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMSingleButtonBaseComponent.h"
#include "Framework/Commands/InputChord.h"
#include "Util/BCModernActionMenusTypes.h"
#include "BCMAMActionComponent.generated.h"

class UBCMAMActionBase;
class UBCModernActionMenuItemButtonStyleAsset;
class STextBlock;
class SImage;
class SButton;

/**
 * A component that executes a single action when clicked. Can either bind to `OnExecuted` or provide an
 * action object to execute.
 */
UCLASS(DisplayName="Modern Action Component")
class BCMODERNACTIONMENUS_API UBCMAMActionComponent : public UBCMAMSingleButtonBaseComponent
{
	GENERATED_BODY()

public:

	UBCMAMActionComponent();
	
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetShowIcon(bool bShow);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetIcon(const FSlateBrush& InIcon);

	/** Set a custom action object to execute. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetAction(UBCMAMActionBase* InAction);

	virtual bool ProcessMenuInputChord(const FInputChord& InChord) override;

	/** Called when this action is executed. */
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBCMAMActionComponentDelegate OnExecuted;
	
protected:

	virtual void SynchronizeProperties() override;

	/** Whether to show the icon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(InlineEditConditionToggle), Category="Modern Action Menu Component")
	bool bShowIcon;

	/** The icon to show. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition=bShowIcon), Category="Modern Action Menu Component")
	FSlateBrush Icon;
	
	/** An optional action object to execute. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Modern Action Menu Component")
    TObjectPtr<UBCMAMActionBase> Action;

	virtual void ExecuteAction();

	virtual FReply HandleButtonClicked() override;

};
