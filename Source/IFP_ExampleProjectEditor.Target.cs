// Copyright (C) Varian Daemon 2025. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class IFP_ExampleProjectEditorTarget : TargetRules
{
	public IFP_ExampleProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "IFP_ExampleProject" } );
	}
}
