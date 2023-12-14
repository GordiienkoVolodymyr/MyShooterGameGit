// MyShooterGame

using UnrealBuildTool;
using System.Collections.Generic;

public class MyShooterGameEditorTarget : TargetRules
{
	public MyShooterGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "MyShooterGame" } );
	}
}
