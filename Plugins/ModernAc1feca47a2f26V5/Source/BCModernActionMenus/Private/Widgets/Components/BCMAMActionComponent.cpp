// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMActionComponent.h"

#include "Actions/BCMAMActionBase.h"
#include "Components/HorizontalBox.h"
#include "Framework/SlateDelegates.h"
#include "Framework/Application/SlateApplication.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/BCModernActionMenu.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Helpers/SBCLeafButton.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

UBCMAMActionComponent::UBCMAMActionComponent()
{
	bShowIcon = false;
	Label = NSLOCTEXT("BCModernActionMenus", "ActionLabel", "Action");
}

void UBCMAMActionComponent::SetShowIcon(bool bShow)
{
	bShowIcon = bShow;

	if (LeafButton && LeafButton->GetIcon())
	{
		const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

		LeafButton->GetIcon()->SetVisibility(bShowIcon
			                          ? EVisibility::SelfHitTestInvisible
			                          : Style.bMaintainLeftColumnWidth
			                          ? EVisibility::Hidden
			                          : EVisibility::Collapsed);
	}
}

void UBCMAMActionComponent::SetIcon(const FSlateBrush& InIcon)
{
	Icon = InIcon;
	
	if (LeafButton)
	{
		LeafButton->SetIconBrush(&InIcon);
	}
}

void UBCMAMActionComponent::SetAction(UBCMAMActionBase* InAction)
{
	Action = InAction;
}

bool UBCMAMActionComponent::ProcessMenuInputChord(const FInputChord& InChord)
{
	if (InChord == Shortcut)
	{
		ExecuteAction();

		return true;
	}

	return false;
}

void UBCMAMActionComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	SetIcon(Icon);
	SetShowIcon(bShowIcon);
}

FReply UBCMAMActionComponent::HandleButtonClicked()
{
	ExecuteAction();
	
	return FReply::Handled();
}

void UBCMAMActionComponent::ExecuteAction()
{
	if (UBCModernActionMenu* ParentMenu = UBCMAMComponentFunctionLibrary::GetParentActionMenu(this))
	{
		if (Action)
		{
			Action->Execute(ParentMenu);
		}

		ParentMenu->NotifyActionExecuted(this);
	}

	OnExecuted.Broadcast(this);
}
