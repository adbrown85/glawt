/*
 * WindowGLUT.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "WindowGLUT.hpp"
#ifdef HAVE_GLUT


/** Adds the canvas to the window. */
void WindowGLUT::add(Canvas *canvas) {
	
	this->canvas = canvas;
	glutInitWindowSize(canvas->getWidth(), canvas->getHeight());
}


void* WindowGLUT::getNativeWindow() {
	
	return NULL;
}


/** Starts processing the window. */
void WindowGLUT::run() {
	
	glutMainLoop();
}


/** Makes the window visible on screen. */
void WindowGLUT::show() {
	
	glutCreateWindow(getTitle().c_str());
	(dynamic_cast<CanvasGLUT*>(canvas))->onRealize();
}



#endif // HAVE_GLUT
