

:: Download
call get-mingw --unattended

:: Copy
echo Copying...
xcopy /Q /S /E /Y "stage\mingw\*" "C:\mingw\" > NUL

:: Pause
echo.
echo.
pause
