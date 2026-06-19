// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMPanelComponent.h"
#include "BCMAMSectionComponent.generated.h"

class SBCSeparator;
class STextBlock;

/**
 * A component with a title that represents a section of content in the menu.
 */
UCLASS(DisplayName="Modern Section Component")
class BCMODERNACTIONMENUS_API UBCMAMSectionComponent : public UBCMAMPanelComponent
{
	GENERATED_BODY()

public:

	UBCMAMSectionComponent();

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetTitle(const FText& InTitle);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetShowSeparator(bool bInShowSeparator);

	virtual void SynchronizeProperties() override;

protected:

	/** The title of the section to display. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	FText Title;

	/** Whether to show a separator after the section. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	bool bShowSeparator;
	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	
	TSharedPtr<SWidget> Root;
	TSharedPtr<STextBlock> TextBlock;
	TSharedPtr<SBCSeparator> Separator;
};
