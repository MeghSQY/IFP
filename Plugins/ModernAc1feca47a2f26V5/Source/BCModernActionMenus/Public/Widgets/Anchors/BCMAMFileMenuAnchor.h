// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMAnchorBase.h"
#include "BCMAMFileMenuAnchor.generated.h"

class SStackBox;
class STextBlock;
class SButton;

/** A single tab in a file menu anchor. */
USTRUCT(BlueprintType, DisplayName="Modern File Menu Anchor Tab", Category="Modern Action Menu")
struct FBCMAMFileMenuAnchorTab
{
	GENERATED_BODY()

	/** The ID of the tab. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu")
	FName ID;

	/** The label of the tab. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu")
	FText Label;

	/** The class of the tab's action menu to summon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu")
	TSubclassOf<UBCModernActionMenu> ActionMenuClass;

	/** Whether the tab is enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu")
	bool bEnabled = true;

	/** Whether the tab is hidden. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu")
	bool bHidden = false;
};

/**
 * An anchor that controls a file menu.
 *
 * A file menu is a collection of tabs that each summon their own action menu.
 * When a tab is clicked, its action menu is summoned. When a menu is already open,
 * hovering over another tab will switch to that menu automatically.
 */
UCLASS(DisplayName="Modern File Menu Anchor")
class BCMODERNACTIONMENUS_API UBCMAMFileMenuAnchor : public UBCMAMAnchorBase
{
	GENERATED_BODY()

public:

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;
	
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetActiveTabIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetActiveTab(FName ID);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	int32 GetActiveTabIndex() const;

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	FName GetActiveTab() const;

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetTabIndexEnabled(int32 Index, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetTabEnabled(FName ID, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetTabIndexLabel(int32 Index, FText Label);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetTabLabel(FName ID, FText Label);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetTabIndexHidden(int32 Index, bool bHidden);
	
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetTabHidden(FName ID, bool bHidden);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetOrientation(TEnumAsByte<EOrientation> InOrientation);
	
protected:

	/** The orientation of the file menu. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	TEnumAsByte<EOrientation> Orientation;

	/** The tabs of the file menu. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	TArray<FBCMAMFileMenuAnchorTab> Tabs;

	/** An optional custom label widget to spawn instead of the default text label. Must implement the BCMAMFileMenuAnchorLabel interface, and can use the OnTabSet() function to configure its visuals. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu", meta=(MustImplement = "/Script/BCModernActionMenus.BCMAMFileMenuAnchorLabel", DesignerRebuild))
	TSubclassOf<UUserWidget> CustomLabelWidgetClass;

	/** Whether the menu should initially open on hover. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	bool bOpenOnHover;

	/** An optional style override for the file menu. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	TSubclassOf<UBCModernFileMenuStyleAsset> Style;

	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void OpenMenu() override;
	virtual void CloseMenu() override;

	void OnButtonHovered(int32 Index);
	void OnButtonClicked(int32 Index);

	void RefreshEnabledTabs();
	void RefreshLabels();
	void RefreshHiddenTabs();
	void RefreshButtonStyles();

	TSharedPtr<SStackBox> Root;
	TArray<TSharedPtr<SButton>> Buttons;
	TArray<TSharedPtr<STextBlock>> Labels;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UUserWidget>> CustomLabelWidgets;
	
};
