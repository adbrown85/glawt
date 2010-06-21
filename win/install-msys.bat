

:: Initialize
set BASE=C:\msys


:: Download
call get-msys --unattended

:: Copy
echo Copying...
echo   "stage\msys" to "C:\msys"
xcopy /Q /S /E /Y "stage\msys\*" "C:\msys\" > NUL

:: Begin setup
echo Setting up...

:: Add mingw directory for mounting
set DIRECTORY=%BASE%\mingw
if NOT EXIST %DIRECTORY% (
	echo   Making "%DIRECTORY%" for mounting.
	mkdir %DIRECTORY%
)

:: Add fstab file for mounting
set DIRECTORY=%BASE%\etc
if NOT EXIST %DIRECTORY%\fstab (
	echo   Making "%DIRECTORY%\fstab".
	copy %DIRECTORY%\fstab.sample %DIRECTORY%\fstab > NUL
)

:: Pause
echo.
echo.
pause
