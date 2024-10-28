@echo off
setlocal

set SCRIPT_PATH=%~dp0
set PS5_PAYLOAD_SDK=%SCRIPT_PATH%..

set LIBS_C="-lc"
set LIBS_CXX="-lunwind -lc++abi -lc++"
set LIBS_DEPS="-lSceLibcInternal -lSceNet"
set "LIB_KERN="

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
    ) else if not "%1:~0,1%"=="-" (
        set TU="%1"
    )
shift
goto checkargs

:runcmd

if "%TU%"=="" (
    set "LIBS_C="
    set "LIBS_CXX="
    set "LIBS_DEPS="
    set "LIBS_KERN="
)

set INCDIR=%PS5_PAYLOAD_SDK%\target\include\c++\v1
set PATH=%PATH%;%PS5_PAYLOAD_SDK%\win

clang++ ^
    --start-no-unused-arguments ^
    -target x86_64-sie-ps5 ^
    -isysroot "%PS5_PAYLOAD_SDK%" ^
    -stdlib++-isystem "%INCDIR%" ^
    -fno-stack-protector -fno-plt -femulated-tls ^
    -frtti -fexceptions ^
    %LIBS_C% %LIBS_CXX% ^
    --end-no-unused-arguments ^
    %* ^
    --start-no-unused-arguments ^
    %LIBS_DEPS% %LIBS_KERN% ^
    --end-no-unused-arguments
