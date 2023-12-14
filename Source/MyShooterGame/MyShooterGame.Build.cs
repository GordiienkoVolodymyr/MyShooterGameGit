// MyShooterGame

using UnrealBuildTool;

public class MyShooterGame : ModuleRules
{
	public MyShooterGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore",
            "Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"MyShooterGame/Public/Player",
			"MyShooterGame/Public/Components",
			"MyShooterGame/Public/Dev",
			"MyShooterGame/Public/Weapon",
			"MyShooterGame/Public/UI",
            "MyShooterGame/Public/Animations",
            "MyShooterGame/Public/PickUPs",
            "MyShooterGame/Public/Weapon/Components",
            "MyShooterGame/Public/AI",
            "MyShooterGame/Public/AI/Tasks",
            "MyShooterGame/Public/AI/Services",
            "MyShooterGame/Public/AI/EQS",
            "MyShooterGame/Public/AI/Decorators",
            "MyShooterGame/Public/Menu",
            "MyShooterGame/Public/Menu/UI"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
