/*
 * NodeException.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeException.hpp"


NodeException::NodeException(const Tag &tag) {
	
	(*this) << tag.getLocation();
}

