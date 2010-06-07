/*
 * SimpleDrawable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "SimpleDrawable.hpp"


/** Initializes the selected, visible, and selectable attributes. */
SimpleDrawable::SimpleDrawable(const Tag &tag) : SimpleTransformable(tag) {
	
	// Initialize attributes
	this->selected = false;
	this->visible = true;
	if (!tag.get("selectable", selectable, false))
		selectable = true;
}


/** @return String comprised of the object's attributes. */
string SimpleDrawable::toString() const {
	
	ostringstream stream;
	
	// Make string
	stream << Node::toString();
	stream << " " << Identifiable::toString();
	stream << " visible='" << (visible?'T':'F') << "'"
	       << " selected='" << (selected?'T':'F') << "'"
	       << " selectable='" << (selectable?'T':'F') << "'";
	return stream.str();
}

