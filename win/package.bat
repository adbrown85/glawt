@echo off

:: Globals
set "PACKAGE_DIR=C:\Program Files\Gander"
set "PACKAGE_TARNAME=gander"
set "PACKAGE_VERSION=0.95"
set "ZIPFILE=%PACKAGE_TARNAME%-%PACKAGE_VERSION%-win.zip"

:: Zip up directory
7za a %ZIPFILE% "%PACKAGE_DIR%"

:: Pause
if NOT "%1"=="--unattended" (
	echo.
	echo.
	pause
)
