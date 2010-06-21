@echo off


:: Queue a binary file to be downloaded.
::
:: @see enqueue_archive
::
:: @param FILENAME
:: @param DIRECTORY
:: @param SUBDIRECTORY
	
	call ftp\enqueue_archive %1 dev%TGZ% %2 %3

