// Copyright Bartschi Creative 2025. All rights reserved.

#include "Widgets/Helpers/BCMenu.h"
#include "Widgets/SWidget.h"
#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"

FBCMenuBase::FBCMenuBase(TSharedRef<SWidget> InContent, const bool bCollapsedByParent)
	: Content(InContent)
	, bDismissing(false)
	, bIsCollapsedByParent(bCollapsedByParent)
{
}

FBCMenuInWindow::FBCMenuInWindow(TSharedRef<SWindow> InWindow, TSharedRef<SWidget> InContent, const bool bIsCollapsedByParent)
	: FBCMenuBase(InContent, bIsCollapsedByParent)
	, Window(InWindow)
{
}

TSharedPtr<SWindow> FBCMenuInWindow::GetParentWindow() const
{
	// Return the menu's window
	return Window.Pin();
}

void FBCMenuInWindow::Dismiss()
{
	if (!bDismissing)
	{
		bDismissing = true;
		OnMenuDismissed.Broadcast(AsShared());

		// Close the window
		// Will cause the window destroy code to call back into the stack to clean up
		TSharedPtr<SWindow> WindowPinned = Window.Pin();
		if (WindowPinned.IsValid())
		{
			WindowPinned->RequestDestroyWindow();
		}
	}
}


FBCMenuInPopup::FBCMenuInPopup(TSharedRef<SWidget> InContent, const bool bIsCollapsedByParent)
	: FBCMenuBase(InContent, bIsCollapsedByParent)
{
}

TSharedPtr<SWindow> FBCMenuInPopup::GetParentWindow() const
{
	// Return the menu's window
	return FSlateApplication::Get().GetVisibleMenuWindow();
}

void FBCMenuInPopup::Dismiss()
{
	if (!bDismissing)
	{
		bDismissing = true;
		OnMenuDismissed.Broadcast(AsShared());
	}
}


FBCMenuInHostWidget::FBCMenuInHostWidget(TSharedRef<IMenuHost> InHost, const TSharedRef<SWidget>& InContent, const bool bIsCollapsedByParent)
	: FBCMenuBase(InContent, bIsCollapsedByParent)
	, MenuHost(InHost)
{
}

TSharedPtr<SWindow> FBCMenuInHostWidget::GetParentWindow() const
{
	// Return the menu's window
	TSharedPtr<IMenuHost> HostPinned = MenuHost.Pin();
	if (HostPinned.IsValid())
	{
		return HostPinned->GetMenuWindow();
	}
	return TSharedPtr<SWindow>();
}

void FBCMenuInHostWidget::Dismiss()
{
	if (!bDismissing)
	{
		bDismissing = true;
		TSharedPtr<IMenuHost> HostPinned = MenuHost.Pin();
		if (HostPinned.IsValid())
		{
			HostPinned->OnMenuDismissed();
		}
		OnMenuDismissed.Broadcast(AsShared());
	}
}

bool FBCMenuInHostWidget::UsingApplicationMenuStack() const
{
	TSharedPtr<IMenuHost> HostPinned = MenuHost.Pin();
	if (HostPinned.IsValid())
	{
		return HostPinned->UsingApplicationMenuStack();
	}
	return true;
}
