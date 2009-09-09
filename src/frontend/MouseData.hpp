/*
 * MouseData.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef MOUSEDATA_HPP
#define MOUSEDATA_HPP
#include <cstdlib>
#include <iostream>
#include "Manipulator.hpp"
#include "Vector.hpp"



struct MouseData {
	
	int button, modifier, state, x, y;
	float z;
	unsigned int itemID, iteration, shapeID;
	Manipulator *manipulator;
	Vector lastPosition;
};


#endif
