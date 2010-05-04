/*
 * Drawable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Drawable.hpp"


/**
 * Creates a new Drawable from an XML tag.
 * 
 * @param tag XML tag with "size" attribute.
 */
Drawable::Drawable(const Tag &tag) : Node(tag) {
	
	// Initialize attributes
	this->visible = true;
	if (!tag.get("size", size, false))
		size = 1.0;
}


string Drawable::toString() const {
	
	char visibleChar;
	stringstream stream;
	
	// Format
	visibleChar = visible ? 'T' : 'F';
	
	// Make string
	stream << Identifiable::toString();
	stream << " vis='" << visibleChar << "'"
	       << " siz='" << size << "'";
	return stream.str();
}

