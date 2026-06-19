// Copyright Bartschi Creative 2025. All rights reserved.

#include "Util/BCModernActionMenusSlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "UObject/ConstructorHelpers.h"
#include "Styling/CoreStyle.h"
#include "Materials/MaterialInterface.h"
#include "Styling/StyleColors.h"
#include "Util/BCModernActionMenusTypes.h"

TSharedPtr<FSlateStyleSet> FBCModernActionMenusSlateStyle::StyleInstance = nullptr;

void FBCModernActionMenusSlateStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBCModernActionMenusSlateStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		StyleInstance.Reset();
	}
}

FName FBCModernActionMenusSlateStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BCModernActionMenusStyle"));
	return StyleSetName;
}

const ISlateStyle& FBCModernActionMenusSlateStyle::Get()
{
	if (!StyleInstance.IsValid())
	{
		Initialize();
	}
	
	return *StyleInstance;
}

TSharedRef<FSlateStyleSet> FBCModernActionMenusSlateStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("BCModernActionMenus"))->GetBaseDir() / TEXT("Resources"));

	Style->Set("ClassIcon.BCMAMSectionComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_FolderOpen.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMActionComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_Crosshair.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMSeparatorComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_Minus.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMRootComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_List.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMSubMenuComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_ListIndent.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMRadioComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_Radio.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMCheckboxComponent", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_Check.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMContextMenuAnchor", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_AlignCenterHorizontalSimple.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMDropdownMenuAnchor", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_AlignTopSimple.png")), FVector2D(16.0f, 16.0f)));
	Style->Set("ClassIcon.BCMAMFileMenuAnchor", new FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_Icon_AlignTop.png")), FVector2D(16.0f, 16.0f)));
	
	FLinearColor BackgroundDark = FLinearColor(0.052083f, 0.052083f, 0.052083f, 1.f);

	FLinearColor BackgroundColorHover = FLinearColor(0.093750f, 0.093750f, 0.093750f, 1.f);
	
	Style->Set("ActionMenu.Dark", FBCModernActionMenuStyle()
		.SetBackgroundBrush(FSlateRoundedBoxBrush(BackgroundDark, 6.f, BackgroundDark, 0.f))
		.SetShadowBrush(FSlateNoResource())
		.SetItemButtonStyle(FButtonStyle()
		                    .SetNormal(FSlateRoundedBoxBrush(FLinearColor::Transparent, 6.0f, FStyleColors::Transparent,
		                                                     0.f))
		                    .SetHovered(FSlateRoundedBoxBrush(BackgroundColorHover, 5.0f,
		                                                      BackgroundColorHover, 0.f))
		                    .SetPressed(FSlateRoundedBoxBrush(BackgroundColorHover, 5.0f,
		                                                      BackgroundColorHover, 0.f))
		                    .SetNormalPadding(FMargin(0.f, 6.f))
		                    .SetPressedPadding(FMargin(0.f, 7.f, 0.f, 5.f)))
		.SetHighlightedItemButtonStyle(FButtonStyle()
		                               .SetNormal(FSlateRoundedBoxBrush(BackgroundColorHover, 5.0f,
		                                                                BackgroundColorHover, 0.f))
		                               .SetHovered(FSlateRoundedBoxBrush(BackgroundColorHover, 5.0f,
		                                                                 BackgroundColorHover, 0.f))
		                               .SetPressed(FSlateRoundedBoxBrush(BackgroundColorHover, 5.0f,
		                                                                 BackgroundColorHover, 0.f))
		                               .SetNormalPadding(FMargin(0.f, 6.f))
		                               .SetPressedPadding(FMargin(0.f, 7.f, 0.f, 5.f)))
		.SetBaseTextStyle(FTextBlockStyle().SetFont(DEFAULT_FONT("Regular", 14.f * 3.f / 4.f)).SetColorAndOpacity(FLinearColor::White))
		.SetSectionTextStyle(FTextBlockStyle().SetFont(DEFAULT_FONT("Regular", 14.f * 3.f / 4.f)).SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,0.5f)))
		.SetShortcutTextStyle(FTextBlockStyle().SetFont(DEFAULT_FONT("Regular", 14.f * 3.f / 4.f)).SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,0.4f)))
		.SetArrowBrush(FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_IC_CaretRight.png")), FVector2D(12.0f, 12.0f)))
		.SetCheckmarkBrush(FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_IC_Check.png")), FVector2D(16.0f, 16.0f)))
		.SetEmptyCheckmarkBrush(FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_IC_Uncheck.png")), FVector2D(16.0f, 16.0f), FLinearColor(1.f, 1.f, 1.f, 0.5f)))
		.SetRadioBrush(FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_IC_RadioButton.png")), FVector2D(16.0f, 16.0f)))
		.SetEmptyRadioBrush(FSlateImageBrush(Style->RootToContentDir(TEXT("Icons/BC_IC_Circle.png")), FVector2D(16.0f, 16.0f), FLinearColor(1.f, 1.f, 1.f, 0.5f)))
	);
	
	return Style;
}
