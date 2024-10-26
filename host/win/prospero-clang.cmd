@echo off
setlocal

set SCRIPT_PATH=%~dp0
set PS5_PAYLOAD_SDK=%SCRIPT_PATH%..

set LIBS_C=-lc
set LIBS_DEPS=-lSceLibcInternal -lSceNet
set INCDIR=%PS5_PAYLOAD_SDK%\target\include

set PATH=%PATH%;%PS5_PAYLOAD_SDK%/win

clang -target x86_64-sie-ps5 -isysroot "%PS5_PAYLOAD_SDK%" -isystem "%INCDIR%" ^
    -fno-stack-protector -fno-plt -femulated-tls -frtti -fexceptions ^
    %LIBS_C% %* %LIBS_DEPS%

