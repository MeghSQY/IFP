// Copyright (C) Varian Daemon 2025. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class IFP_ExampleProjectTarget : TargetRules
{
	public IFP_ExampleProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "IFP_ExampleProject" } );
	}
}
