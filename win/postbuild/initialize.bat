@echo off


:: Start of the postbuild process.
:: 
	
	:: Get parameters
	if "%1"=="--unattended" (
		set POSTBUILD_UNATTENDED=TRUE
	) else (
		set POSTBUILD_UNATTENDED=FALSE
	)
	
	:: Set global variables
	set POSTBUILD_BASE_DIR=C:\mingw\bin
	set POSTBUILD_DEST_DIR=C:\Program Files\Gander\bin
	
	:: Create destination directory
	if NOT EXIST "%POSTBUILD_DEST_DIR%" (
		echo.
		echo Creating %POSTBUILD_DEST_DIR%
		mkdir "%POSTBUILD_DEST_DIR%"
	)
