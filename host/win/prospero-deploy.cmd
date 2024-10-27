@echo off
setlocal

set PS5_PORT=9021
set PS5_HOST=ps5
set "PS5_PAYLOAD="

:argparse
if "%1"=="" goto runcmd
if "%1" == "-h" (
  set PS5_HOST=%2
  shift
  shift
  goto :argparse
)
if "%1" == "-p" (
  set PS5_PORT=%2
  shift
  shift
  goto :argparse
)
set PS5_PAYLOAD=%1
shift
goto :argparse

:runcmd

if "%PS5_PAYLOAD%"=="" (
  echo usage: %0 [-h HOST] [-p PORT] PAYLOAD_PATH
  exit /b 1
)

type %PS5_PAYLOAD% | plink.exe -raw -P %PS5_PORT% %PS5_HOST%
