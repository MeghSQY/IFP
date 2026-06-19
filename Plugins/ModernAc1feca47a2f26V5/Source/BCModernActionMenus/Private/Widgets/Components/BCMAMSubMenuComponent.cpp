// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMSubMenuComponent.h"

#include "Components/HorizontalBox.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Helpers/SBCMenuAnchor.h"
#include "Widgets/SBCModernActionMenuPanel.h"
#include "Widgets/Helpers/SBCVisualAttachmentBox.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"

UBCMAMSubMenuComponent::UBCMAMSubMenuComponent(): bShowIcon(false)
{
	Label = NSLOCTEXT("BCModernActionMenus", "SubMenuLabel", "Sub Menu");
}

void UBCMAMSubMenuComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	if (ButtonWidget.IsValid())
	{
		RefreshButtonStyle();
		ButtonWidget->SetContentPadding(Style.ItemPadding);
	}

	if (IconWidget.IsValid())
	{
		IconWidget->SetImage(&Icon);
		IconWidget->SetDesiredSizeOverride(Style.IconSize);
		IconWidget->SetVisibility(bShowIcon ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed);
		IconWidget->SetColorAndOpacity(ButtonStyleOverride ? FLinearColor::White : Style.BaseTextStyle.ColorAndOpacity);
	}

	if (LabelWidget.IsValid())
	{
		LabelWidget->SetText(Label);
		LabelWidget->SetTextStyle(ButtonStyleOverride ? &ButtonStyleOverride->GetDefaultObject<UBCModernActionMenuItemButtonStyleAsset>()->TextStyle : &Style.BaseTextStyle);
	}

	if (ArrowWidget.IsValid())
	{
		ArrowWidget->SetImage(&Style.ArrowBrush);
	}

	if (MenuAnchor)
	{
		MenuAnchor->SetTransitionDuration(Style.TransitionDuration);
	}
}

#if WITH_EDITOR
void UBCMAMSubMenuComponent::OnDescendantSelectedByDesigner(UWidget* DescendantWidget)
{
	Super::OnDescendantSelectedByDesigner(DescendantWidget);

	if (Visual && Panel)
	{
		Visual->SetVisibility(EVisibility::Visible);
		Visual->SetContent(Panel.ToSharedRef());
	}
}

void UBCMAMSubMenuComponent::OnDescendantDeselectedByDesigner(UWidget* DescendantWidget)
{
	Super::OnDescendantDeselectedByDesigner(DescendantWidget);

	if (Visual)
	{
		Visual->SetVisibility(EVisibility::Collapsed);
		Visual->SetContent(SNullWidget::NullWidget);
	}
}

void UBCMAMSubMenuComponent::OnSelectedByDesigner()
{
	Super::OnSelectedByDesigner();

	if (Visual && Panel)
	{
		Visual->SetVisibility(EVisibility::Visible);
		Visual->SetContent(Panel.ToSharedRef());
	}
}

void UBCMAMSubMenuComponent::OnDeselectedByDesigner()
{
	Super::OnDeselectedByDesigner();

	if (Visual)
	{
		Visual->SetVisibility(EVisibility::Collapsed);
		Visual->SetContent(SNullWidget::NullWidget);
	}
}
#endif

TSharedRef<SWidget> UBCMAMSubMenuComponent::RebuildWidget()
{
	TSharedRef<SWidget> VerticalBox = Super::RebuildWidget();

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	const FButtonStyle& ActiveButtonStyle = ButtonStyleOverride
		                                        ? ButtonStyleOverride->GetDefaultObject<
			                                        UBCModernActionMenuItemButtonStyleAsset>()->Style
		                                        : Style.ItemButtonStyle;

	TSharedRef<SWidget> SlotContent = SNullWidget::NullWidget;

	SAssignNew(Panel, SBCModernActionMenuPanel)
	.Content(VerticalBox)
	.Style(&Style)
	.OnFocusLost(FSimpleDelegate::CreateUObject(this, &UBCMAMSubMenuComponent::HandleFocusLost));

	if (IsDesignTime())
	{
		SAssignNew(Visual, SBCVisualAttachmentBox)
		.Padding(FMargin(Style.MenuPadding.Right, 0.f, 0.f, 0.f))
			[
				SNullWidget::NullWidget
			];

		Visual->SetContentAnchor(FVector2D(-1.f, 0.f));

		SlotContent = Visual.ToSharedRef();
	}
	else
	{
		SAssignNew(MenuAnchor, SBCMenuAnchor)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.Placement(EMenuPlacement::MenuPlacement_MenuRight)
		.UseApplicationMenuStack(false)
		.Method(EPopupMethod::UseCurrentWindow)
		// .PopupPadding(Style.MenuPadding.Right)
		.MenuContent(Panel)
		[
			SNew(SSpacer)
		];

		SlotContent = MenuAnchor.ToSharedRef();
	}

	SAssignNew(ButtonWidget, SButton)
	.HAlign(HAlign_Fill)
	.OnHovered(FSimpleDelegate::CreateUObject(this, &UBCMAMSubMenuComponent::HandleButtonHovered))
	.OnClicked(FOnClicked::CreateUObject(this, &UBCMAMSubMenuComponent::HandleButtonClicked))
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(
				FMargin(0.f, 0.f, Style.ColumnPadding, 0.f))
			[
				SAssignNew(IconWidget, SImage)
			]
			+ SHorizontalBox::Slot().FillWidth(1.f).VAlign(VAlign_Center)
			[
				SAssignNew(LabelWidget, STextBlock)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(
				FMargin(Style.ColumnPadding, 0.f, 0.f, 0.f))
			[
				SAssignNew(ArrowWidget, SImage)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding((Style.ItemPadding + ActiveButtonStyle.NormalPadding) * -1.0f)
		[
			SlotContent
		]
	];

	return ButtonWidget.ToSharedRef();
}

void UBCMAMSubMenuComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MenuAnchor.Reset();
	ButtonWidget.Reset();
	IconWidget.Reset();
	ArrowWidget.Reset();
	LabelWidget.Reset();

	Panel.Reset();
	Visual.Reset();
}

void UBCMAMSubMenuComponent::RefreshButtonStyle()
{
	if (ButtonWidget.IsValid())
	{
		const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

		if (MenuAnchor && MenuAnchor->IsDesiredOpen())
		{
			ButtonWidget->SetButtonStyle(ButtonStyleOverride
				                             ? &ButtonStyleOverride->GetDefaultObject<
					                             UBCModernActionMenuItemButtonStyleAsset>()->HighlightedStyle
				                             : &Style.HighlightedItemButtonStyle);
		}
		else
		{
			ButtonWidget->SetButtonStyle(ButtonStyleOverride
				                             ? &ButtonStyleOverride->GetDefaultObject<
					                             UBCModernActionMenuItemButtonStyleAsset>()->Style
				                             : &Style.ItemButtonStyle);
		}
	}
}

void UBCMAMSubMenuComponent::HandleFocusLost()
{
	if (ButtonWidget && ButtonWidget->IsPressed())
	{
		return;
	}

	if (MenuAnchor && MenuAnchor->IsDesiredOpen())
	{
		MenuAnchor->SetIsOpen(false);
		RefreshButtonStyle();
	}
}

void UBCMAMSubMenuComponent::HandleButtonHovered()
{
	if (MenuAnchor && !MenuAnchor->IsDesiredOpen())
	{
		MenuAnchor->SetIsOpen(true);

		RefreshButtonStyle();
		if (Panel)
		{
			Panel->FocusMenu();
		}
	}
}

FReply UBCMAMSubMenuComponent::HandleButtonClicked()
{
	if (MenuAnchor && !MenuAnchor->IsDesiredOpen())
	{
		MenuAnchor->SetIsOpen(true);

		RefreshButtonStyle();
	}

	if (Panel)
	{
		Panel->FocusMenu();
	}

	return FReply::Handled();
}
