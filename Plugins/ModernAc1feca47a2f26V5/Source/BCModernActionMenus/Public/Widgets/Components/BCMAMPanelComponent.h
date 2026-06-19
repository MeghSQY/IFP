// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "BCMAMPanelComponent.generated.h"

/**
 * An action menu component that contains children in a vertical box layout.
 */
UCLASS(Abstract, DisplayName="BCMAM Panel Component")
class BCMODERNACTIONMENUS_API UBCMAMPanelComponent : public UPanelWidget
{
	GENERATED_BODY()

public:
	
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
	virtual const FText GetPaletteCategory() override;
#endif
	
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType=Content), Category="Modern Action Menu Component")
	UWidget* AddChildComponent(UWidget* Content);
	
protected:

	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	// End UPanelWidget

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	TSharedPtr<class SVerticalBox> MyVerticalBox;

	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
};
