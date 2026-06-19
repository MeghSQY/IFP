// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMPanelComponent.h"

#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBoxSlot.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"
#include "Widgets/Components/Slots/BCMAMPanelComponentSlot.h"

#if WITH_EDITOR
void UBCMAMPanelComponent::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	UBCMAMComponentFunctionLibrary::ValidateComponent(this, CompileLog);	
}

const FText UBCMAMPanelComponent::GetPaletteCategory()
{
	return INVTEXT("Modern Action Menu Components");
}
#endif

UWidget* UBCMAMPanelComponent::AddChildComponent(UWidget* Content)
{
	AddChild(Content);

	return Content;
}

UClass* UBCMAMPanelComponent::GetSlotClass() const
{
	return UBCMAMPanelComponentSlot::StaticClass();
}

void UBCMAMPanelComponent::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);
	
	// Add the child to the live canvas if it already exists
	if ( MyVerticalBox.IsValid() )
	{
		CastChecked<UBCMAMPanelComponentSlot>(InSlot)->BuildSlot(MyVerticalBox.ToSharedRef());
	}
}

void UBCMAMPanelComponent::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);
	
	// Remove the widget from the live slot if it exists.
	if ( MyVerticalBox.IsValid() && InSlot->Content)
	{
		TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
		if ( Widget.IsValid() )
		{
			MyVerticalBox->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

void UBCMAMPanelComponent::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyVerticalBox.Reset();
}

TSharedRef<SWidget> UBCMAMPanelComponent::RebuildWidget()
{
	MyVerticalBox = SNew(SVerticalBox);

	for ( UPanelSlot* PanelSlot : Slots )
	{
		if ( UBCMAMPanelComponentSlot* TypedSlot = Cast<UBCMAMPanelComponentSlot>(PanelSlot) )
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyVerticalBox.ToSharedRef());
		}
	}

	return MyVerticalBox.ToSharedRef();
}
