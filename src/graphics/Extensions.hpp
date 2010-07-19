/*
 * Extensions.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef EXTENSIONS_HPP
#define EXTENSIONS_HPP
#include "common.h"
#ifdef HAVE_GLUT
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#ifdef HAVE_GTK
#include <gdkmm/gl/query.h>
#endif
#include "Exception.hpp"
using namespace std;


/* Functions to load explicitly */
typedef void (*PFNGLBINDFRAGDATALOCATIONGANPROC)(GLuint,GLuint,const char*);
typedef GLint (*PFNGLGETFRAGDATALOCATIONGANPROC)(GLuint,const char*);
extern PFNGLBINDFRAGDATALOCATIONGANPROC glBindFragDataLocationGAN;
extern PFNGLGETFRAGDATALOCATIONGANPROC glGetFragDataLocationGAN;


/** @brief Utility for loading OpenGL extensions.
 * @ingroup graphics
 */
class Extensions {
public:
	static void load();
protected:
	static void loadGLEW();
	static void loadGLUT();
	static void loadGTK();
};


#endif
