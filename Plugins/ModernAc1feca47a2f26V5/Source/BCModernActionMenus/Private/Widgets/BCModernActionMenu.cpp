// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/BCModernActionMenu.h"

#include "Blueprint/WidgetTree.h"
#include "Editor/WidgetCompilerLog.h"
#include "Framework/Commands/InputChord.h"
#include "Widgets/Components/BCMAMLeafComponent.h"
#include "Widgets/Components/BCMAMRootComponent.h"

UBCModernActionMenu::UBCModernActionMenu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(true);
}

const FBCModernActionMenuStyle& UBCModernActionMenu::GetStyle() const
{
	if (Style)
	{
		return Style->GetDefaultObject<UBCModernActionMenuStyleAsset>()->Style;
	}

	return FBCModernActionMenuStyle::GetDefault();
}

void UBCModernActionMenu::SetStyle(TSubclassOf<UBCModernActionMenuStyleAsset> InStyle)
{
	Style = InStyle;
}

const TArray<UObject*>& UBCModernActionMenu::GetContextArray() const
{
	return Context;
}

UObject* UBCModernActionMenu::GetContextObject() const
{
	return Context.Num() > 0 ? Context[0] : nullptr;
}

void UBCModernActionMenu::SetContextArray(const TArray<UObject*>& InContext)
{
	Context = InContext;

	ContextChanged(GetContextObject(), Context);
	BP_ContextChanged(GetContextObject(), Context);

	OnContextChanged.Broadcast(Context);
}

void UBCModernActionMenu::SetContextObject(UObject* InContext)
{
	TArray<UObject*> NewContext;
	NewContext.Add(InContext);
	SetContextArray(NewContext);
}

#if WITH_EDITOR
void UBCModernActionMenu::ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree,
	IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledWidgetTree(BlueprintWidgetTree, CompileLog);

	static const FName RootComponentName("RootComponent");
	
	UWidget* RootComponentWidget = BlueprintWidgetTree.FindWidget(RootComponentName);
	
	if (RootComponentWidget == nullptr || RootComponentWidget != BlueprintWidgetTree.RootWidget)
	{
		CompileLog.Error(
			INVTEXT("Modern Action Menu must have a Root Component (Action Menu) as its root widget."));
	}
}

#endif

void UBCModernActionMenu::NotifyActionExecuted(UBCMAMActionComponent* ActionComponent)
{
	if (RootComponent && ShouldCloseOnActionExecuted())
	{
		RootComponent->FocusMenu();
	}
	
	OnActionExecuted.Broadcast(ActionComponent);
}

bool UBCModernActionMenu::ProcessMenuInput(const FKeyEvent& InKeyEvent)
{
	// Traverse the widget tree and look for LeafComponents that can handle this shortcut key.
 	if (WidgetTree && GetVisibility() != ESlateVisibility::HitTestInvisible)
 	{
 		const FInputChord InputChord = FInputChord(InKeyEvent.GetKey(), EModifierKey::FromBools(InKeyEvent.IsControlDown(), InKeyEvent.IsAltDown(), InKeyEvent.IsShiftDown(), InKeyEvent.IsCommandDown()));
 
 		TArray<UWidget*> Widgets;
 		WidgetTree->GetAllWidgets(Widgets);
 		
 		for (UWidget* Widget : Widgets)
 		{
 			if (UBCMAMLeafComponent* LeafComponent = Cast<UBCMAMLeafComponent>(Widget))
 			{
 				if (LeafComponent->ProcessMenuInputChord(InputChord))
 				{
 					return true;
 				}
 			}
 		}
 	}

 	return false;
}

FReply UBCModernActionMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (bProcessKeyInput && ProcessMenuInput(InKeyEvent))
	{
		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}
