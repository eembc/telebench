:: ============================================================================
::
:: Copyright (C) EEMBC(R) All Rights Reserved
::
:: This software is licensed with an Acceptable Use Agreement under Apache 2.0.
:: Please refer to the license file (LICENSE.md) included with this code.
::
:: ============================================================================
@if "%os%%" == "Windows_NT" setlocal
@set VER=
@set called=%1
@if "%called%" == ""  set called=techtag
:: top level section
@if NOT "%called%" == "techtag" goto skiptop
@cvs -Q checkout -PAd th eembc2/techtag/th
@cvs -Q checkout -PAd th_lite eembc2/techtag/th_lite
@cvs -Q checkout -PAd util eembc2/techtag/util
:skiptop
@if "%os%%" == "Windows_NT" goto for_nt
@for %%i in (8_16-bit automotive consumer networking office telecom) do call me %called% %2 %%i
@goto end
:for_nt
@for %%i in (8_16-bit automotive consumer networking office telecom) do pushd %%i&&call ..\%called% %2&&popd
:end
