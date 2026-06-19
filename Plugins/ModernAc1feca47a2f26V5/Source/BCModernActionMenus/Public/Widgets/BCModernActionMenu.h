// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Util/BCModernActionMenusTypes.h"
#include "BCModernActionMenu.generated.h"

class UBCMAMRootComponent;
class UBCModernActionMenuStyleAsset;

/**
 * Primary User Widget for building action menus. Create a Widget Blueprint of this to create a menu for a specific use case,
 * and add Modern Action Menu Components to it.
 *
 * For menus that are meant to control a specific object, use the Context Object and Array functions to set the context.
 */
UCLASS(Abstract, DisplayName="BC Modern Action Menu")
class BCMODERNACTIONMENUS_API UBCModernActionMenu : public UUserWidget
{

	GENERATED_BODY()

public:

	UBCModernActionMenu(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	const FBCModernActionMenuStyle& GetStyle() const;

	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	void SetStyle(TSubclassOf<UBCModernActionMenuStyleAsset> InStyle);

	/** Get the currently set context array. */
	UFUNCTION(BlueprintCallable, DisplayName="Get Context (Array)", Category="Modern Action Menu")
	const TArray<UObject*>& GetContextArray() const;

	/** Get the currently set context as a single object. */
	UFUNCTION(BlueprintCallable, DisplayName="Get Context (Object)", Category="Modern Action Menu")
	UObject* GetContextObject() const;

	/** Set the context array. */
	UFUNCTION(BlueprintCallable, DisplayName="Set Context (Array)", Category="Modern Action Menu")
	void SetContextArray(const TArray<UObject*>& InContext);

	/** Set the context as a single object. */
	UFUNCTION(BlueprintCallable, DisplayName="Set Context (Object)", Category="Modern Action Menu")
	void SetContextObject(UObject* InContext);

	/** Override to provide functionality when the context has changed. */
	virtual void ContextChanged(const UObject* ContextObject, const TArray<UObject*>& ContextArray) {}

	/** Override to provide functionality when the context has changed. */
	UFUNCTION(BlueprintImplementableEvent, DisplayName="Context Changed", Category="Modern Action Menu")
	void BP_ContextChanged(const UObject* ContextObject, const TArray<UObject*>& ContextArray);

	/** Process external input through all possible hotkey handlers. */
	UFUNCTION(BlueprintCallable, Category="Modern Action Menu")
	bool ProcessMenuInput(const FKeyEvent& InKeyEvent);

	/** Called when the menu context has changed. */
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBCMAMContextDelegate OnContextChanged;

	/** Called when an action component has been executed. */
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBCMAMActionComponentDelegate OnActionExecuted;

#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree,
		IWidgetCompilerLog& CompileLog) const override;
#endif

	void NotifyActionExecuted(UBCMAMActionComponent* ActionComponent);

	bool ShouldCloseOnActionExecuted() const { return bCloseOnActionExecuted; }
	
	/** Asset used to style the menu and components. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	TSubclassOf<UBCModernActionMenuStyleAsset> Style;

	/** Close the menu automatically when an action is executed. Applies to submenus, or to the menu itself if it was spawned from an anchor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	bool bCloseOnActionExecuted = true;

	/** Process key input through all possible hotkey handlers. Disable this if you want to handle key input manually. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Modern Action Menu")
	bool bProcessKeyInput = true;
	
protected:

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category="Modern Action Menu")
	TObjectPtr<UBCMAMRootComponent> RootComponent;
	
	UPROPERTY(Transient)
	TArray<UObject*> Context;
};
