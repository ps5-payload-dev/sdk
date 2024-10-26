@echo off
setlocal

set SCRIPT_PATH=%~dp0
set PS5_PAYLOAD_SDK=%SCRIPT_PATH%..

set LIBS_C="-lc"
set LIBS_CXX=-lunwind -lc++abi -lc++
set LIBS_DEPS=-lSceLibcInternal -lSceNet
set INCDIR=%PS5_PAYLOAD_SDK%\target\include\c++\v1
set PATH=%PATH%;%PS5_PAYLOAD_SDK%\win

:checkargs
    if "%1"=="" goto runcmd
    else if "%1"=="-c" (
        set LIBS_C=""
	set LIBS_CXX=""
        set LIBS_DEPS=""
    ) else if "%1"=="-nostdlibc" (
        set LIBS_C=""
	set LIBS_CXX=""
        set LIBS_DEPS=""
    ) else if "%1"=="-E" (
        set LIBS_C=""
	set LIBS_CXX=""
        set LIBS_DEPS=""
    ) else if "%1:~0,2%"=="-M" (
        set LIBS_C=""
	set LIBS_CXX=""
        set LIBS_DEPS=""
    ) else if "%1"=="-nostdlib++" (
	set LIBS_CXX=""
    )
shift
goto checkargs

:runcmd
clang++ -target x86_64-sie-ps5 -isysroot "%PS5_PAYLOAD_SDK%" -stdlib++-isystem "%INCDIR%" ^
    -fno-stack-protector -fno-plt -femulated-tls -frtti -fexceptions ^
    %LIBS_C% %LIBS_CXX% %* %LIBS_DEPS%
