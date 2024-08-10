// Copyright BunnySoft

using UnrealBuildTool;
using System.Collections.Generic;

public class LouiesAdventuresTarget : TargetRules
{
	public LouiesAdventuresTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "LouiesAdventures" } );
	}
}
