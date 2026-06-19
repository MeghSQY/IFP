// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMActionBase.h"
#include "BCMAMAction_PrintString.generated.h"

/**
 * Menu action that prints a string to the console.
 */
UCLASS(DisplayName="Print String (Action)")
class BCMODERNACTIONMENUS_API UBCMAMAction_PrintString : public UBCMAMActionBase
{
	GENERATED_BODY()

public:

	virtual void Execute(UBCModernActionMenu* ActionMenu) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu|Print String")
	FString ToPrint;
};
