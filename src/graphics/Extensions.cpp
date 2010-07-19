/*
 * Extensions.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Extensions.hpp"
PFNGLBINDFRAGDATALOCATIONGANPROC glBindFragDataLocationGAN=NULL;
PFNGLGETFRAGDATALOCATIONGANPROC glGetFragDataLocationGAN=NULL;


void Extensions::load() {
	
	loadGLUT();
	loadGLEW();
	loadGTK();
}


void Extensions::loadGLEW() {
#ifdef HAVE_GLEW
	
	GLenum err;
	
	err = glewInit();
	if (err != GLEW_OK) {
		throw Exception("[Gander] Could not initialize GLEW");
	}
#endif
}


void Extensions::loadGLUT() {
#ifdef HAVE_GLUT
#ifdef FREEGLUT
	
	glBindFragDataLocationGAN = (PFNGLBINDFRAGDATALOCATIONPROC)
		glutGetProcAddress("glBindFragDataLocation");
	glGetFragDataLocationGAN = (PFNGLGETFRAGDATALOCATIONPROC)
		glutGetProcAddress("glGetFragDataLocation");
#endif
#endif
}


void Extensions::loadGTK() {
#ifdef HAVE_GTK
	
	glBindFragDataLocationGAN = (PFNGLBINDFRAGDATALOCATIONPROC)
		Gdk::GL::get_proc_address("glBindFragDataLocation");
	glGetFragDataLocationGAN = (PFNGLGETFRAGDATALOCATIONPROC)
		Gdk::GL::get_proc_address("glGetFragDataLocation");
#endif
}

