// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BCMAMLeafComponent.h"
#include "Framework/Commands/InputChord.h"
#include "Util/BCModernActionMenusTypes.h"
#include "BCMAMRadioComponent.generated.h"

class SVerticalBox;
class SBCLeafButton;
class UBCModernActionMenuItemButtonStyleAsset;

/** Represents an item in a radio component. */
USTRUCT(BlueprintType)
struct FBCMAMRadioItem
{
	GENERATED_BODY()

	/** The ID of the item used to identify it in events and functions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu Component")
	FName ID = NAME_None;

	/** The displayed label text of the item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu Component")
	FText Label;

	/** The shortcut of the item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Modern Action Menu Component")
	FInputChord Shortcut;
};

/**
 * A component that displays a group of radio buttons, where only one can be selected at a time.
 */
UCLASS(DisplayName="Modern Radio Component")
class BCMODERNACTIONMENUS_API UBCMAMRadioComponent : public UBCMAMLeafComponent
{
	GENERATED_BODY()

public:

	UBCMAMRadioComponent();

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetSelectedID(FName ID);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetSelectedIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	FName GetSelectedID();

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	int32 GetSelectedIndex();

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetItems(TArray<FBCMAMRadioItem> InItems);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void AddItem(FBCMAMRadioItem InItem);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void RemoveItem(FName InID);

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void ClearItems();
	
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu Component")
	void SetButtonStyleOverride(TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> InButtonStyleOverride);

	/** Called when the selected ID changes. */
	UPROPERTY(BlueprintAssignable, Category=Events, DisplayName="On Selected ID Changed")
	FBCMAMNameDelegate OnSelectedIDChanged;

	/** Called when the selected index changes. */
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBCMAMIntDelegate OnSelectedIndexChanged;
	
	virtual bool ProcessMenuInputChord(const FInputChord& InChord) override;
	
protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> ButtonStyleOverride;

	/** The items to display in the radio component. Each one will be displayed as a radio button. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component", meta=(DesignerRebuild))
	TArray<FBCMAMRadioItem> Items;

	/** The ID of the currently selected item. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu Component")
	FName SelectedID = NAME_None;

	FReply HandleButtonClicked(FName ID);

	void HandleButtonHovered(FName ID);

	void CreateItem(const FBCMAMRadioItem& InItem);
	void SynchronizeItem(const TSharedPtr<SBCLeafButton>& Button, const FBCMAMRadioItem& Item);

	TSharedPtr<SVerticalBox> VerticalBox;
	TArray<TSharedPtr<SBCLeafButton>> LeafButtons;
};
