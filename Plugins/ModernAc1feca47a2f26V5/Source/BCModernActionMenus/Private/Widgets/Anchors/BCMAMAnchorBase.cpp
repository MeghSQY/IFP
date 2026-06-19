// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Anchors/BCMAMAnchorBase.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/BCModernActionMenu.h"
#include "Widgets/Helpers/SBCMenuAnchor.h"

UBCMAMAnchorBase::UBCMAMAnchorBase()
{
	ActiveAnchorIndex = 0;
}

#if WITH_EDITOR
const FText UBCMAMAnchorBase::GetPaletteCategory()
{
	return INVTEXT("Modern Action Menu Anchors");
}
#endif

void UBCMAMAnchorBase::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MenuAnchors.Reset();
}

void UBCMAMAnchorBase::SetIsOpen(bool bOpen)
{
	if (bOpen)
	{
		OpenMenu();
	}
	else
	{
		CloseMenu();
	}
}

void UBCMAMAnchorBase::ToggleOpen()
{
	TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor();
	if (!ActiveAnchor.IsValid())
	{
		return;
	}

	SetIsOpen(!ActiveAnchor->IsDesiredOpen());
}

bool UBCMAMAnchorBase::IsOpen() const
{
	TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor();
	return ActiveAnchor.IsValid() && ActiveAnchor->IsDesiredOpen();
}

void UBCMAMAnchorBase::HandleActionExecuted(UBCMAMActionComponent* ActionComponent)
{
	if (ActionMenu && ActionMenu->ShouldCloseOnActionExecuted())
	{
		CloseMenu();
	}
}

void UBCMAMAnchorBase::OnGlobalFocusChanging(const FFocusEvent& InFocusEvent,
                                             const FWeakWidgetPath& InOldFocusedWidgetPath,
                                             const TSharedPtr<SWidget>& InOldFocusedWidget,
                                             const FWidgetPath& InNewFocusedWidgetPath,
                                             const TSharedPtr<SWidget>& InNewFocusedWidget)
{
	if (!GetActiveMenuAnchor().IsValid()) return;
	
	const bool bDecendantNewlyFocused = InNewFocusedWidgetPath.ContainsWidget(GetActiveMenuAnchor().Get());
	if (!bDecendantNewlyFocused)
	{
		SetIsOpen(false);
	}
}

void UBCMAMAnchorBase::OpenMenu()
{
	TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor();
	
	if (ActiveAnchor && !ActiveAnchor->IsDesiredOpen())
	{
		FSlateApplication::Get().OnFocusChanging().AddUObject(this, &UBCMAMAnchorBase::OnGlobalFocusChanging);

		ActiveAnchor->SetIsOpen(true);

		if (ActionMenu)
		{
			OnMenuOpened.Broadcast(ActionMenu);
			ActionMenu->SetFocus();
			ActionMenu->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UBCMAMAnchorBase::CloseMenu()
{
	TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor();

	if (ActiveAnchor && ActiveAnchor->IsDesiredOpen())
	{
		FSlateApplication::Get().OnFocusChanging().RemoveAll(this);

		if (ActionMenu)
		{
			OnMenuClosed.Broadcast(ActionMenu);
			ActionMenu->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		ActiveAnchor->SetIsOpen(false);

		if (!bFadeOutOnClose)
		{
			ActiveAnchor->FinishCloseImmediately();
		}
	}
}

TSharedPtr<SBCMenuAnchor> UBCMAMAnchorBase::GetActiveMenuAnchor() const
{
	return MenuAnchors.IsValidIndex(ActiveAnchorIndex) ? MenuAnchors[ActiveAnchorIndex] : nullptr;
}

void UBCMAMAnchorBase::SetActiveAnchorIndex(int32 Index)
{
	bool bIsNewIndexValid = Index >= 0 && Index < MenuAnchors.Num();

	if (!bIsNewIndexValid) return;
	
	// If the active anchor is already open, close it and open the new active anchor
	TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor();

	bWasAnotherMenuActive = ActiveAnchor.IsValid() && ActiveAnchor->IsDesiredOpen();
	CloseMenu();
	
	ActiveAnchorIndex = Index;

	if (bWasAnotherMenuActive)
	{
		OpenMenu();
		
		bWasAnotherMenuActive = false;
	}

}

