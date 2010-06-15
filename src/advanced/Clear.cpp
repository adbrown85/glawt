/*
 * Clear.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Clear.hpp"


/** Initialize the three color components. */
Clear::Clear(const Tag &tag) : Node(tag) {
	
	// Initialize
	tag.get("r", r, false);
	tag.get("g", g, false);
	tag.get("b", b, false);
}


/** Clears the current framebuffer with the node's color. */
void Clear::apply() {
	
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/** @return String comprised of the object's attributes. */
string Clear::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " r='" << r << "'"
	       << " g='" << g << "'"
	       << " b='" << b << "'";
	return stream.str();
}

