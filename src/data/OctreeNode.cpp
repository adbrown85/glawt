/*
 * OctreeNode.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "OctreeNode.hpp"


OctreeNode::OctreeNode() {
	
	this->empty = false;
	for (int i=0; i<8; ++i) {
		children[i] = NULL;
	}
}


string OctreeNode::toString() {
	
	stringstream stream;
	
	// Format attributes
	stream << boolalpha;
	stream << "empty=" << empty;
	return stream.str();
}

