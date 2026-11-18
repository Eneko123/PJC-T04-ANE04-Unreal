// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PJC_T04_ANE04_GAME : ModuleRules
{
	public PJC_T04_ANE04_GAME(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PJC_T04_ANE04_GAME",
			"PJC_T04_ANE04_GAME/Variant_Platforming",
			"PJC_T04_ANE04_GAME/Variant_Platforming/Animation",
			"PJC_T04_ANE04_GAME/Variant_Combat",
			"PJC_T04_ANE04_GAME/Variant_Combat/AI",
			"PJC_T04_ANE04_GAME/Variant_Combat/Animation",
			"PJC_T04_ANE04_GAME/Variant_Combat/Gameplay",
			"PJC_T04_ANE04_GAME/Variant_Combat/Interfaces",
			"PJC_T04_ANE04_GAME/Variant_Combat/UI",
			"PJC_T04_ANE04_GAME/Variant_SideScrolling",
			"PJC_T04_ANE04_GAME/Variant_SideScrolling/AI",
			"PJC_T04_ANE04_GAME/Variant_SideScrolling/Gameplay",
			"PJC_T04_ANE04_GAME/Variant_SideScrolling/Interfaces",
			"PJC_T04_ANE04_GAME/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
