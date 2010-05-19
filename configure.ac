# Initialize
AC_PREREQ([2.65])
AC_INIT([gander], [1.0], [adb1413@rit.edu])
AC_CONFIG_SRCDIR([src/Gander.cxx])

# Checks for programs
AC_PROG_CXX
AC_PROG_INSTALL

# Checks for libraries
AC_SEARCH_LIBS([cos], [m])
AC_SEARCH_LIBS([glutInit], [glut])
AC_SEARCH_LIBS([ilGetInteger], [IL])
AC_SEARCH_LIBS([iluGetInteger], [ILU])
AC_SEARCH_LIBS([ilutGetInteger], [ILUT])

# Checks for headers
AC_CHECK_HEADER([GL/glut.h],,AC_MSG_ERROR([Cannot find Glut.]))
AC_CHECK_HEADER([IL/il.h],,AC_MSG_ERROR([Cannot find 'il.h' from DevIL.]))
AC_CHECK_HEADER([IL/ilu.h],,AC_MSG_ERROR([Cannot find 'ilu.h' from DevIL.]))
AC_CHECK_HEADER([IL/ilut.h],,AC_MSG_ERROR([Cannot find 'ilut.h' from DevIL.]))

# Checks for library functions
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([sqrt])
AC_C_INLINE
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Manual variables
modules="data graph basic advanced backend frontend"
AC_SUBST([modules])

# Finish
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

echo \
"-------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 prefix      ${prefix}
 CXX         ${CXX}
 CXXFLAGS    ${CXXFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 modules     ${modules}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------"
