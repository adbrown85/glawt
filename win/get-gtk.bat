@echo off


:: Globals
set MODULE=gtk
set FTP_SITE=ftp.gnome.org
set FTP_ROOT=pub/GNOME/binaries/win32
set SUFFIX=

:: Start
call ftp\initialize %*

:: gtkmm
call ftp\begin gtkmm 2.16.0-4 "GTK+ C++ Bindings"
call ftp\set_folder gtkmm
call ftp\set_subfolder 2.16
call ftp\enqueue_archive gtkmm-win32-devel %EXE%

:: freetype
call ftp\begin freetype 2.3.12-1 "Font rasterization engine"
call ftp\set_folder dependencies
call ftp\set_subfolder .
call ftp\enqueue %NAME%-dev_%VERSION%_win32.zip

:: fontconfig
call ftp\begin fontconfig 2.8.0-2 "Font configuration and access library"
call ftp\set_folder dependencies
call ftp\set_subfolder .
call ftp\enqueue %NAME%-dev_%VERSION%_win32.zip

:: Finish
call ftp\download
call ftp\stage
call ftp\finalize
