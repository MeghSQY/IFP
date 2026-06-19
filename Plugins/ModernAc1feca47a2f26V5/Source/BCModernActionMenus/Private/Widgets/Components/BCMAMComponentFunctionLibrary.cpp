// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"

#if WITH_EDITOR
#include "WidgetBlueprint.h"
#endif

#include "Blueprint/WidgetTree.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/BCModernActionMenu.h"


#if WITH_EDITOR
void UBCMAMComponentFunctionLibrary::ValidateComponent(const UWidget* Widget, IWidgetCompilerLog& CompileLog)
{
	if (UWidgetTree* WidgetTree = GetWidgetTree(Widget))
	{
		if (UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(WidgetTree->GetOuter()))
		{
			if (!WidgetBlueprint->GeneratedClass->IsChildOf(UBCModernActionMenu::StaticClass()))
			{
				CompileLog.Error(
					INVTEXT("Modern Action Menu Components must be with a UBCMAMMenuContentWidget blueprint."));
			}
		}
	}
}
#endif

UBCModernActionMenu* UBCMAMComponentFunctionLibrary::GetParentActionMenu(const UWidget* Widget)
{
	if (const UWidgetTree* WidgetTree = GetWidgetTree(Widget))
	{
		// The menu content widget should be the outer of the widget tree
		return Cast<UBCModernActionMenu>(WidgetTree->GetOuter());
	}

	return nullptr;
}

UWidgetTree* UBCMAMComponentFunctionLibrary::GetWidgetTree(const UWidget* Widget)
{
	// Walk up the widget tree to find the parent menu content widget
	const UWidget* Parent = Widget;
	while (Parent)
	{
		if (const UWidget* NextParent = Parent->GetParent())
		{
			Parent = NextParent;
		}
		else
		{
			break;
		}
	}

	// Once there are no more parents, get the outer WidgetTree
	if (UWidgetTree* WidgetTree = Cast<UWidgetTree>(Parent->GetOuter()))
	{
		return WidgetTree;
	}

	return nullptr;
}

const FBCModernActionMenuStyle& UBCMAMComponentFunctionLibrary::GetStyle(const UWidget* Widget)
{
	if (const UBCModernActionMenu* MenuContent = GetParentActionMenu(Widget))
	{
		return MenuContent->GetStyle();
	}
	
	return FBCModernActionMenuStyle::GetDefault();
}
