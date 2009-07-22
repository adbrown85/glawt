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



class MouseData {
	
	
	public :
		
		int button, modifier, state, x, y;
		unsigned int itemID, iteration;
		Manipulator *manipulator;
		Vector lastPosition;
};


#endif
