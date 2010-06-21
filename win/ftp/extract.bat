@echo off

:: Extracts an archive that was downloaded.
:: 
:: @param ARCHIVE
	
	:: Set parameters
	set ARCHIVE=%1
	set DESTINATION=%STAGE%\%MODULE%
	
	:: Check file size
	call ftp\file_size %ARCHIVE%
	if %FILE_SIZE% EQU 0 (
		echo   Skipping %ARCHIVE%
		exit /B
	)
	
	:: Check extension
	set EXTENSION=%~x1
	if "%EXTENSION%"==".exe" (
		echo   Copying %ARCHIVE%
		copy %ARCHIVE% %DESTINATION%
		exit /B
	)
	
	:: Extract
	echo   %ARCHIVE%
	7za x -o%DESTINATION% %ARCHIVE% -y > NUL
	
	:: Check for compressed tarball
	set TARBALL=
	if "%EXTENSION%"==".gz" set TARBALL=%DESTINATION%\%~n1
	if "%EXTENSION%"==".lzma" set TARBALL=%DESTINATION%\%~n1
	if NOT "%TARBALL%"=="" (
		7za x -o%DESTINATION% "%TARBALL%" -y > NUL
		del "%TARBALL%"
	)