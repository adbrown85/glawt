@echo off


:: Copies a file from the base to the destination.
:: 
:: %1 Filename
::
	
	echo   %1
	copy "%POSTBUILD_BASE_DIR%\%1" "%POSTBUILD_DEST_DIR%\%1" > NUL
