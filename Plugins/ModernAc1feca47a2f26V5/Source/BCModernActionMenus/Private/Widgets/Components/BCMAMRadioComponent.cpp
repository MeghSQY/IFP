// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMRadioComponent.h"

#include "Framework/Application/SlateApplication.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Helpers/SBCLeafButton.h"
#include "Widgets/Input/SButton.h"

UBCMAMRadioComponent::UBCMAMRadioComponent()
{
}

void UBCMAMRadioComponent::SetSelectedID(FName ID)
{
	SelectedID = ID;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (LeafButtons.IsValidIndex(i))
		{
			SynchronizeItem(LeafButtons[i], Items[i]);
		}
	}
}

void UBCMAMRadioComponent::SetSelectedIndex(int32 Index)
{
	SetSelectedID(Items.IsValidIndex(Index) ? Items[Index].ID : NAME_None);
}

FName UBCMAMRadioComponent::GetSelectedID()
{
	return SelectedID;
}

int32 UBCMAMRadioComponent::GetSelectedIndex()
{
	int32 Index = INDEX_NONE;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ID == SelectedID)
		{
			Index = i;
			break;
		}
	}

	return Index;
}

void UBCMAMRadioComponent::AddItem(FBCMAMRadioItem InItem)
{
	CreateItem(InItem);

	Items.Add(InItem);
}

void UBCMAMRadioComponent::RemoveItem(FName InID)
{
	int32 IndexToRemove = INDEX_NONE;
	
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ID == InID)
		{
			IndexToRemove = i;
			break;
		}
	}

	if (IndexToRemove != INDEX_NONE)
	{
		Items.RemoveAt(IndexToRemove);

		if (LeafButtons.IsValidIndex(IndexToRemove) && VerticalBox)
		{
			VerticalBox->RemoveSlot(LeafButtons[IndexToRemove].ToSharedRef());
			LeafButtons.RemoveAt(IndexToRemove);
		}
	}
}

void UBCMAMRadioComponent::ClearItems()
{
	Items.Reset();
	LeafButtons.Reset();

	if (VerticalBox)
	{
		VerticalBox->ClearChildren();
	}
}

void UBCMAMRadioComponent::SetButtonStyleOverride(
	TSubclassOf<UBCModernActionMenuItemButtonStyleAsset> InButtonStyleOverride)
{
	ButtonStyleOverride = InButtonStyleOverride;

	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	for (TSharedPtr<SBCLeafButton>& LeafButton : LeafButtons)
	{
		if (LeafButton.IsValid())
		{
			LeafButton->SetStyle(&Style, InButtonStyleOverride);
		}
	}
}

bool UBCMAMRadioComponent::ProcessMenuInputChord(const FInputChord& InChord)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Shortcut == InChord)
		{
			HandleButtonClicked(Items[i].ID);

			return true;
		}
	}

	return false;
}

TSharedRef<SWidget> UBCMAMRadioComponent::RebuildWidget()
{
	SAssignNew(VerticalBox, SVerticalBox);

	LeafButtons.Reset();

	for (int i = 0; i < Items.Num(); i++)
	{
		const FBCMAMRadioItem& Item = Items[i];
		CreateItem(Item);
	}

	return VerticalBox.ToSharedRef();
}

void UBCMAMRadioComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	VerticalBox.Reset();
	LeafButtons.Reset();
}

void UBCMAMRadioComponent::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	for (int32 i = 0; i < LeafButtons.Num(); i++)
	{
		if (Items.IsValidIndex(i))
		{
			SynchronizeItem(LeafButtons[i], Items[i]);
		}
	}
}

FReply UBCMAMRadioComponent::HandleButtonClicked(FName ID)
{
	SetSelectedID(ID);

	OnSelectedIDChanged.Broadcast(ID);

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ID == ID)
		{
			OnSelectedIndexChanged.Broadcast(i);
			break;
		}
	}

	return FReply::Handled();
}

void UBCMAMRadioComponent::HandleButtonHovered(FName ID)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ID == ID)
		{
			if (LeafButtons.IsValidIndex(i) && LeafButtons[i]->GetButton())
			{
				FSlateApplication::Get().SetUserFocus(0, LeafButtons[i]->GetButton(), EFocusCause::SetDirectly);
			}
			break;
		}
	}
}

void UBCMAMRadioComponent::CreateItem(const FBCMAMRadioItem& InItem)
{
	if (VerticalBox)
	{
		TSharedPtr<SBCLeafButton> NewButton = SNew(SBCLeafButton)
			.OnClicked_Lambda([this, InItem] { return HandleButtonClicked(InItem.ID); })
			.OnHovered_Lambda([this, InItem] { HandleButtonHovered(InItem.ID); });

		VerticalBox->AddSlot()
		           .AutoHeight()
		[
			NewButton.ToSharedRef()
		];

		SynchronizeItem(NewButton, InItem);

		LeafButtons.Add(NewButton);
	}
}

void UBCMAMRadioComponent::SynchronizeItem(const TSharedPtr<SBCLeafButton>& Button, const FBCMAMRadioItem& Item)
{
	const FBCModernActionMenuStyle& Style = UBCMAMComponentFunctionLibrary::GetStyle(this);

	if (Button)
	{
		Button->SetStyle(&Style, ButtonStyleOverride);
		Button->SetLabel(Item.Label);
		Button->SetIconBrush(Item.ID == SelectedID ? &Style.RadioBrush : &Style.EmptyRadioBrush);
		Button->SetShortcut(Item.Shortcut);
	}
}

void UBCMAMRadioComponent::SetItems(TArray<FBCMAMRadioItem> InItems)
{
	Items = InItems;

	ClearItems();

	for (int i = 0; i < Items.Num(); i++)
	{
		CreateItem(Items[i]);
	}
}
