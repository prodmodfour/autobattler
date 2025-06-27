// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class autobattlerEditorTarget : TargetRules
{
	public autobattlerEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("autobattler");

        // This command chain will:
        // 1. Change to the project's root directory.
        // 2. If the 'generated' folder exists, quietly remove it and all its contents.
        // 3. Create a new, empty 'generated' folder.
        // 4. Run Doxygen.
        string command = "cd \"$(ProjectDir)\" && " +
                         "if exist \"Documentation\\generated\" ( rd /s /q \"Documentation\\generated\" ) && " +
                         "mkdir \"Documentation\\generated\" && " +
                         "doxygen Doxyfile";

        PostBuildSteps.Add($"echo \"Cleaning and running Doxygen...\" && {command}");
	}
}
