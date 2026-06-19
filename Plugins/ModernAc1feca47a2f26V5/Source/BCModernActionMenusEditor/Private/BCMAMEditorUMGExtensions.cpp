// Copyright Bartschi Creative 2025. All rights reserved.

#include "BCMAMEditorUMGExtensions.h"

#include "BlueprintEditor.h"
#include "BlueprintEditorContext.h"
#include "Blueprint/UserWidget.h"
#include "BlueprintModes/WidgetBlueprintApplicationModes.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"
#include "UMGEditorModule.h"
#include "WidgetBlueprint.h"
#include "WidgetBlueprintEditor.h"
#include "Widgets/BCModernActionMenu.h"

class FUICommandList;

#define LOCTEXT_NAMESPACE "BCMAMEditorUMGExtensions"

namespace BCMAMEditor::Private
{
	// Hardcoded toolbar name since not exposed without instance of UMG editor
	static FName WidgetBlueprintEditorToolbarName = FName("AssetEditor.WidgetBlueprintEditor.ToolBar");
	static FName ExtensionName = FName("BCMAMEditorExtensions");
}

class FBCMAMEditorUMGExtensions_Impl
{
public:

	static void AddEditorUtilityExtension(UToolMenu* InMenu)
	{
		FToolMenuSection& Section = InMenu->AddSection(BCMAMEditor::Private::ExtensionName);
		Section.InsertPosition = FToolMenuInsert("Compile", EToolMenuInsertType::After);
		Section.AddDynamicEntry("BCModernActionMenuActions", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
		{
			UBlueprintEditorToolMenuContext* Context = InSection.FindContext<UBlueprintEditorToolMenuContext>();
			if (Context)
			{
				if (TSharedPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor = StaticCastSharedPtr<FWidgetBlueprintEditor>(Context->BlueprintEditor.Pin()))
				{
					if (WidgetBlueprintEditor->GetPreview() && WidgetBlueprintEditor->GetPreview()->IsEditorUtility())
					{
						TWeakPtr<FWidgetBlueprintEditor> WeakWidgetBlueprintEditor = WidgetBlueprintEditor;

						FName UtilityWidgetName = WidgetBlueprintEditor->GetBlueprintObj()->GetFName();

						InSection.AddEntry(FToolMenuEntry::InitToolBarButton(
							"ModernActionMenu",
							FUIAction(
								FExecuteAction::CreateLambda([WeakWidgetBlueprintEditor]()
									{ 
										if (TSharedPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor = WeakWidgetBlueprintEditor.Pin())
										{
											
										}
									}),
								FCanExecuteAction(),
								FGetActionCheckState(),
								FIsActionButtonVisible::CreateLambda([WeakWidgetBlueprintEditor]()
									{
										if (TSharedPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor = WeakWidgetBlueprintEditor.Pin())
										{
											if (UWidgetBlueprint* WBP = WidgetBlueprintEditor->GetWidgetBlueprintObj())
											{
												if (WBP->GetBlueprintClass()->IsChildOf(UBCModernActionMenu::StaticClass()))
												{
													return true;
												}
											}
										}
										return true; 
									})
							)
							, LOCTEXT("ModernActionMenu", "Modern Action Menu")
							, LOCTEXT("ModernActionMenuTooltip", "Helpers for creating modern action menus")
							// , FSlateIcon(FAppStyle::Get().GetStyleSetName(), "PlayWorld.PlayInViewport") 
						));
					}
				}
			}
		}));
	}

	static void RemoveEditorUtilityExtension(UToolMenu* InMenu)
	{
		InMenu->RemoveSection(BCMAMEditor::Private::ExtensionName);
	}
};

void FBCMAMEditorUMGExtensions::InstallHooks()
{
	// Load module to ensure relevant toolbar exists
	IUMGEditorModule& UMGEditorModule = FModuleManager::Get().LoadModuleChecked<IUMGEditorModule>("UMGEditor");

	auto AddExtensionsUMGEditorToolbar = [](const FName InModeName, FName ParentToolbarName)
	{
		const FName ModeSpecificToolbarName = *(ParentToolbarName.ToString() + TEXT(".") + InModeName.ToString());

		if (!UToolMenus::Get()->IsMenuRegistered(ModeSpecificToolbarName))
		{
			UToolMenus::Get()->RegisterMenu(ModeSpecificToolbarName, ParentToolbarName, EMultiBoxType::ToolBar);
		}

		if (UToolMenu* Toolbar = UToolMenus::Get()->FindMenu(ModeSpecificToolbarName))
		{
			FBCMAMEditorUMGExtensions_Impl::AddEditorUtilityExtension(Toolbar);
		}
	};

	AddExtensionsUMGEditorToolbar(FWidgetBlueprintApplicationModes::DesignerMode, BCMAMEditor::Private::WidgetBlueprintEditorToolbarName);
}

void FBCMAMEditorUMGExtensions::RemoveHooks()
{
	// Load module to ensure relevant toolbar exists
	IUMGEditorModule& UMGEditorModule = FModuleManager::Get().LoadModuleChecked<IUMGEditorModule>("UMGEditor");

	auto RemoveExtensionsUMGEditorToolbar = [](const FName InModeName, FName ParentToolbarName)
	{
		const FName ModeSpecificToolbarName = *(ParentToolbarName.ToString() + TEXT(".") + InModeName.ToString());

		if (!UToolMenus::Get()->IsMenuRegistered(ModeSpecificToolbarName))
		{
			UToolMenus::Get()->RegisterMenu(ModeSpecificToolbarName, ParentToolbarName, EMultiBoxType::ToolBar);
		}

		if (UToolMenu* Toolbar = UToolMenus::Get()->FindMenu(ModeSpecificToolbarName))
		{
			FBCMAMEditorUMGExtensions_Impl::RemoveEditorUtilityExtension(Toolbar);
		}
	};

	if (UToolMenus::Get())
		RemoveExtensionsUMGEditorToolbar(FWidgetBlueprintApplicationModes::DesignerMode, BCMAMEditor::Private::WidgetBlueprintEditorToolbarName);
}

#undef LOCTEXT_NAMESPACE
