@echo off


set INSTALLER=downloads\gtk\gtkmm-win32-devel-2.16.0-4.exe


:: Run installer
echo Running installer...
%INSTALLER% /S /SET_ENVVARS /ALLUSERS /D=C:\gtk
echo.

:: Copy
echo Copying...
echo   "stage\gtk" to "C:\gtk"
if NOT EXIST C:\gtk (
	mkdir C:\gtk
)
xcopy /Q /S /E /Y "stage\gtk\*" "C:\gtk" > NUL

:: Pause
echo.
echo.
pause