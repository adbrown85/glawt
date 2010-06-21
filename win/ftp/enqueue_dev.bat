@echo off


:: Queue a development file to be downloaded.
::
:: @see enqueue_archive
::
:: @param FILENAME
:: @param DIRECTORY
:: @param SUBDIRECTORY
	
	call ftp\enqueue_archive %1 dev%TLZ% %2 %3

