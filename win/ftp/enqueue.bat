@echo off


:: Queue a file to be downloaded.
::
:: @note Assumes MODULE, VERSION, NAME, and SUFFIX are already set.
:: @note Assumes FOLDER and SUBFOLDER are already set.
::
:: @see ftp_set
::
:: @param FILENAME
:: 
	
	:: Copy parameters
	set FILENAME=%1
	
	:: Form local and remote filenames
	set LOCAL_FILENAME=%DOWNLOADS%\%MODULE%\%FILENAME%
	set REMOTE_FILENAME=%FOLDER%/%SUBFOLDER%/%FILENAME%
	
	:: Skip if already exists
	call ftp\file_size %LOCAL_FILENAME%
	if %FILE_SIZE% GTR 0 (
		echo     - [S] %FILENAME%
		exit /B
	)
	if EXIST %LOCAL_FILENAME% (
		echo   Removing failed %LOCAL_FILENAME%
		del "%LOCAL_FILENAME%"
	)

	:: Print
	echo     - [Q] %FILENAME%
	set QUEUE_EMPTY=FALSE
	
	:: Add to queue
	echo get "%REMOTE_FILENAME%" >> %FTP_SCRIPT%
	echo %LOCAL_FILENAME% >> %FTP_QUEUE%

