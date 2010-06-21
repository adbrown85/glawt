@echo off


:: Sets important variables used in FTP commands.
:: 
:: @note FOLDER is reset to NAME
:: @note SUBFOLDER is reset to NAME-VERSION
:: 
:: @param NAME
:: @param VERSION
:: @param DESCRIPTION
	
	:: Copy parameters
	set NAME=%1
	set VERSION=%2
	set DESCRIPTION=%~3
	
	:: Reset to defaults
	set FOLDER=%NAME%
	set SUBFOLDER=%NAME%-%VERSION%
	
	:: Print
	echo   %NAME% (%DESCRIPTION%)
