/*
 * CanvasFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CANVASFACTORY_HPP
#define CANVASFACTORY_HPP
#include "common.h"
#include "Canvas.hpp"
#include "CanvasGTK.hpp"
#include "CanvasGLUT.hpp"
using namespace std;


/** @brief Utility for getting a Canvas for the correct toolkit.
 * @ingroup graphics
 */
class CanvasFactory {
public:
	static Canvas* create(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
};


#endif
