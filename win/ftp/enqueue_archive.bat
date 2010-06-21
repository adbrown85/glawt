@echo off


:: Queue an archive file to be downloaded.
::
:: @note Adds VERSION and SUFFIX before EXTENSION. 
:: 
:: @see ftp\enqueue
:: 
:: @param FILENAME
:: @param EXTENSION
:: @param DIRECTORY
:: @param SUBDIRECTORY
	
	:: Copy parameters
	set FILENAME=%1
	set EXTENSION=%2
	set DIRECTORY=%3
	set SUBDIRECTORY=%4
	
	:: Fix filename
	set FILENAME=%FILENAME%-%VERSION%%SUFFIX%%EXTENSION%
	
	:: Add to queue
	call ftp\enqueue %FILENAME% %DIRECTORY% %SUBDIRECTORY%

