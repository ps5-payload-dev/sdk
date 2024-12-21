@echo off
setlocal

set SCRIPT_PATH=%~dp0
set PS5_PAYLOAD_SDK=%SCRIPT_PATH%..

set LIBS_CRT="%PS5_PAYLOAD_SDK%\target\lib\crt1.o"
set LIBS_C="-lc"
set LIBS_CXX="-lunwind -lc++abi -lc++"
set LIBS_DEPS="-lSceLibcInternal -lSceNet"
set LIBS_KERN="-lkernel_web"
set "TU="

:checkargs
    if "%1"=="" goto runcmd
    if "%1"=="-nostdlibc" (
        set "LIBS_C="
	set "LIBS_CXX="
        set "LIBS_DEPS="
        set "LIBS_KERN="
    ) else if "%1"=="-nodefaultlibs" (
        set "LIBS_C="
	set "LIBS_CXX="
        set "LIBS_DEPS="
        set "LIBS_KERN="
    ) else if "%1"=="-nostdlib++" (
	set "LIBS_CXX="
    ) else if "%1"=="-lkernel" (
	set "LIBS_KERN="
    ) else if "%1"=="-lkernel_sys" (
	set "LIBS_KERN="
    ) else if "%1"=="-lkernel_web" (
	set "LIBS_KERN="
    ) else if "%1"=="-nostartfiles" (
        set "LIBS_CRT="
    ) else if "%1"=="-c" (
        set "LIBS_CRT="
    ) else if "%1"=="-shared" (
        set "LIBS_CRT="
    ) else if not "%1:~0,1%"=="-" (
        set TU="%1"
    )
shift
goto checkargs

:runcmd

if "%TU%"=="" (
    set "LIBS_CRT="
    set "LIBS_C="
    set "LIBS_CXX="
    set "LIBS_DEPS="
    set "LIBS_KERN="
)

rem ensure clang knows where prospero-lld.exe is at
set PATH=%PATH%;%PS5_PAYLOAD_SDK%\win

clang++ ^
    --start-no-unused-arguments ^
    -target x86_64-sie-ps5 ^
    -isysroot "%PS5_PAYLOAD_SDK%" ^
    -stdlib++-isystem "%PS5_PAYLOAD_SDK%\target\include\c++\v1" ^
    -L "%PS5_PAYLOAD_SDK%\target\lib" ^
    -L "%PS5_PAYLOAD_SDK%\target\user\homebrew\lib" ^
    -fno-stack-protector -fno-plt -femulated-tls ^
    -frtti -fexceptions ^
    %LIBS_C% %LIBS_CXX% ^
    --end-no-unused-arguments ^
    %* ^
    --start-no-unused-arguments ^
    %LIBS_CRT% %LIBS_DEPS% %LIBS_KERN% ^
    --end-no-unused-arguments
