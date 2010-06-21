@echo off


:: Checks if a file was downloaded correctly.
::
	
	call ftp\file_size %1
	if %FILE_SIZE% GTR 0 (
		echo   [GOOD] %1
	) else (
		echo   [FAIL] %1
		del "%1"
		set DOWNLOAD_FAILED=TRUE
	)
