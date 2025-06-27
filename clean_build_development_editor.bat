@echo off
REM =================================================================================
REM  Unreal Engine Project Clean and Rebuild Script
REM
REM  Instructions:
REM  1. Place this file in the root directory of your project.
REM  2. !!! IMPORTANT !!! Change the UE_ENGINE_PATH variable below to point to
REM     your specific Unreal Engine installation folder.
REM  3. Double-click to run.
REM =================================================================================

echo.
echo #################################
echo #  AUTOBATTLER BUILD SCRIPT   #
echo #################################
echo.

REM --- CONFIGURATION ---
REM --- !!! EDIT THIS PATH TO MATCH YOUR ENGINE INSTALLATION !!! ---
set UE_ENGINE_PATH=C:\Program Files\Epic Games\UE_5.5

REM --- Get Project Name and Path from the current directory ---
for %%i in (*.uproject) do set UPROJECT_NAME=%%~ni
set PROJECT_PATH=%~dp0%UPROJECT_NAME%.uproject

REM --- Set paths to Engine tools for clarity ---
set UBT_PATH="%UE_ENGINE_PATH%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
set UAT_PATH="%UE_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat"


REM --- STEP 1: CLEAN PROJECT CACHE FILES ---
echo [1/3] Cleaning project...
echo      - Deleting Binaries folder...
if exist "Binaries" ( rmdir /s /q "Binaries" )
echo      - Deleting Intermediate folder...
if exist "Intermediate" ( rmdir /s /q "Intermediate" )
echo      - Deleting .vs folder...
if exist ".vs" ( rmdir /s /q ".vs" )
echo      - Deleting Solution file...
if exist "%UPROJECT_NAME%.sln" ( del "%UPROJECT_NAME%.sln" )
echo      - Clean-up complete.
echo.


REM --- STEP 2: GENERATE VISUAL STUDIO PROJECT FILES ---
echo [2/3] Generating Visual Studio project files...
call %UBT_PATH% -projectfiles -project="%PROJECT_PATH%" -game -engine -progress
if %errorlevel% neq 0 (
    echo ERROR: Failed to generate project files.
    goto end
)
echo      - Project files generated successfully.
echo.


REM --- STEP 3: BUILD THE PROJECT FOR DEVELOPMENT EDITOR ---
echo [3/3] Building project for Development Editor (Win64)...
call %UBT_PATH% %UPROJECT_NAME%Editor Win64 Development -project="%PROJECT_PATH%" -progress
if %errorlevel% neq 0 (
    echo ERROR: Build failed. Check the output above for details.
    goto end
)
echo      - Build successful!
echo.


:end
echo #################################
echo #  SCRIPT FINISHED              #
echo #################################
echo.
pause
