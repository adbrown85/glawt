/*
 * WindowGLUT.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLAWT_WINDOWGLUT_HPP
#define GLAWT_WINDOWGLUT_HPP
#include "common.h"
#ifdef HAVE_GLUT
#include <GL/glut.h>
#include "Window.hpp"
#include "CanvasGLUT.hpp"
using namespace std;


class WindowGLUT : public Window {
public:
	WindowGLUT() {}
	virtual ~WindowGLUT() {}
	virtual void add(Canvas *canvas);
	virtual void* getNativeWindow();
	virtual void hide();
	virtual void run();
	virtual void setIcon(string filename) {}
	virtual void show();
private:
	Canvas *canvas;
};


#endif // HAVE_GLUT
#endif
