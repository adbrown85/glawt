@echo off


:: Queue a DLL to be downloaded.
::
:: @see enqueue_archive
::
:: @param FILENAME
:: @param RELEASE      Number after "dll" (with dash)
	
	call ftp\enqueue_archive %1 dll%2%TGZ%