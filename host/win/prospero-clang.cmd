@echo off
setlocal

set SCRIPT_PATH=%~dp0
set PS5_PAYLOAD_SDK=%SCRIPT_PATH%..

set LIBS_CRT=-lcrt
set LIBS_C=-lc
set LIBS_DEPS=-lSceLibcInternal -lSceNet
set LIBS_KERN=-lkernel_web

:checkargs
    if "%1"=="" goto runcmd
    if "%1"=="-nostdlibc" (
        set "LIBS_C="
        set "LIBS_DEPS="
	set "LIBS_KERN="
    ) else if "%1"=="-nodefaultlibs" (
        set "LIBS_C="
        set "LIBS_DEPS="
	set "LIBS_KERN="
    ) else if "%1"=="-lkernel" (
	set "LIBS_KERN="
    ) else if "%1"=="-lkernel_sys" (
	set "LIBS_KERN="
    ) else if "%1"=="-lkernel_web" (
	set "LIBS_KERN="
    ) else if "%1"=="-nostartfiles" (
        set "LIBS_CRT="
    )
shift
goto checkargs

:runcmd

rem ensure clang knows where prospero-lld.exe is at
set PATH=%PATH%;%PS5_PAYLOAD_SDK%\win

clang ^
    --start-no-unused-arguments ^
    -target x86_64-sie-ps5 ^
    -isysroot "%PS5_PAYLOAD_SDK%" ^
    -isystem "%PS5_PAYLOAD_SDK%\target\include" ^
    -L "%PS5_PAYLOAD_SDK%\target\lib" ^
    -L "%PS5_PAYLOAD_SDK%\target\user\homebrew\lib" ^
    -fno-stack-protector -fno-plt -femulated-tls ^
    %LIBS_CRT% %LIBS_C% ^
    --end-no-unused-arguments ^
    %* ^
    --start-no-unused-arguments ^
    %LIBS_DEPS% %LIBS_KERN% ^
     --end-no-unused-arguments
