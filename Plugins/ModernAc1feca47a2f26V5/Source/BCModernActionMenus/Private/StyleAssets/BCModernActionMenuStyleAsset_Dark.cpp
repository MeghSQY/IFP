// Copyright Bartschi Creative 2025. All rights reserved.


#include "StyleAssets/BCModernActionMenuStyleAsset_Dark.h"

#include "Engine/Font.h"
#include "Misc/ConfigCacheIni.h"
#include "UObject/ConstructorHelpers.h"
#include "Util/BCModernActionMenusSlateStyle.h"

UBCModernActionMenuStyleAsset_Dark::UBCModernActionMenuStyleAsset_Dark()
{
#if WITH_EDITORONLY_DATA
		FString DefaultFontName = TEXT("/Engine/EngineFonts/Roboto");
		GConfig->GetString(TEXT("SlateStyle"), TEXT("DefaultFontName"), DefaultFontName, GEngineIni);
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*DefaultFontName);
        
        Style = FBCModernActionMenusSlateStyle::Get().GetWidgetStyle<FBCModernActionMenuStyle>("ActionMenu.Dark");
        Style.BaseTextStyle = FTextBlockStyle(Style.BaseTextStyle)
        	.SetFont(FSlateFontInfo(RobotoFontObj.Object, Style.BaseTextStyle.Font.Size, FName("Regular")));
        Style.SectionTextStyle = FTextBlockStyle(Style.SectionTextStyle)
        	.SetFont(FSlateFontInfo(RobotoFontObj.Object, Style.SectionTextStyle.Font.Size, FName("Regular")));
        Style.ShortcutTextStyle = FTextBlockStyle(Style.ShortcutTextStyle)
        	.SetFont(FSlateFontInfo(RobotoFontObj.Object, Style.ShortcutTextStyle.Font.Size, FName("Regular")));
#endif
}
