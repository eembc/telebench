::==============================================================================
::$RCSfile: makereg.bat,v $
::
::   DESC : TH Regular Clean,Build,Run on VC and GCC with Consolidated Log
::
:: AUTHOR : Rick Foos, ECL, LLC 
::
:: EEMBC : Technical Advisory Group (TechTAG)
::
::    CVS : $Revision: 1.11 $
::------------------------------------------------------------------------------
:: Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
:: Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
::==============================================================================
@echo off
:: GCC
@make VER=%VER% TOOLCHAIN=gcc LITE= %1
@if NOT EXIST ..\gcc_time%VER%.log type ..\util\awk\titletime.txt >..\gcc_time%VER%.log
@if     EXIST gcc_time%VER%.log type gcc_time%VER%.log >>..\gcc_time%VER%.log
:: Visual C++
:: See if user has removed visual C
@if NOT EXIST ..\util\make\vc.mak goto end
:: PORTING: Set up Visual C variables in your environment
@if "%MSVCDir%" == "" call ..\util\make\vcvars32
@if "%MSVCDir%" == "" goto vcerror
@make VER=%VER% TOOLCHAIN=vc LITE= %1
@if NOT EXIST ..\vc_time%VER%.log type ..\util\awk\titletime.txt >..\vc_time%VER%.log
@if     EXIST vc_time%VER%.log type vc_time%VER%.log >>..\vc_time%VER%.log
@goto end
:vcerror
@echo "***ERROR: VC++ NOT FOUND: edit util/make/vcvars32.bat
:end
