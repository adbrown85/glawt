/*
 * Resources.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Resources.hpp"



string Resources::getIconFilename() {
	
	ostringstream stream;
	
	stream << GANDER_DATA_DIR << '/' << "ui/gander.png";
	return stream.str();
}


string Resources::getSquareIconFilename() {
	
	ostringstream stream;
	
	stream << GANDER_DATA_DIR << '/' << "ui/gander-square.png";
	return stream.str();
}

