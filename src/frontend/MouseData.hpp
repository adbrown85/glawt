/*
 * MouseData.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSEDATA_HPP
#define MOUSEDATA_HPP
#include <cstdlib>
#include <iostream>
#include "Manipulator.hpp"
#include "Vector.hpp"


/**
 * @ingroup frontend
 * @brief Shared data between all the mouse controls.
 * 
 * Sharing all the data allows all the controls to work together.
 * 
 * @see Mouse
 * @see MouseClickHelper
 * @see MouseDragHelper
 */
struct MouseData {
	int button, modifier, state, x, y;
	float z;
	unsigned int itemID, iteration, shapeID;
	Manipulator *manipulator;
	Vector lastPosition;
};


#endif
