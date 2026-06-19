// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMPanelComponent.h"
#include "BCMAMSubMenuComponent.generated.h"

class SBCVisualAttachmentBox;
class UBCModernActionMenuItemButtonStyleAsset;
class SBCModernActionMenuPanel;
class STextBlock;
class SImage;
class SButton;
class SBCMenuAnchor;

/**
 * A component that adds a sub menu to the menu. The trigger is a menu item with a label and an arrow.
 */
UCLASS(DisplayName="Modern Sub Menu Component")
class BCMODERNACTIONMENUS_API UBCMAMSubMenuComponent : public UBCMAMPanelComponent
{
	GENERATED_BODY()
	
public:

	UBCMAMSubMenuComponent();

	virtual void SynchronizeProperties() override;

#if WITH_EDITOR
	virtual void OnDescendantSelectedByDesigner(UWidget* DescendantWidget) override;
	virtual void OnDescendantDeselectedByDesigner(UWidget* DescendantWidget) override;
	virtual void OnSelectedByDesigner() override;
	virtual void OnDeselectedByDesigner() override;
#endif
	
protected:

	/** The label of the sub menu trigger item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	FText Label;

	/** Whether to show the icon of the sub menu trigger item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(InlineEditConditionToggle), Category="Modern Action Menu Component")
	bool bShowIcon;

	/** The icon of the sub menu trigger item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition=bShowIcon), Category="Modern Action Menu Component")
	FSlateBrush Icon;

	/** The style override of the sub menu trigger item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> ButtonStyleOverride;

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	
	void RefreshButtonStyle();
	void HandleFocusLost();
	void HandleButtonHovered();
	FReply HandleButtonClicked();

	TSharedPtr<SBCMenuAnchor> MenuAnchor;
	TSharedPtr<SButton> ButtonWidget;
	TSharedPtr<SImage> IconWidget;
	TSharedPtr<SImage> ArrowWidget;
	TSharedPtr<STextBlock> LabelWidget;
	
	TSharedPtr<SBCModernActionMenuPanel> Panel;
	TSharedPtr<SBCVisualAttachmentBox> Visual;
	
};
