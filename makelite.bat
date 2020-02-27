:: ============================================================================
::
:: Copyright (C) EEMBC(R) All Rights Reserved
::
:: This software is licensed with an Acceptable Use Agreement under Apache 2.0.
:: Please refer to the license file (LICENSE.md) included with this code.
::
:: ============================================================================
@echo off
:: GCC
@make VER=%VER% TOOLCHAIN=gcc LITE=_lite %1
@if NOT EXIST ..\gcc_time%VER%_lite.log type ..\util\awk\titletime.txt >..\gcc_time%VER%_lite.log
@if     EXIST gcc_time%VER%_lite.log type gcc_time%VER%_lite.log >>..\gcc_time%VER%_lite.log
:: Visual C++
:: See if user has removed visual C
@if NOT EXIST ..\util\make\vc.mak goto end
:: PORTING: Set up Visual C variables in your environment
@if "%MSVCDir%" == "" call ..\util\make\vcvars32
@if "%MSVCDir%" == "" goto vcerror
:: For each TOOLCHAIN
@make VER=%VER% TOOLCHAIN=vc LITE=_lite %1
@if NOT EXIST ..\vc_time%VER%_lite.log type ..\util\awk\titletime.txt >..\vc_time%VER%_lite.log
@if     EXIST vc_time%VER%_lite.log type vc_time%VER%_lite.log >>..\vc_time%VER%_lite.log
@goto end
:vcerror
@echo "***ERROR: VC++ NOT FOUND: edit util/make/vcvars32.bat
:end
