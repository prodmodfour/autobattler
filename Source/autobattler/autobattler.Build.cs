// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class autobattler : ModuleRules
{
	public autobattler(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });


	}
}
