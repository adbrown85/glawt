@echo off


:: Globals
set MODULE=mingw
set FTP_SITE=ftp.mirrorservice.org
set FTP_ROOT=pub/sourceforge/m/project/mi/mingw/MinGW
set SUFFIX=-mingw32-

:: Start
call ftp\initialize %*

:: binutils
call ftp\begin binutils 2.20.1-2 "GNU Binary Utilities"
call ftp\set_folder BaseSystem/GNU-Binutils
call ftp\set_subfolder %NAME%-2.20.1
call ftp\enqueue_bin_tgz binutils

:: mingwrt
call ftp\begin mingwrt 3.18 "MinGW Runtime"
call ftp\set_folder BaseSystem/RuntimeLibrary/MinGW-RT
call ftp\enqueue_dev_tgz mingwrt
call ftp\enqueue_dll_tgz mingwrt

:: w32api
call ftp\begin w32api 3.14 "Windows API"
call ftp\set_folder BaseSystem/RuntimeLibrary/Win32-API
call ftp\enqueue_dev_tgz w32api

:: mpc
call ftp\begin mpc 0.8.1-1 "Math Precision library"
call ftp\enqueue_dev mpc
call ftp\enqueue_dll libmpc -2

:: mpfr
call ftp\begin mpfr 2.4.1-1 "Multiple-Precision Floating-point library"
call ftp\enqueue_dev mpfr
call ftp\enqueue_dll libmpfr -1

:: gmp
call ftp\begin gmp 5.0.1-1 "GNU Multiple-Precision arithmetic library"
call ftp\enqueue_dev gmp
call ftp\enqueue_dll libgmp -10

:: pthreads
call ftp\begin pthreads-w32 2.8.0-3 "Posix Threads"
call ftp\enqueue_dev pthreads-w32
call ftp\enqueue_dll libpthread -2

:: gcc
call ftp\begin gcc 4.5.0-1 "GNU Compiler Collection"
call ftp\set_folder BaseSystem/GCC/Version4
call ftp\enqueue_dll libgomp -1
call ftp\enqueue_dll libssp -0
call ftp\enqueue_bin gcc-core
call ftp\enqueue_dll libgcc -1
call ftp\enqueue_bin gcc-c++
call ftp\enqueue_dll libstdc++ -6

:: expat
call ftp\begin expat 2.0.1-1 "Stream-oriented XML parser"
call ftp\enqueue_dll_tgz libexpat -1

:: gdb
call ftp\begin gdb 7.1-2 "GNU Debugger"
call ftp\set_folder BaseSystem/GDB 
call ftp\set_subfolder GDB-7.1
call ftp\enqueue_bin_tgz gdb

:: libtool
call ftp\begin libtool 2.2.7a-1 "GNU shared library generation tool"
call ftp\enqueue_bin libtool

:: autoconf
call ftp\begin autoconf2.5 2.64-1 "Automatic configure script builder"
call ftp\set_folder autoconf/%NAME%
call ftp\enqueue_bin %NAME%

:: autoconf wrapper
call ftp\begin autoconf 7-1 "Automatically execute correct autoconf"
call ftp\set_folder autoconf/wrapper
call ftp\enqueue_bin autoconf

:: automake
call ftp\begin automake1.7 1.7.9-1 "Produce portable makefiles"
call ftp\set_folder automake/%NAME%
call ftp\enqueue_bin %NAME%

:: automake
call ftp\begin automake1.11 1.11-1 "Produce portable makefiles"
call ftp\set_folder automake/%NAME%
call ftp\enqueue_bin %NAME%

:: automake wrapper
call ftp\begin automake 4-1 "Automatically execute correct automake"
call ftp\set_folder automake/wrapper
call ftp\enqueue_bin automake

:: Finish
call ftp\download
call ftp\stage
call ftp\finalize
