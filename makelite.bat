::==============================================================================
::$RCSfile: makelite.bat,v $
::
::   DESC : TH Lite Clean,Build,Run on VC and GCC with Consolidated Log
::
:: AUTHOR : Rick Foos, ECL, LLC 
::
:: EEMBC : Technical Advisory Group (TechTAG)
::
::    CVS : $Revision: 1.13 $
::------------------------------------------------------------------------------
:: Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
:: Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
::==============================================================================
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
