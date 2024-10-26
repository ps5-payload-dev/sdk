@echo off
setlocal

set SCRIPT_PATH=%~dp0
set PS5_PAYLOAD_SDK=%SCRIPT_PATH%..

set TOOLCHAIN=%PS5_PAYLOAD_SDK%\toolchain\prospero.cmake
set PATH=%PATH%;%PS5_PAYLOAD_SDK%\win

set BUILD_SYS_ARGS="-G Ninja"
:checkargs
    if "%1"=="" goto runcmd
    if "%1"=="-G" set BUILD_SYS_ARGS=""
shift
goto checkargs

:runcmd
cmake -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN%" %* %BUILD_SYS_ARGS%
