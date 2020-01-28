::==============================================================================
::$RCSfile: makeall.bat,v $
::
::   DESC : Clean build and run VC and GCC with Consolidated log file
::
:: AUTHOR : Rick Foos, ECL, LLC 
::
::    CVS : $Revision: 1.9 $
::------------------------------------------------------------------------------
:: Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
:: Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
::==============================================================================
@echo off
@if NOT EXIST makefile goto end
@call ..\makereg %1
@call ..\makelite %1
:end
