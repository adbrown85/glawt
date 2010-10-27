/*
 * GLAWTFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLAWT_GLAWTFACTORY_HPP_
#define GLAWT_GLAWTFACTORY_HPP_
#include "common.h"
#include "CanvasGLUT.hpp"
#include "CanvasGTK.hpp"
#include "WindowGLUT.hpp"
#include "WindowGTK.hpp"


/** @brief Create GLAWT objects.
 * 
 * @note Makes no attempt at cleaning up the objects.
 * 
 * @ingroup core 
 */
class GLAWTFactory {
public:
	static Canvas* createCanvas(int w=CANVAS_WIDTH, int h=CANVAS_HEIGHT);
	static Window* createWindow();
};

#endif
