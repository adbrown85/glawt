

:: Run script if files are queued
if %QUEUE_EMPTY%==FALSE (
	echo.
	echo.
	echo Downloading...
	echo quit >> %FTP_SCRIPT%
	ftp -n -s:%FTP_SCRIPT% > NUL
)

:: Confirm
echo.
echo.
echo Results...
if %QUEUE_EMPTY%==FALSE (
	for /F "tokens=*" %%i in (%FTP_QUEUE%) do (
		call ftp\check %%i
	)
) else (
	echo   All files already downloaded.
)