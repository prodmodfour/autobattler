using UnrealBuildTool;

public class autobattlerTests : ModuleRules
{
    public autobattlerTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PrecompileForTargets = PrecompileTargetsType.Editor; 

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine",
                "autobattler"
            });
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd"
                });
        }
    }
}
