@echo off
echo #################################
echo #  RUNNING AUTOBATTLER TESTS    #
echo #################################
echo.

REM --- CONFIGURATION ---
set "UE_ENGINE_PATH=C:\Program Files\Epic Games\UE_5.5"

REM grab the first *.uproject in this folder
for %%i in ("%~dp0*.uproject") do (
    set "UPROJECT_NAME=%%~ni"
    goto :found_project
)
echo No .uproject file found. & goto :eof
:found_project

set "PROJECT_PATH=%~dp0%UPROJECT_NAME%.uproject"

REM --- Run the tests ---
"%UE_ENGINE_PATH%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" ^
  "%PROJECT_PATH%" ^
  -ExecCmds="Automation RunTests %UPROJECT_NAME%; Quit" ^
  -log -unattended 

echo.
echo #################################
echo #  TESTS FINISHED               #
echo #################################
pause