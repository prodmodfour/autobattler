if (Target.bBuildDeveloperTools || (Target.Configuration != UnrealTargetConfiguration.Shipping && Target.Configuration != UnrealTargetConfiguration.Test))
{
    PrivateDependencyModuleNames.Add("CoreUObject"); // For UObject testing
    if (Target.bBuildEditor == true)
    {
        PrivateDependencyModuleNames.Add("UnrealEd"); // For editor-specific tests
    }
}

PrivateIncludePaths.AddRange(
    new string[] {
        "autobattler/Tests" // Base path for tests
    }
);