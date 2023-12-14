// MyShooterGame

using UnrealBuildTool;
using System.Collections.Generic;

public class MyShooterGameTarget : TargetRules
{
	public MyShooterGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MyShooterGame" } );
	}
}
