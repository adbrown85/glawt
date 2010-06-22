@echo off


:: End of the postbuild process.
:: 
	
	:: Get parameters
	if "%POSTBUILD_UNATTENDED%"=="FALSE" (
		echo.
		echo.
		pause
	)
