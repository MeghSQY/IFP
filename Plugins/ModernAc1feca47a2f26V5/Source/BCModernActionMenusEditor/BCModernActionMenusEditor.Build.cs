// Copyright Bartschi Creative 2025. All Rights Reserved.

using UnrealBuildTool;

public class BCModernActionMenusEditor : ModuleRules
{
    public BCModernActionMenusEditor(ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = ModuleRules.PCHUsageMode.NoPCHs;
		bUseUnity = false;
		
		// PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "PropertyEditor",
                "BCModernActionMenus",
				"DeveloperSettings"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "UMGEditor",
                "UnrealEd",
                "BlueprintGraph",
                "GraphEditor",
                "UMG",
                "ToolMenus",
                "Kismet",
            }
        );
    }
}