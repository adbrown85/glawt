@echo off


:: Globals
set MODULE=glew
set FTP_SITE=ftp.mirrorservice.org
set FTP_ROOT=pub/sourceforge/g/project/gl/glew
set SUFFIX=

:: Start
call ftp\initialize %*

:: glew
call ftp\begin glew 1.5.4 "GL Extension Wrangler"
call ftp\set_folder %NAME%
call ftp\set_subfolder %VERSION%
call ftp\enqueue_archive glew %ZIP%

:: Finish
call ftp\download
call ftp\stage
call ftp\finalize
