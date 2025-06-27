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
        // 2. Check if the theme files are missing and, if so, initialize the submodule.
        // 3. If the 'generated' folder exists, quietly remove it.
        // 4. Create a new, empty 'generated' folder.
        // 5. Run Doxygen.
        string command = "cd \"$(ProjectDir)\" && " +
                         "if not exist \"Documentation\\theme\\doxygen-awesome.css\" ( git submodule update --init --recursive ) && " +
                         "if exist \"Documentation\\generated\" ( rd /s /q \"Documentation\\generated\" ) && " +
                         "mkdir \"Documentation\\generated\" && " +
                         "doxygen Doxyfile";

        PostBuildSteps.Add($"echo \"Checking dependencies and running Doxygen...\" && {command}");
	}
}
