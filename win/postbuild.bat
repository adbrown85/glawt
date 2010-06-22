@echo off


:: Start
call postbuild\initialize %*

:: C++
call postbuild\group C++
call postbuild\copy libgcc_s_dw2-1.dll
call postbuild\copy libstdc++-6.dll

:: GTKGL
call postbuild\group GTKGL
call postbuild\copy libgdkglext-win32-1.0-0.dll
call postbuild\copy libgtkglext-win32-1.0-0.dll
call postbuild\copy libgdkglextmm-win32-1.2-0.dll
call postbuild\copy libgtkglextmm-win32-1.2-0.dll

:: GLEW
call postbuild\group GLEW
call postbuild\copy libGLEW.dll

:: Finish
call postbuild\finalize
