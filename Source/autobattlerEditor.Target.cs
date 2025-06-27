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
         // STEP 1: Clean the previous documentation output to ensure a fresh start.
        string CleanupCommand = "if exist \"$(ProjectDir)\\Documentation\\generated\" ( rd /s /q \"$(ProjectDir)\\Documentation\\generated\" )";
        PostBuildSteps.Add($"echo \"[1/4] Cleaning old documentation...\" && {CleanupCommand}");


        // STEP 2: Export Data Tables to CSV
        // We build the path to the commandlet runner and ensure all paths are correctly quoted.
        string UnrealEditorCmd = Path.Combine(EnginePath, "Engine", "Binaries", "Win64", "UnrealEditor-Cmd.exe");
        string UProjectPath = Path.Combine("$(ProjectDir)", "autobattler.uproject");

        string ExportCsvCommand = $"\"{UnrealEditorCmd}\" \"{UProjectPath}\" -run=ExportDataTablesToCSV";
        PostBuildSteps.Add($"echo \"Exporting data tables to CSV...\" && {ExportCsvCommand}");

        // STEP 3: Convert CSVs to Markdown
        string ConvertToMarkdownCommand = "python \"$(ProjectDir)\\csv_to_markdown.py\"";
        PostBuildSteps.Add($"echo \"Converting CSVs to Markdown...\" && {ConvertToMarkdownCommand}");


        // STEP 4: Run Doxygen by calling our dedicated batch script
		string DoxygenCommand = "\"$(ProjectDir)\\run_doxygen.bat\"";
		PostBuildSteps.Add($"echo \"Running Doxygen build script...\" && {DoxygenCommand}");

  
	}
}
