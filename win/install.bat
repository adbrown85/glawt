@echo off


:: Call each get
call get-glew --unattended
call get-gtk --unattended
call get-gtkgl --unattended
call get-mingw --unattended
call get-msys --unattended

:: Pause
pause