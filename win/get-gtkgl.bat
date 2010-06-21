@echo off


:: Globals
set MODULE=gtkgl
set FTP_SITE=ftp.mirrorservice.org
set FTP_ROOT=pub/sourceforge/g/project/gt/gtkglext
set SUFFIX=

:: Initialize
call ftp\initialize %*

:: gtkglext
call ftp\begin gtkglext 1.2.0 "Gtk GL library"
call ftp\set_folder %NAME%
call ftp\set_subfolder %VERSION%
call ftp\enqueue_archive gtkglext %TGZ%

:: gtkglextmm
call ftp\begin gtkglextmm 1.2.0 "Gtk GL C++ bindings"
call ftp\set_folder %NAME%
call ftp\set_subfolder %VERSION%
call ftp\enqueue_archive gtkglextmm %TGZ%

:: Finish
call ftp\download
call ftp\stage
call ftp\finalize
