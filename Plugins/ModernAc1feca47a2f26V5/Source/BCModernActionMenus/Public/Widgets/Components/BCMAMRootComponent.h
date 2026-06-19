// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMPanelComponent.h"
#include "BCMAMRootComponent.generated.h"

class SBCModernActionMenuPanel;

/**
 * The root component of a modern action menu. Holds the primary menu panel.
 */
UCLASS(DisplayName="Modern Root Component")
class BCMODERNACTIONMENUS_API UBCMAMRootComponent : public UBCMAMPanelComponent
{
	GENERATED_BODY()

public:

	UBCMAMRootComponent();
	
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetUseShadow(bool bInUseShadow);

	void FocusMenu();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	bool bUseShadow;

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

	TSharedPtr<SBCModernActionMenuPanel> Panel;
};
