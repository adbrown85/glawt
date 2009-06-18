/*
 * Manipulator.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Manipulator.hpp"
int Manipulator::count=0;



void Manipulator::copy(const Item &item) {
	
	// Copy position and size
	position = item.getPosition();
	size = item.getSize();
}
