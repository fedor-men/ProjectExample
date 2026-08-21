// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FinalProjectUE09 : ModuleRules
{
	public FinalProjectUE09(ReadOnlyTargetRules Target) : base(Target)
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

		PrivateDependencyModuleNames.AddRange(new string[] {"GameplayAbilities", "GameplayTags", "GameplayTasks"});

		PublicIncludePaths.AddRange(new string[] {
			"FinalProjectUE09",
			
		});

	}
}
