// Copyright Bartschi Creative 2025. All rights reserved.

#include "BCModernActionMenusEditor.h"

#include "BCMAMEditorUMGExtensions.h"
#include "EdGraphUtilities.h"
#include "UMGEditorModule.h"
#include "WidgetBlueprint.h"
#include "Blueprint/WidgetTree.h"
#include "Customizations/BCMAMPanelComponentSlotExtension.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Settings/BCModernActionMenusEditorSettings.h"
#include "Util/BCModernActionMenusTypes.h"
#include "Widgets/BCModernActionMenu.h"
#include "Widgets/Components/BCMAMRootComponent.h"

#define LOCTEXT_NAMESPACE "FBCModernActionMenusEditorModule"

class FBCMAMPanelComponentSlotDesignerFactory : public IDesignerExtensionFactory
{
public:

	virtual TSharedRef<FDesignerExtension> CreateDesignerExtension() const override
	{
		return MakeShareable(new FBCMAMPanelComponentSlotExtension());
	}
};

void FBCModernActionMenusEditorModule::StartupModule()
{
	IUMGEditorModule& UMGEditorInterface = FModuleManager::GetModuleChecked<IUMGEditorModule>("UMGEditor");
	
	UMGEditorInterface.GetDesignerExtensibilityManager()->AddDesignerExtensionFactory(MakeShared<FBCMAMPanelComponentSlotDesignerFactory>());

	FKismetEditorUtilities::RegisterOnBlueprintCreatedCallback(this, UBCModernActionMenu::StaticClass(), FKismetEditorUtilities::FOnBlueprintCreated::CreateRaw(this, &FBCModernActionMenusEditorModule::OnNewBlueprintCreated));

	// FBCMAMEditorUMGExtensions::InstallHooks();
}

void FBCModernActionMenusEditorModule::ShutdownModule()
{
	// FBCMAMEditorUMGExtensions::RemoveHooks();
}

void FBCModernActionMenusEditorModule::OnNewBlueprintCreated(UBlueprint* InBlueprint)
{
	if (UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(InBlueprint))
	{
		if (WidgetBlueprint->WidgetTree->RootWidget == nullptr )
		{
			if (const UBCModernActionMenusEditorSettings* Settings = GetDefault<UBCModernActionMenusEditorSettings>())
			{
				if (TSubclassOf<UBCModernActionMenuStyleAsset> Style = Settings->DefaultMenuStyle.LoadSynchronous())
				{
					if (UClass* WidgetClass = WidgetBlueprint->GeneratedClass)
					{
						if (UObject* CDO = WidgetClass->GetDefaultObject())
						{
							if (UBCModernActionMenu* ActionMenu = Cast<UBCModernActionMenu>(CDO))
							{
								ActionMenu->SetStyle(Style);
							}
						}
					}
				}
			}
			
			UWidget* Root = WidgetBlueprint->WidgetTree->ConstructWidget<UWidget>(UBCMAMRootComponent::StaticClass(), "RootComponent");
			WidgetBlueprint->WidgetTree->RootWidget = Root;

			FKismetEditorUtilities::CompileBlueprint(WidgetBlueprint);
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBCModernActionMenusEditorModule, BCModernActionMenusEditor)
