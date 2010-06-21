@echo off


:: Delete storage
del %FTP_QUEUE%
del %FTP_SCRIPT%
echo.
echo.

:: Pause
if "%DOWNLOAD_FAILED%"=="TRUE" (
	echo ERROR: One or more downloads failed.
	pause
	exit /B
)
if "%UNATTENDED%"=="FALSE" (
	pause
	exit /B
)