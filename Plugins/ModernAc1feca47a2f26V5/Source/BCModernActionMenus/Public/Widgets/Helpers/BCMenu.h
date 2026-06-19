// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/PopupMethodReply.h"
#include "Framework/Application/IMenu.h"

class SWidget;
class SWindow;

/**
 * Represents the base class of popup menus. Used internally with SBCMenuAnchor.
 */
class FBCMenuBase : public IMenu, public TSharedFromThis<FBCMenuBase>
{
public:
	virtual FOnMenuDismissed& GetOnMenuDismissed() override { return OnMenuDismissed; }
	virtual TSharedPtr<SWidget> GetContent() const override { return Content; }
	bool IsCollapsedByParent() const { return bIsCollapsedByParent; }
	virtual bool UsingApplicationMenuStack() const override { return true; }

protected:
	FBCMenuBase(TSharedRef<SWidget> InContent, const bool bCollapsedByParent);

	FOnMenuDismissed OnMenuDismissed;
	TSharedRef<SWidget> Content;
	bool bDismissing;
	bool bIsCollapsedByParent;
};

/**
 * Represents a popup menu that is shown in its own SWindow. Used internally with SBCMenuAnchor.
 */
class FBCMenuInWindow : public FBCMenuBase
{
public:
	FBCMenuInWindow(TSharedRef<SWindow> InWindow, TSharedRef<SWidget> InContent, const bool bIsCollapsedByParent);
	virtual ~FBCMenuInWindow() {}

	virtual EPopupMethod GetPopupMethod() const override { return EPopupMethod::CreateNewWindow; }
	virtual TSharedPtr<SWindow> GetParentWindow() const override;
	virtual TSharedPtr<SWindow> GetOwnedWindow() const override { return GetParentWindow(); }
	virtual void Dismiss() override;

private:
	TWeakPtr<SWindow> Window;
};

/**
 * Represents a popup menu that is shown in the same window as the widget that summons it.
 */
class FBCMenuInPopup : public FBCMenuBase
{
public:
	FBCMenuInPopup(TSharedRef<SWidget> InContent, const bool bIsCollapsedByParent);
	virtual ~FBCMenuInPopup() {}

	virtual EPopupMethod GetPopupMethod() const { return EPopupMethod::UseCurrentWindow; }
	virtual TSharedPtr<SWindow> GetParentWindow() const;
	virtual TSharedPtr<SWindow> GetOwnedWindow() const { return TSharedPtr<SWindow>(); }
	virtual void Dismiss() override;
};

/**
* Represents a popup menu that is shown in a host widget (such as a menu anchor).
*/
class FBCMenuInHostWidget : public FBCMenuBase
{
public:
	FBCMenuInHostWidget(TSharedRef<IMenuHost> InHost, const TSharedRef<SWidget>& InContent, const bool bIsCollapsedByParent);
	virtual ~FBCMenuInHostWidget() {}

	virtual EPopupMethod GetPopupMethod() const { return EPopupMethod::UseCurrentWindow; }
	virtual TSharedPtr<SWindow> GetParentWindow() const;
	virtual TSharedPtr<SWindow> GetOwnedWindow() const { return TSharedPtr<SWindow>(); }
	virtual void Dismiss() override;
	virtual bool UsingApplicationMenuStack() const override;

private:
	TWeakPtr<IMenuHost> MenuHost;
};
