/*
 * Drawable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Drawable.hpp"


/** Creates a new Drawable from an XML tag.
 * 
 * @param tag XML tag with @e size attribute.
 */
Drawable::Drawable(const Tag &tag) : Node(tag) {
	
	// Initialize attributes
	this->selected = false;
	this->visible = true;
	if (!tag.get("size", size, false))
		size = 1.0;
}


string Drawable::toString() const {
	
	stringstream stream;
	
	// Make string
	stream << Identifiable::toString();
	stream << " visible='" << (visible?'T':'F') << "'"
	       << " size='" << size << "'"
	       << " selected='" << (selected?'T':'F') << "'";
	return stream.str();
}

