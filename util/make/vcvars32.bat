@echo off
::$RCSfile: vcvars32.bat,v $
::
::   DESC : Load Microsoft Visual Studio path definitions
::
::    CVS : $Revision: 1.5 $
::          $Name: V1_1_1 $
::          $Date: 2002/08/13 15:32:04 $
::          $Author: rick $
::
:: Root of Visual Developer Studio Common files.
:: Edit this for your environment
::
@if NOT EXIST "C:\Program Files\Microsoft Visual Studio\VC98\Bin\vcvars32.bat" goto port
@call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\vcvars32.bat"
@goto end
:port
@echo "*** Porting"
@echo "Visual C++ build cannot continue, Microsoft vcvars32.bat not found."
@echo "Correct the path in util\make\vcvars32.bat, to point to your install"
@echo "                          OR"
@echo "Delete util/make/vc.mak to ignore this toolchain"
:end
