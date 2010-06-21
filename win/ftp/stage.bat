

:: Extracting
echo.
echo.
if %QUEUE_EMPTY%==FALSE (
	echo Extracting...
	for /F "tokens=*" %%i in (%FTP_QUEUE%) do (
		call ftp\extract %%i
	)
)