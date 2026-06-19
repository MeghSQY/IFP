// Copyright Bartschi Creative 2025. All rights reserved.

#include "BCModernActionMenusModule.h"

#include "Util/BCModernActionMenusSlateStyle.h"

#define LOCTEXT_NAMESPACE "FBCModernActionMenusModule"

void FBCModernActionMenusModule::StartupModule()
{
	FBCModernActionMenusSlateStyle::Initialize();	
}

void FBCModernActionMenusModule::ShutdownModule()
{
	FBCModernActionMenusSlateStyle::Shutdown();	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBCModernActionMenusModule, BCModernActionMenus)