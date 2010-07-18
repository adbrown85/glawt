/*
 * WindowFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "WindowFactory.hpp"


Window* WindowFactory::create() {
	
#ifdef HAVE_GTK
	return new WindowGTK();
#else
	return new WindowGLUT();
#endif
}

