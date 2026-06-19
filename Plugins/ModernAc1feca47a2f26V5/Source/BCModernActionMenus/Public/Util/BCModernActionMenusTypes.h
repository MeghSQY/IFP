// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"

#include "BCModernActionMenusTypes.generated.h"

class UBCModernActionMenuBase;
class UUserWidget;
class UBCModernActionMenuItemBase;
class UBCMAMActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCMAMContextDelegate, TArray<UObject*>, Context);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCMAMActionComponentDelegate, UBCMAMActionComponent*, ActionComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCMAMMenuDelegate, UBCModernActionMenu*, ActionMenu);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCMAMBoolDelegate, bool, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCMAMNameDelegate, FName, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCMAMIntDelegate, int32, Value);

UENUM(BlueprintType)
enum class EBCMAMItemState : uint8
{
	Active,
	Disabled,
	Hidden
};
	
/**
 * Slate widget style for @code UBCModernActionMenuBase @endcode widgets
 */
USTRUCT(BlueprintType, DisplayName="BC Modern Action Menu Style")
struct BCMODERNACTIONMENUS_API FBCModernActionMenuStyle : public FSlateWidgetStyle
{
	GENERATED_BODY()

	FBCModernActionMenuStyle();
	virtual ~FBCModernActionMenuStyle() override {}
	
	virtual void GetResources( TArray< const FSlateBrush* >& OutBrushes ) const override;

	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };

	static const FBCModernActionMenuStyle& GetDefault();

	/** Background brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FSlateBrush BackgroundBrush;
	FBCModernActionMenuStyle& SetBackgroundBrush(const FSlateBrush& InBackgroundBrush){ BackgroundBrush = InBackgroundBrush; return *this; }

	/** Menu Width */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	float MenuWidth;
	FBCModernActionMenuStyle& SetMenuWidth(const float& InMenuWidth){ MenuWidth = InMenuWidth; return *this; }
	
	/** Menu padding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FMargin MenuPadding;
	FBCModernActionMenuStyle& SetMenuPadding(const FMargin& InMenuPadding){ MenuPadding = InMenuPadding; return *this; }
	
	/** Shadow brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FSlateBrush ShadowBrush;
	FBCModernActionMenuStyle& SetShadowBrush(const FSlateBrush& InShadowBrush){ ShadowBrush = InShadowBrush; return *this; }

	/** Shadow Offset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FMargin ShadowOffset;
	FBCModernActionMenuStyle& SetShadowOffset(const FMargin& InShadowOffset){ ShadowOffset = InShadowOffset; return *this; }

	/** Item Padding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FMargin ItemPadding;
	FBCModernActionMenuStyle& SetItemPadding(const FMargin& InItemPadding){ ItemPadding = InItemPadding; return *this; }

	/** Column Padding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	float ColumnPadding;
	FBCModernActionMenuStyle& SetColumnPadding(const float& InColumnPadding){ ColumnPadding = InColumnPadding; return *this; }

	/** Maintain Left Column Width */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	bool bMaintainLeftColumnWidth;
	FBCModernActionMenuStyle& SetMaintainLeftColumnWidth(const bool& InMaintainLeftColumnWidth){ bMaintainLeftColumnWidth = InMaintainLeftColumnWidth; return *this; }
	
	/** Item button style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FButtonStyle ItemButtonStyle;
	FBCModernActionMenuStyle& SetItemButtonStyle(const FButtonStyle& InButtonStyle){ ItemButtonStyle = InButtonStyle; return *this; }

	/** Highlighted Item button style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FButtonStyle HighlightedItemButtonStyle;
	FBCModernActionMenuStyle& SetHighlightedItemButtonStyle(const FButtonStyle& InButtonStyle){ HighlightedItemButtonStyle = InButtonStyle; return *this; }

	/** Icon size */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FVector2D IconSize;
	FBCModernActionMenuStyle& SetIconSize(const FVector2D& InIconSize){ IconSize = InIconSize; return *this; }
	
	/** Base Text style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Text")
	FTextBlockStyle BaseTextStyle;
	FBCModernActionMenuStyle& SetBaseTextStyle(const FTextBlockStyle& InTextStyle){ BaseTextStyle = InTextStyle; return *this; }

	/** Section Text style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Text")
	FTextBlockStyle SectionTextStyle;
	FBCModernActionMenuStyle& SetSectionTextStyle(const FTextBlockStyle& InTextStyle){ SectionTextStyle = InTextStyle; return *this; }

	/** Shortcut Text style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Text")
	FTextBlockStyle ShortcutTextStyle;
	FBCModernActionMenuStyle& SetShortcutTextStyle(const FTextBlockStyle& InTextStyle){ ShortcutTextStyle = InTextStyle; return *this; }

	/** Arrow Brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	FSlateBrush ArrowBrush;
	FBCModernActionMenuStyle& SetArrowBrush(const FSlateBrush& InArrowBrush){ ArrowBrush = InArrowBrush; return *this; }

	/** Checkmark Brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Checkmark")
	FSlateBrush CheckmarkBrush;
	FBCModernActionMenuStyle& SetCheckmarkBrush(const FSlateBrush& InCheckmarkBrush){ CheckmarkBrush = InCheckmarkBrush; return *this; }

	/** Empty Checkmark Brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Checkmark")
	FSlateBrush EmptyCheckmarkBrush;
	FBCModernActionMenuStyle& SetEmptyCheckmarkBrush(const FSlateBrush& InEmptyCheckmarkBrush){ EmptyCheckmarkBrush = InEmptyCheckmarkBrush; return *this; }

	/** Radio Brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Radio")
	FSlateBrush RadioBrush;
	FBCModernActionMenuStyle& SetRadioBrush(const FSlateBrush& InRadioBrush){ RadioBrush = InRadioBrush; return *this; }

	/** Empty Radio Brush */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Radio")
	FSlateBrush EmptyRadioBrush;
	FBCModernActionMenuStyle& SetEmptyRadioBrush(const FSlateBrush& InEmptyRadioBrush){ EmptyRadioBrush = InEmptyRadioBrush; return *this; }
	
	/** Separator Thickness */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Separator")
	float SeparatorThickness;
	FBCModernActionMenuStyle& SetSeparatorThickness(const float& InSeparatorThickness){ SeparatorThickness = InSeparatorThickness; return *this; }
	
	/** Separator Color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Separator")
	FLinearColor SeparatorColor;
	FBCModernActionMenuStyle& SetSeparatorColor(const FLinearColor& InSeparatorColor){ SeparatorColor = InSeparatorColor; return *this; }

	/** Separator Padding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance|Separator")
	FMargin SeparatorPadding;
	FBCModernActionMenuStyle& SetSeparatorPadding(const FMargin& InSeparatorPadding){ SeparatorPadding = InSeparatorPadding; return *this; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Appearance)
	float TransitionDuration;
	FBCModernActionMenuStyle& SetTransitionDuration(const float& InTransitionDuration){ TransitionDuration = InTransitionDuration; return *this; }
};

/**
 * An asset that defines the style of an action menu
 */
UCLASS(Abstract, Blueprintable, DisplayName="BC Modern Action Menu Style Asset")
class BCMODERNACTIONMENUS_API UBCModernActionMenuStyleAsset : public UObject
{
	GENERATED_BODY()

public:
	UBCModernActionMenuStyleAsset() {}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FBCModernActionMenuStyle Style;
};

/**
 * An asset that defines the style of a menu item button
 */
UCLASS(Abstract, Blueprintable, DisplayName="BC Modern Action Menu Item Button Style Asset")
class BCMODERNACTIONMENUS_API UBCModernActionMenuItemButtonStyleAsset : public UObject
{
	GENERATED_BODY()

public:
	UBCModernActionMenuItemButtonStyleAsset() {}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FButtonStyle Style;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FButtonStyle HighlightedStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FTextBlockStyle TextStyle;
};

/**
 * An asset that defines the style of a separator
 */
UCLASS(Abstract, Blueprintable, DisplayName="BC Modern Action Menu Separator Style Asset")
class BCMODERNACTIONMENUS_API UBCModernActionMenuSeparatorStyleAsset : public UObject
{
	GENERATED_BODY()

public:
	UBCModernActionMenuSeparatorStyleAsset()
	{
		Thickness = 1.f;
		Color = FLinearColor::White;
		Padding = FMargin(0.f);
	}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	float Thickness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FLinearColor Color;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FMargin Padding;
};

/**
 * An asset that defines the style of a file menu
 */
UCLASS(Abstract, Blueprintable, DisplayName="BC Modern File Menu Style Asset")
class BCMODERNACTIONMENUS_API UBCModernFileMenuStyleAsset : public UObject
{
	GENERATED_BODY()

public:
	UBCModernFileMenuStyleAsset() {}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FButtonStyle ButtonStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FButtonStyle ActiveButtonStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FTextBlockStyle LabelStyle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	FMargin SlotPadding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Appearance)
	float MenuOffset;
};

/**
 * Used by editor utilities to reference a @code UBCModernActionMenuBase @endcode property
 */
USTRUCT(BlueprintType)
struct FBCMAMActionMenuReference
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Modern Action Menu")
	FName Name = NAME_None;
};
