@echo off


:: Sets FILE_SIZE to the size of a file
:: 
:: @param %1 Filename
:: 
	
	:: Reset
	set FILE_SIZE=0
	
	:: Check if no argument
	if "%1"=="" (
		echo WARNING: file_size called with no argument.
		exit /B
	)
	
	:: Set size if file exists
	if EXIST %1 (
		set FILE_SIZE=%~z1
	)

