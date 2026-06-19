// Copyright Bartschi Creative 2025. All rights reserved.


#include "Widgets/Components/BCMAMLeafComponent.h"

#include "Blueprint/WidgetTree.h"
#include "Widgets/Components/BCMAMComponentFunctionLibrary.h"

#if WITH_EDITOR
void UBCMAMLeafComponent::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	UBCMAMComponentFunctionLibrary::ValidateComponent(this, CompileLog);	
}

const FText UBCMAMLeafComponent::GetPaletteCategory()
{
	return INVTEXT("Modern Action Menu Components");
}
#endif

bool UBCMAMLeafComponent::ProcessMenuInputChord(const FInputChord& InChord)
{
	return false;
}
