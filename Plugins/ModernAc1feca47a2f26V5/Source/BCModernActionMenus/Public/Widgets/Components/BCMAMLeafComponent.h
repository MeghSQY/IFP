// Copyright Bartschi Creative 2025. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "BCMAMLeafComponent.generated.h"

/**
 * An action menu component that has no children. Must be used within a UBCModernActionMenu.
 *
 * Can process menu input (typically matching with Shortcut properties).
 */
UCLASS(Abstract, DisplayName="BCMAM Leaf Component")
class BCMODERNACTIONMENUS_API UBCMAMLeafComponent : public UWidget
{
	GENERATED_BODY()

public:

#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
	virtual const FText GetPaletteCategory() override;
#endif

	/** Override this function to handle menu input (typically matching with Shortcut properties). Returns true if the input was handled. */
	virtual bool ProcessMenuInputChord(const FInputChord& InChord);
};
