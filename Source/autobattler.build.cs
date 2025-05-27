using UnrealBuildTool;

public class autobattler : ModuleRules 
{
    public autobattler(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // These are your module's main dependencies
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine", // Essential for AActor and UWorld
            // Add other modules your game needs, like "InputCore", "UMG", "GameplayAbilities", etc.
        });



        // Your conditional block for test-related setup
        if (Target.bBuildDeveloperTools || (Target.Configuration != UnrealTargetConfiguration.Shipping && Target.Configuration != UnrealTargetConfiguration.Test))
        {
            // If CoreUObject or Engine were only needed for tests and not general module use,
            // they could go here. But they are usually public dependencies.
            if (Target.bBuildEditor == true)
            {
                PrivateDependencyModuleNames.Add("UnrealEd");
            }

        
            PrivateIncludePaths.Add("Tests");
        }
    }
}