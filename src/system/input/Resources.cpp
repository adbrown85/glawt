/*
 * Resources.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Resources.hpp"


string Resources::get(const string &filename) {
	
	ostringstream stream;
	
	stream << GANDER_DATA_DIR << '/' << filename;
	return stream.str();
}



string Resources::getIconFilename() {
	
	return get("ui/gander.png");
}


string Resources::getSquareIconFilename() {
	
	return get("ui/gander-square.png");
}

