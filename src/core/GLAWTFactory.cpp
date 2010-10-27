/*
 * GLAWTFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GLAWTFactory.hpp"


/** @return Pointer to a new canvas. */
Canvas* GLAWTFactory::createCanvas(int width, int height) {
#ifdef HAVE_GTK
	return new CanvasGTK(width, height);
#else
	return new CanvasGLUT(width, height);
#endif
}

/** @return Pointer to a new window. */
Window* GLAWTFactory::createWindow() {
#ifdef HAVE_GTK
	return new WindowGTK();
#else
	return new WindowGLUT();
#endif
}
