/*
 * CanvasFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "CanvasFactory.hpp"


Canvas* CanvasFactory::create(int width, int height) {
	
#ifdef HAVE_GTK
	return new CanvasGTK(width, height);
#else
	return new CanvasGLUT(width, height);
#endif
}

