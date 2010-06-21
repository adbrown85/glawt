@echo off


:: Queue a binary file to be downloaded.
::
:: @see ftp\enqueue_archive
::
:: @param FILENAME
:: @param DIRECTORY
:: @param SUBDIRECTORY
	
	call ftp\enqueue_archive %1 bin%TGZ% %2 %3

