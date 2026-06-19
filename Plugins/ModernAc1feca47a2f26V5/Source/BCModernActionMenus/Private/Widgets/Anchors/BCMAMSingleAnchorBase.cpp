// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Anchors/BCMAMSingleAnchorBase.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/BCModernActionMenu.h"
#include "Widgets/Helpers/SBCMenuAnchor.h"
#include "Widgets/Layout/SBorder.h"

UBCMAMSingleAnchorBase::UBCMAMSingleAnchorBase()
{
}

#if WITH_EDITOR
const FText UBCMAMSingleAnchorBase::GetPaletteCategory()
{
	return INVTEXT("Modern Action Menu Anchors");
}
#endif

void UBCMAMSingleAnchorBase::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	ReleaseNamedSlotSlateResources(bReleaseChildren);
}

static const FName TargetName(TEXT("Target"));

void UBCMAMSingleAnchorBase::GetSlotNames(TArray<FName>& SlotNames) const
{
	SlotNames.Add(TargetName);
}

UWidget* UBCMAMSingleAnchorBase::GetContentForSlot(FName SlotName) const
{
	if (SlotName == TargetName)
	{
		return TargetContent;
	}

	return nullptr;
}

void UBCMAMSingleAnchorBase::SetContentForSlot(FName SlotName, UWidget* Content)
{
	if (SlotName == TargetName)
	{
		if (TargetContent)
		{
			const bool bReleaseChildren = true;
			TargetContent->ReleaseSlateResources(bReleaseChildren);
		}

		TargetContent = Content;
	}
}

void UBCMAMSingleAnchorBase::BeginDestroy()
{
	Super::BeginDestroy();
}

TSharedRef<SWidget> UBCMAMSingleAnchorBase::RebuildWidget()
{
	TSharedRef<SWidget> TargetWidget = TargetContent ? TargetContent->TakeWidget() : SNullWidget::NullWidget;

	MenuAnchors.SetNum(1);
	
	MenuAnchors[0] = SNew(SBCMenuAnchor)
			.UseApplicationMenuStack(false)
			.Placement(Placement)
			.OnMenuOpenChanged_Lambda([&](bool bIsOpen)
			{
				if (!bIsOpen)
				{
					ActionMenu = nullptr;
				}
			})
		.
		OnGetMenuContent_Lambda([&]
		{
			if (ActionMenuClass != nullptr && !ActionMenuClass->HasAnyClassFlags(CLASS_Abstract))
			{
				if (UWorld* World = GetWorld())
				{
					ActionMenu = CreateWidget<UBCModernActionMenu>(World, ActionMenuClass);

					if (ActionMenu)
					{
						ActionMenu->OnActionExecuted.AddUniqueDynamic(this, &UBCMAMSingleAnchorBase::HandleActionExecuted);
						
						const FBCModernActionMenuStyle& Style = ActionMenu->GetStyle();

						if (TSharedPtr<SBCMenuAnchor> ActiveAnchor = GetActiveMenuAnchor())
						{
							ActiveAnchor->SetTransitionDuration(Style.TransitionDuration);
						}
						
						return ActionMenu->TakeWidget();
					}
				}
			}

			return SNullWidget::NullWidget;
		})
		[
			SNew(SBorder)
			.OnMouseButtonDown(BIND_UOBJECT_DELEGATE(FPointerEventHandler, HandleMouseButtonDown))
			.OnMouseButtonUp(BIND_UOBJECT_DELEGATE(FPointerEventHandler, HandleMouseButtonUp))
			.BorderImage(nullptr)
			.Padding(0.f)
			[
				TargetWidget
			]
		];

	return MenuAnchors[0].ToSharedRef();
}

FReply UBCMAMSingleAnchorBase::HandleMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}

FReply UBCMAMSingleAnchorBase::HandleMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	return FReply::Unhandled();
}


