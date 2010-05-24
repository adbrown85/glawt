# Initialize
AC_PREREQ([2.65])
AC_INIT([Gander], [1.0], [adb1413@rit.edu], , [http://gander.sourceforge.net])
AC_CONFIG_SRCDIR([src/gander.cxx])
AC_CONFIG_HEADERS([config.h:config.in])

# Checks for programs
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_SED
if test -z $SED; then
	echo "--------------------------------------------------"
	echo " Sed is required to build Gander.                 "
	echo "--------------------------------------------------"
fi
PKG_PROG_PKG_CONFIG

# Check for GNU Make
echo -n "Checking for GNU Make..."
make_command=""
for i in "$MAKE" make gmake gnumake; do
	if (sh -c "$i --version" 2>/dev/null | grep GNU >/dev/null); then
		make_command=$i;
		break;
	fi
done
if test -z $make_command; then
	echo " no"
	echo "-------------------------------------------------------"
	echo " GNU Make is required to build Gander.                 "
	echo " Please visit http://www.gnu.org/software/make/        "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
else
	echo " yes"
fi

# Checks for libraries
AC_SEARCH_LIBS([cos], [m])

# Check for GTKmm
error_no_gtkmm() {
	echo "no"
	echo "-------------------------------------------------------"
	echo " GTKmm (gtkmm-2.4) is required to build Gander.        "
	echo " Try 'sudo apt-get install libgtkmm-2.4-dev'           "
	echo " Or visit 'http://www.gtkmm.org/'                      "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
echo -n "checking for gtkmm-2.4... "
PKG_CHECK_EXISTS([gtkmm-2.4],[echo "yes"],error_no_gtkmm)

# Check for GTKmm
error_no_gtkglmm() {
	echo "no"
	echo "-------------------------------------------------------"
	echo " GTKGLmm (gtkglextmm-1.2) is required to build Gander. "
	echo " Try 'sudo apt-get install libgtkglextmm-x11-1.2-dev'  "
	echo " Or visit 'http://projects.gnome.org/gtkglext/'        "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
echo -n "checking for gtkglextmm-1.2... "
PKG_CHECK_EXISTS([gtkglextmm-1.2],[echo "yes"],error_no_gtkglmm)

# Check for DevIL
error_no_devil() {
	echo "-------------------------------------------------------"
	echo " DevIL (ILUT) is required to install Gander.           "
	echo " Try 'sudo apt-get install libdevil-dev'               "
	echo " Or visit 'http://openil.sourceforge.net'              "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
AC_SEARCH_LIBS([ilGetInteger], [IL], , [error_no_devil])
AC_SEARCH_LIBS([iluGetInteger], [ILU], , [error_no_devil])
AC_SEARCH_LIBS([ilutGetInteger], [ILUT], , [error_no_devil])
AC_CHECK_HEADER([IL/il.h], , [error_no_devil])
AC_CHECK_HEADER([IL/ilu.h], , [error_no_devil])
AC_CHECK_HEADER([IL/ilut.h], , [error_no_devil])

# Checks for library functions
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([sqrt])
AC_C_INLINE
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Manual variables
modules='data graph basic advanced backend frontend'
AC_SUBST([modules])

# Finish
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])
PKG_CHECK_MODULES([DEPS], [gtkmm-2.4 gtkglextmm-1.2])
AC_OUTPUT

echo \
"--------------------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 prefix      ${prefix}
 CXX         ${CXX}
 CXXFLAGS    ${CXXFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 modules     ${modules}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"
