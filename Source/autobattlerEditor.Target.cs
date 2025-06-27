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


        string command = "cd \"$(ProjectDir)\" && " +
                         "if exist \"Documentation\\generated\" ( rd /s /q \"Documentation\\generated\" ) && " +
                         "doxygen Doxyfile";

        PostBuildSteps.Add($"echo \"Cleaning and running Doxygen...\" && {command}");
	}
}
