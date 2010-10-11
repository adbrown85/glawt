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

# Check for options
glut_help='Use GLUT instead of GTKGL.'
AC_ARG_WITH(glut, AS_HELP_STRING([--with-glut], [$glut_help]))
glew_help='Do not try to load new OpenGL features.'
AC_ARG_WITH(glew, AS_HELP_STRING([--without-glew], [$glew_help]))
images_help='No support for loading 2D images as textures.'
AC_ARG_ENABLE(images, AS_HELP_STRING([--disable-images], [$images_help]))

# Check for GTKGLmm
error_no_gtkglmm() {
	echo "no"
	echo "-------------------------------------------------------"
	echo " GTKGLextmm is needed for OpenGL by default.           "
	echo " Try 'sudo apt-get install libgtkglextmm-x11-1.2-dev'  "
	echo " Or visit 'http://projects.gnome.org/gtkglext/'        "
	echo " Alternatively, add '--with-glut' to use GLUT instead. "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
if test "x$with_glut" != 'xyes'; then
	echo -n "checking for gtkglextmm-1.2... "
	PKG_CHECK_EXISTS([gtkglextmm-1.2], [echo "yes"], [error_no_gtkglmm])
	AC_DEFINE([HAVE_GTK], [1], [Define to 1 if GTKGLmm is available.])
fi

# Check for GLUT
error_no_glut() {
	echo "-------------------------------------------------------"
	echo " You chose GLUT for OpenGL but it can't be found.      "
	echo " Try 'sudo apt-get install freeglut3-dev'              "
	echo " Or visit 'http://freeglut.sourceforge.net'            "
	echo " Remove '--with-glut' to use GTKGLextmm instead.       "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
if test "x$with_glut" = 'xyes'; then
	AC_SEARCH_LIBS([glutInit], [glut], , [error_no_glut])
	AC_CHECK_HEADER([GL/glut.h], , [error_no_glut])
	AC_DEFINE([HAVE_GLUT], [1], [Define to 1 if GLUT is available.])
	echo "-------------------------------------------------------"
	echo " You chose to use GLUT instead of GTKGLextmm.          "
	echo " Some features requiring GTK will not be available:    "
	echo "   - Side panel for examining scene                    "
	echo "   - Bottom panel showing log messages                 "
	echo "-------------------------------------------------------"
fi

# Check for GLEW
error_no_glew() {
	echo "-------------------------------------------------------"
	echo " GLEW is usually needed to load some OpenGL features.  "
	echo " Try 'sudo apt-get install libglew-dev'                "
	echo " Or visit 'http://glew.sourceforge.net/'               "
	echo " Alternatively, add '--without-glew' to ignore.        "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
if test "x$with_glew" = 'xyes'; then
	$use_glew = 'yes';
elif test "$build_os" = 'mingw32' -a "x$with_glew" != 'xno'; then
	$use_glew = 'yes';
fi
if test "x$use_glew" = 'xyes'; then
	AC_SEARCH_LIBS([glewInit], [GLEW], , [error_no_glew])
	AC_CHECK_HEADER([GL/glew.h], , [error_no_glew])
	AC_DEFINE([HAVE_GLEW], [1], [Define to 1 if GLEW is available.])
fi

# Check for images
error_no_pixbufs() {
	echo "-------------------------------------------------------"
	echo " GDK Pixbufs are needed to load images for textures.   "
	echo " Try 'sudo apt-get install libgtkmm-2.4-dev'           "
	echo " Or visit 'http://www.gtkmm.org/'                      "
	echo " Alternatively, add '--disable-images' to ignore.      "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
if test "x$enable_images" != 'xno'; then
	echo -n "checking for gdkmm-2.4... "
	PKG_CHECK_EXISTS([gdkmm-2.4], [echo "yes"], [error_no_pixbufs])
	AC_DEFINE([HAVE_PIXBUFS], [1], [Define to 1 if GDK Pixbufs are available.])
else
	echo "-------------------------------------------------------"
	echo " You chose to disable images.                          "
	echo " Loading images for textures will not be available.    "
	echo "-------------------------------------------------------"
fi

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

# Prefixes
baseprefix=`basename $prefix`
baseprefix_low=`echo $baseprefix | tr '[[:upper:]]' '[[:lower:]]'`
if test $baseprefix_low = $PACKAGE_TARNAME; then
	datadir='${datarootdir}'
	docdir='${prefix}'/doc
else
	datadir='${datarootdir}'/$PACKAGE_TARNAME
	docdir='${datarootdir}'/doc/$PACKAGE_TARNAME
fi
htmldir='${docdir}'/html

# Finish
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile test/Makefile])
PKG_CHECK_MODULES([DEPS], [gtkmm-2.4 gtkglextmm-1.2])
AC_OUTPUT

echo \
"--------------------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 prefix      ${prefix}
 datarootdir ${datarootdir}
 datadir     ${datadir}
 docdir      ${docdir}
 htmldir     ${htmldir}
 CXX         ${CXX}
 CXXFLAGS    ${CXXFLAGS}
 LDFLAGS     ${LDFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 modules     ${modules}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"
