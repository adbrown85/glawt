@echo off


:: Queue a binary file to be downloaded.
::
:: @see enqueue_archive
::
:: @param FILENAME
:: @param DIRECTORY
:: @param SUBDIRECTORY
	
	call ftp\enqueue_archive %1 bin%TLZ% %2 %3

