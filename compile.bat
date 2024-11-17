@echo off
chcp 65001

setlocal enabledelayedexpansion

@REM change projName to project root folder
set "projName=MACER"
set "generator=Visual Studio 17 2022"

@REM Parse command line arguments
set "debugMode=0"
set "runAfter=0"
:parseArgs
if not "%~1"=="" (
    if "%~1"=="-debug" (
        set "debugMode=1"
    ) else if "%~1"=="-run" (
        set "runFlag=1"
    )
    shift
    goto parseArgs
)

@REM find full path of the root folder
@REM and save as projDir
set "found=0"
:findParent
if "!found!"=="0" (
    cd ..
    set "currentPath=%cd%"
    for %%a in ("!currentPath!") do set "currentFolder=%%~nxa"
    echo At: !currentFolder!

    @REM Check if reached the root directory
    if "!currentPath:~-1!"=="\" (
        echo Compile script is not in project folder
        exit /b 2
    )

    @REM recursion
    dir !projName! >nul 2>&1
    if errorlevel 1 (
        goto findParent
    ) else (
        echo Found project folder at: %cd%
        set "projDir=%cd%"
        set "found=1"
    )
)

@REM save some path

set "cmakePlan=Release"
if "!debugMode!"=="1" (
    set "cmakePlan=Debug"
)

set "projEXE=!projDir!\!projName!.exe"
set "projPDB=!projDir!\!projName!.pdb"

set "buildDir=!projDir!\.debug\build"
set "buildEXE=!buildDir!\!cmakePlan!\!projName!.exe"
set "buildPDB=!buildDir!\!cmakePlan!\!projName!.pdb"

set "batchOut=!projDir!\.debug\batchout"
set "shellOut=!batchOut!\cmd_output.txt"
set "cmakeOut=!batchOut!\cmake_output.txt"
set "compileOut=!batchOut!\make_output.txt"

@REM clear batch output files
echo. > !shellOut!
echo. > !cmakeOut!
echo. > !compileOut!

@REM clear all files and folders in buildDir
if "!debugMode!"=="1" (
    echo Clearing caches in build directory...
    del /q !buildDir!\*.* >>!shellOut! 2>&1
    for /d %%d in ("!buildDir!\*") do rmdir /s /q "%%d" >>!shellOut! 2>&1
)

@REM build with generator specified above
echo Build with !generator!
cmake -G "!generator!" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S"!projDir!" -B"!buildDir!" >>!cmakeOut! 2>&1
if "%errorlevel%"=="1" (
    echo Build failed
    exit /b 1
)

@REM compile (use debug type in debug mode)
echo Compiling ...
cmake --build !buildDir! --config !cmakePlan! >>!compileOut! 2>&1
if "%errorlevel%"=="1" (
    echo Compile failed
    exit /b 1
)

@REM delete if file exist
@REM then copy the new one from buildEXE to projEXE
echo Compile succeed, copying files ...
if exist "!projEXE!" del /Q "!projEXE!" >>!shellOut! 2>&1
copy /B/V/Y "!buildEXE!" "!projEXE!" >>!shellOut! 2>&1
if "!debugMode!"=="1" (
    if exist "!projPDB!" del /Q "!projPDB!" >>!shellOut! 2>&1
    copy /B/V/Y "!buildPDB!" "!projPDB!" >>!shellOut! 2>&1
)

@REM run the executable if -run is specified
if "!runFlag!"=="1" (
    echo Running the executable...
    if "!debugMode!"=="1" (
        "!projEXE!" -debug >>!shellOut! 2>&1
    ) else (
        "!projEXE!" >>!shellOut! 2>&1
    )
)

endlocal
