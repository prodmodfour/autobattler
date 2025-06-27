// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class autobattlerEditorTarget : TargetRules
{
	public autobattlerEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("autobattler");

        // Set the path to your Unreal Engine installation directory.
        string EnginePath = "C:\\Program Files\\Epic Games\\UE_5.5";

        // --- Post-Build Steps ---

        // 1. Export Data Tables to CSV
        // We build the path to the commandlet runner and ensure all paths are correctly quoted.
        string UnrealEditorCmd = Path.Combine(EnginePath, "Engine", "Binaries", "Win64", "UnrealEditor-Cmd.exe");
        string UProjectPath = Path.Combine("$(ProjectDir)", "autobattler.uproject");

        string ExportCsvCommand = $"\"{UnrealEditorCmd}\" \"{UProjectPath}\" -run=ExportDataTablesToCSV";
        PostBuildSteps.Add($"echo \"Exporting data tables to CSV...\" && {ExportCsvCommand}");

        // 2. Convert CSVs to Markdown
        string ConvertToMarkdownCommand = "python \"$(ProjectDir)\\csv_to_markdown.py\"";
        PostBuildSteps.Add($"echo \"Converting CSVs to Markdown...\" && {ConvertToMarkdownCommand}");

        // 3. Run Doxygen
            // This command chain will:
            // 1. Change to the project's root directory.
            // 2. Check if the theme files are missing and, if so, initialize the submodule.
            // 3. If the 'generated' folder exists, quietly remove it.
            // 4. Create a new, empty 'generated' folder.
            // 5. Run Doxygen.
        string DoxygenCommand = "cd \"$(ProjectDir)\" && " +
                                "if not exist \"Documentation\\theme\\doxygen-awesome.css\" ( git submodule update --init --recursive ) && " +
                                "if exist \"Documentation\\generated\" ( rd /s /q \"Documentation\\generated\" ) && " +
                                "mkdir \"Documentation\\generated\" && " +
                                "doxygen Doxyfile";
        PostBuildSteps.Add($"echo \"Checking dependencies and running Doxygen...\" && {DoxygenCommand}");
	}
}
