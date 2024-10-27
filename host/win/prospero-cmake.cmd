@echo off
setlocal

set PS5_PAYLOAD_SDK=%~dp0..

set CMAKE_GENERATOR=Ninja
set CMAKE_TOOLCHAIN_FILE=%PS5_PAYLOAD_SDK%\toolchain\prospero.cmake
set CMAKE_MAKE_PROGRAM=%PS5_PAYLOAD_SDK%\win\ninja.exe

cmake %*
