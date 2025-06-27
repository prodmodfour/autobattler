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

		PostBuildSteps.Add("echo \"Running Doxygen...\" && doxygen \"$(ProjectDir)Doxyfile\"");
	}
}
