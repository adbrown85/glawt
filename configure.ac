# Initialize
AC_PREREQ([2.65])
AC_INIT([Gander], [0.95], [adb1413@rit.edu], , [http://gander.sourceforge.net])
AC_CONFIG_SRCDIR([src/gander.cxx])
AC_CONFIG_HEADERS([config.h:config.in])

# Check system
AC_CANONICAL_SYSTEM

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

# Check for GTKGLmm
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
AC_DEFINE([HAVE_GTK], [1], [Define to 1 if GTKGLmm is available.])

# Check for GLEW
error_no_glew() {
	echo "-------------------------------------------------------"
	echo " GLEW (GLEW) is required to install Gander.            "
	echo " Try 'sudo apt-get install libglew-dev'                "
	echo " Or visit 'http://glew.sourceforge.net/'               "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
AC_SEARCH_LIBS([glewInit], [GLEW], , [error_no_glew])
AC_CHECK_HEADER([GL/glew.h], , [error_no_glew])

# Checks for library functions
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([sqrt])
AC_C_INLINE
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Manual variables
modules='system graphics scene basic advanced command gui'
AC_SUBST([modules])

# OS-specific compiler switches
if test $build_os = "mingw32"; then
	extra_ldflags="-Wl,--enable-auto-import"
	if test -z "$LDFLAGS"; then
		LDFLAGS="$extra_ldflags"
	else
		LDFLAGS="$LDFLAGS $extra_ldflags"
	fi
fi

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
 LDFLAGS     ${LDFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 modules     ${modules}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"
