:: ============================================================================
::
:: Copyright (C) EEMBC(R) All Rights Reserved
::
:: This software is licensed with an Acceptable Use Agreement under Apache 2.0.
:: Please refer to the license file (LICENSE.md) included with this code.
::
:: ============================================================================
@echo off
@if NOT EXIST makefile goto end
@call ..\makereg %1
@call ..\makelite %1
:end
