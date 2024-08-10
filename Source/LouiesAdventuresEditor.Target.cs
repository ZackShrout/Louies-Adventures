// Copyright BunnySoft

using UnrealBuildTool;
using System.Collections.Generic;

public class LouiesAdventuresEditorTarget : TargetRules
{
	public LouiesAdventuresEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "LouiesAdventures" } );
	}
}
