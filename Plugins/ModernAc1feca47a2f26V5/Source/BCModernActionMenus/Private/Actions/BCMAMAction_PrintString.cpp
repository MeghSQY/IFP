// Copyright Bartschi Creative 2025. All rights reserved.


#include "Actions/BCMAMAction_PrintString.h"

#include "Engine/Engine.h"

void UBCMAMAction_PrintString::Execute(UBCModernActionMenu* ActionMenu)
{
	Super::Execute(ActionMenu);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ToPrint);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *ToPrint);
}
