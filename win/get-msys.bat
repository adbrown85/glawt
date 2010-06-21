@echo off


:: Globals
set MODULE=msys
set MODULE_VERSION=1.0.13
set FTP_SITE=ftp.mirrorservice.org
set FTP_ROOT=pub/sourceforge/m/project/mi/mingw/MSYS
set SUFFIX=-%MODULE%-%MODULE_VERSION%-

:: Start
call ftp\initialize %*

:: core
call ftp\begin msys 1.0.13-2 "MSYS Core"
call ftp\set_folder BaseSystem
call ftp\enqueue_bin msysCORE

:: termcap
call ftp\begin termcap 0.20050421_1-2 "Terminal capabilities database"
call ftp\enqueue_bin termcap
call ftp\enqueue_dll libtermcap -0

:: regex
call ftp\begin regex 1.20090805-2 "Regular Expressions"
call ftp\enqueue_dll libregex -1

:: gettext
call ftp\begin gettext 0.17-2 "GNU internationalization library"
set SUFOLD=%SUFFIX%
set SUFFIX=-msys-
call ftp\enqueue_dll libintl -8
set SUFFIX=%SUFOLD%

:: iconv
call ftp\begin libiconv 1.13.1-2 "Character encoding conversion"
call ftp\enqueue_dll libiconv -2

:: bash
call ftp\begin bash 3.1.17-3 "Bourne Again SHell"
call ftp\enqueue_bin %NAME%

:: coreutils
call ftp\begin coreutils 5.97-3 "Commonly used POSIX utilities"
call ftp\enqueue_bin %NAME%

:: make
call ftp\begin make 3.81-3 "Build tool"
call ftp\enqueue_bin %NAME%

:: gawk
call ftp\begin gawk 3.1.7-2 "Text file manipulation"
call ftp\enqueue_bin %NAME%

:: grep
call ftp\begin grep 2.5.4-2 "Matches patterns in files"
call ftp\enqueue_bin %NAME%

:: sed
call ftp\begin sed 4.2.1-2 "Stream editor"
call ftp\enqueue_bin %NAME%

:: diff
call ftp\begin diffutils 2.8.7.20071206cvs-3 "Differences between files"
call ftp\enqueue_bin %NAME%

:: less
call ftp\begin less 436-2 "Display text files"
call ftp\enqueue_bin %NAME%

:: mktemp
call ftp\begin mktemp 1.6-2 "Safely create temp files"
call ftp\enqueue_bin %NAME%

:: vim
call ftp\begin vim 7.2-2 "Text editor"
call ftp\enqueue_bin %NAME%

:: zlib
call ftp\begin zlib 1.2.3-2 "Compression library"
call ftp\enqueue_dll %NAME%

:: gdbm
call ftp\begin gdbm 1.8.3-3 "GNU Database Routines"
call ftp\enqueue_dll libgdbm -3

:: crypt
call ftp\begin crypt 1.1_1-3 "DES Encryption library"
call ftp\enqueue_dll libcrypt -0

:: perl
call ftp\begin perl 5.6.1_2-2 "Scripting language"
call ftp\enqueue_bin %NAME%

:: cvs
call ftp\begin cvs 1.12.13-2 "Version control system"
call ftp\enqueue_bin %NAME%

:: m4
call ftp\begin m4 1.4.14-1 "Macro processor"
call ftp\enqueue_bin %NAME%

:: Finish
call ftp\download
call ftp\stage
call ftp\finalize
