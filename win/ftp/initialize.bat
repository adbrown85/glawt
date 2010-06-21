@echo off


:: Check if unattended
if "%1"=="--unattended" (
	set UNATTENDED=TRUE
) else (
	set UNATTENDED=FALSE
)


:: Initialize user and password
set FTP_USER=anonymous
set FTP_PASS=anonymous

:: Initialize data files
set FTP_SCRIPT=ftp\ftp-script.dat
set FTP_QUEUE=ftp\ftp-queue.dat
echo.> %FTP_SCRIPT%
echo.> %FTP_QUEUE%

:: Initialize common extensions
set EXE=.exe
set TGZ=.tar.gz
set TLZ=.tar.lzma
set ZIP=.zip
set BIN_TGZ=bin%TGZ%
set DEV_TGZ=dev%TGZ%
set DLL_TGZ=dll%TGZ%
set BIN_TLZ=bin%TLZ%
set DEV_TLZ=dev%TLZ%
set DLL_TLZ=dll%TLZ%

:: Create directories
set DOWNLOADS=downloads
if NOT EXIST "%DOWNLOADS%\%MODULE%" (
	mkdir "%DOWNLOADS%\%MODULE%"
)
set STAGE=stage
if NOT EXIST "%STAGE%\%MODULE%" (
	mkdir "%STAGE%\%MODULE%"
)

:: Empty queue
set QUEUE_EMPTY=TRUE
echo.
echo.
echo Checking files...  ('S' for skipped, 'Q' for queued)

:: Open connection
echo open %FTP_SITE% > %FTP_SCRIPT%

:: Login
echo user %FTP_USER% >> %FTP_SCRIPT%
echo %FTP_PASS% >> %FTP_SCRIPT%

:: Switch mode
echo bin >> %FTP_SCRIPT%

:: Change directories
echo cd "%FTP_ROOT%" >> %FTP_SCRIPT%
echo lcd "%DOWNLOADS%\%MODULE%" >> %FTP_SCRIPT%
