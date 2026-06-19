// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Util/BCModernActionMenusTypes.h"
#include "BCMAMComponentFunctionLibrary.generated.h"

class UWidget;
class UWidgetTree;
class UBCModernActionMenu;
class IWidgetCompilerLog;

/**
 * Helper functions for action menu components.
 */
UCLASS()
class BCMODERNACTIONMENUS_API UBCMAMComponentFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

#if WITH_EDITOR
	static void ValidateComponent(const UWidget* Widget, IWidgetCompilerLog& CompileLog);
#endif
	
	static UBCModernActionMenu* GetParentActionMenu(const UWidget* Widget);

	static UWidgetTree* GetWidgetTree(const UWidget* Widget);
	
	static const FBCModernActionMenuStyle& GetStyle(const UWidget* Widget);
};
