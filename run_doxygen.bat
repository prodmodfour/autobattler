@echo off
cd /d "%~dp0"

echo.
echo #################################
echo #      RUNNING DOXYGEN          #
echo #################################
echo.

echo Checking for Doxygen theme...
if not exist "Documentation\theme\doxygen-awesome.css" (
    echo Theme not found, updating git submodules...
    git submodule update --init --recursive
)



echo Creating documentation directory...
mkdir "Documentation\generated"

echo Running Doxygen...
doxygen Doxyfile

echo.
echo #################################
echo #      DOXYGEN FINISHED         #
echo #################################
echo.