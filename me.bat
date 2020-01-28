::   DESC : Stub for Windows 98/ME
::
::    CVS : $Revision: 1.3 $
::          $Date: 2002/07/27 00:20:41 $
::          $Author: rick $
:: $Log: me.bat,v $
:: Revision 1.3  2002/07/27 00:20:41  rick
:: Fix 95/ME calls
::
:: Revision 1.2  2002/04/09 20:20:43  rick
:: Support 98/ME in checkout.bat
::
::
@echo off
@set medir=%3
@set meparm=%2
@if NOT "%3" == "" goto skipslide
@set medir=%2
@set meparm=
:skipslide
@cd %medir%
@call ..\%1 %meparm%
@cd ..


