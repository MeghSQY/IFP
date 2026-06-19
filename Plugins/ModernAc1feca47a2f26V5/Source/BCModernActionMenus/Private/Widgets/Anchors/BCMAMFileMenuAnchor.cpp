// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Anchors/BCMAMFileMenuAnchor.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/BCModernActionMenu.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Anchors/IBCMAMFileMenuAnchorLabel.h"
#include "Widgets/Helpers/SBCMenuAnchor.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

void UBCMAMFileMenuAnchor::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Buttons.Reset();
	Labels.Reset();
	Root.Reset();
}

void UBCMAMFileMenuAnchor::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	RefreshLabels();
	RefreshEnabledTabs();
	RefreshHiddenTabs();

	SetOrientation(Orientation);

	RefreshButtonStyles();

	for (int i = 0; i < CustomLabelWidgets.Num(); i++)
	{
		if (Tabs.IsValidIndex(i) && CustomLabelWidgets[i]->Implements<UBCMAMFileMenuAnchorLabel>())
		{
			IBCMAMFileMenuAnchorLabel::Execute_OnTabSet(CustomLabelWidgets[i], Tabs[i], this);
		}
	}
}

void UBCMAMFileMenuAnchor::SetActiveTabIndex(int32 Index)
{
	SetActiveAnchorIndex(Index);
}

void UBCMAMFileMenuAnchor::SetActiveTab(FName ID)
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (Tabs[i].ID == ID)
		{
			SetActiveAnchorIndex(i);
			return;
		}
	}
}

int32 UBCMAMFileMenuAnchor::GetActiveTabIndex() const
{
	return ActiveAnchorIndex;
}

FName UBCMAMFileMenuAnchor::GetActiveTab() const
{
	if (Tabs.IsValidIndex(ActiveAnchorIndex))
	{
		return Tabs[ActiveAnchorIndex].ID;
	}

	return NAME_None;
}

void UBCMAMFileMenuAnchor::SetTabIndexEnabled(int32 Index, bool bEnabled)
{
	if (Tabs.IsValidIndex(Index))
	{
		Tabs[Index].bEnabled = bEnabled;

		RefreshEnabledTabs();
	}
}

void UBCMAMFileMenuAnchor::SetTabEnabled(FName ID, bool bEnabled)
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (Tabs[i].ID == ID)
		{
			SetTabIndexEnabled(i, bEnabled);
			return;
		}
	}
}

void UBCMAMFileMenuAnchor::SetTabIndexLabel(int32 Index, FText Label)
{
	if (Tabs.IsValidIndex(Index))
	{
		Tabs[Index].Label = Label;

		RefreshLabels();
	}
}

void UBCMAMFileMenuAnchor::SetTabLabel(FName ID, FText Label)
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (Tabs[i].ID == ID)
		{
			SetTabIndexLabel(i, Label);
			return;
		}
	}
}

void UBCMAMFileMenuAnchor::SetTabIndexHidden(int32 Index, bool bHidden)
{
	if (Tabs.IsValidIndex(Index))
	{
		Tabs[Index].bHidden = bHidden;
		RefreshHiddenTabs();
	}
}

void UBCMAMFileMenuAnchor::SetTabHidden(FName ID, bool bHidden)
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (Tabs[i].ID == ID)
		{
			SetTabIndexHidden(i, bHidden);
			return;
		}
	}
}

void UBCMAMFileMenuAnchor::SetOrientation(TEnumAsByte<EOrientation> InOrientation)
{
	Orientation = InOrientation;

	if (Root)
	{
		Root->SetOrientation(InOrientation);
	}
}

TSharedRef<SWidget> UBCMAMFileMenuAnchor::RebuildWidget()
{
	SAssignNew(Root, SStackBox);

	Buttons.SetNum(Tabs.Num());
	Labels.SetNum(CustomLabelWidgetClass ? 0 : Tabs.Num());
	CustomLabelWidgets.SetNum(CustomLabelWidgetClass ? Tabs.Num() : 0);
	MenuAnchors.SetNum(Tabs.Num());

	UBCModernFileMenuStyleAsset* CurrentStyle =
		Style ? Style->GetDefaultObject<UBCModernFileMenuStyleAsset>() : nullptr;

	for (int i = 0; i < Tabs.Num(); i++)
	{
		TSharedPtr<SWidget> LabelWidget = SNullWidget::NullWidget;

		if (CustomLabelWidgetClass)
		{
			CustomLabelWidgets[i] = CreateWidget<UUserWidget>(
				GetWorld(), CustomLabelWidgetClass);

			LabelWidget = CustomLabelWidgets[i]->TakeWidget();
		}
		else
		{
			SAssignNew(Labels[i], STextBlock).Text(Tabs[i].Label);

			LabelWidget = Labels[i];
		}

		Root->AddSlot()
		    .HAlign(HAlign_Fill)
		    .VAlign(VAlign_Fill)
		    .AutoSize()
		    .Padding(CurrentStyle ? CurrentStyle->SlotPadding : FMargin(0.f))
		[
			SAssignNew(MenuAnchors[i], SBCMenuAnchor)
			.PopupPadding(CurrentStyle ? CurrentStyle->MenuOffset : 0.f)
			.UseApplicationMenuStack(false)
			.Placement(Placement)
			.OnMenuOpenChanged_Lambda([this, i](bool bIsOpen)
			{
				if (!bIsOpen && i == ActiveAnchorIndex)
				{
					ActionMenu = nullptr;
				}
			})
			.OnGetMenuContent_Lambda([this, i]
			{
				if (Tabs[i].ActionMenuClass != nullptr && !Tabs[i].
				                                           ActionMenuClass->
				                                           HasAnyClassFlags(CLASS_Abstract))
				{
					if (UWorld* World = GetWorld())
					{
						ActionMenu = CreateWidget<UBCModernActionMenu>(
							World, Tabs[i].ActionMenuClass);

						if (ActionMenu)
						{
							ActionMenu->OnActionExecuted.AddUniqueDynamic(
								this, &UBCMAMFileMenuAnchor::HandleActionExecuted
							);

							const FBCModernActionMenuStyle& ActionMenuStyle = ActionMenu
								->GetStyle();

							if (TSharedPtr<SBCMenuAnchor> ActiveAnchor =
								GetActiveMenuAnchor())
							{
								// ActiveAnchor->SetTransitionDuration(
								// 	bWasAnotherMenuActive ? 0.f : Style.TransitionDuration);

								ActiveAnchor->SetTransitionDuration(ActionMenuStyle.TransitionDuration);
							}

							return ActionMenu->TakeWidget();
						}
					}
				}

				return SNullWidget::NullWidget;
			})
			[
				SAssignNew(Buttons[i], SButton)
				.OnClicked_Lambda([this, i]()
				{
					OnButtonClicked(i);
					return FReply::Handled();
				})
				.OnHovered_Lambda([this, i]() { OnButtonHovered(i); })
				[
					LabelWidget.ToSharedRef()
				]
			]
		];
	}

	if (CurrentStyle)
	{
		for (int i = 0; i < Labels.Num(); i++)
		{
			Labels[i]->SetTextStyle(&CurrentStyle->LabelStyle);
		}
	}

	return Root.ToSharedRef();
}

void UBCMAMFileMenuAnchor::OpenMenu()
{
	Super::OpenMenu();

	RefreshButtonStyles();
}

void UBCMAMFileMenuAnchor::CloseMenu()
{
	Super::CloseMenu();

	RefreshButtonStyles();
}

void UBCMAMFileMenuAnchor::OnButtonHovered(int32 Index)
{
	if (bOpenOnHover || IsOpen())
	{
		SetActiveAnchorIndex(Index);

		OpenMenu();
	}
}

void UBCMAMFileMenuAnchor::OnButtonClicked(int32 Index)
{
	if (IsOpen())
	{
		CloseMenu();
	}
	else
	{
		SetActiveAnchorIndex(Index);

		OpenMenu();
	}
}

void UBCMAMFileMenuAnchor::RefreshEnabledTabs()
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (Buttons.IsValidIndex(i) && Buttons[i])
		{
			Buttons[i]->SetEnabled(Tabs[i].bEnabled);
		}
	}
}

void UBCMAMFileMenuAnchor::RefreshLabels()
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (Labels.IsValidIndex(i) && Labels[i])
		{
			Labels[i]->SetText(Tabs[i].Label);
		}
	}
}

void UBCMAMFileMenuAnchor::RefreshHiddenTabs()
{
	for (int i = 0; i < Tabs.Num(); i++)
	{
		if (MenuAnchors.IsValidIndex(i) && MenuAnchors[i])
		{
			MenuAnchors[i]->SetVisibility(Tabs[i].bHidden ? EVisibility::Collapsed : EVisibility::Visible);
		}
	}
}

void UBCMAMFileMenuAnchor::RefreshButtonStyles()
{
	if (const UBCModernFileMenuStyleAsset* CurrentStyle = Style
		                                                      ? Style->GetDefaultObject<UBCModernFileMenuStyleAsset>()
		                                                      : nullptr)
	{
		for (int i = 0; i < Buttons.Num(); i++)
		{
			Buttons[i]->SetButtonStyle(ActiveAnchorIndex == i && IsOpen()
				                           ? &CurrentStyle->ActiveButtonStyle
				                           : &CurrentStyle->ButtonStyle);
		}
	}
}
