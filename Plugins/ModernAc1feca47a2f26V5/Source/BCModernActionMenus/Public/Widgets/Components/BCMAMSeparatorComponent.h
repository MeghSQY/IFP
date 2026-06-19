// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMLeafComponent.h"
#include "BCMAMSeparatorComponent.generated.h"

class SBox;
class SBCSeparator;
class UBCModernActionMenuSeparatorStyleAsset;

/**
 * A component that adds a separator to a panel, dividing content visually.
 */
UCLASS(DisplayName="Modern Separator Component")
class BCMODERNACTIONMENUS_API UBCMAMSeparatorComponent : public UBCMAMLeafComponent
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Modern Action Menu Component")
	void SetStyleOverride(TSubclassOf<UBCModernActionMenuSeparatorStyleAsset> InStyleOverride);

protected:

	/** An asset to override the default style of the separator. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	TSubclassOf<UBCModernActionMenuSeparatorStyleAsset> StyleOverride;
	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

	TSharedPtr<SBCSeparator> Separator;
};
