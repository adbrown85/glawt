/*
 * Clear.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Clear.hpp"


/** Initialize the three color components. */
Clear::Clear(const Tag &tag) : Node(tag) {
	
	// Color
	hasColor = true;
	if (!tag.get("color", color, false)) {
		hasColor = false;
		color = Vector(0.0, 0.0, 0.0, 0.0);
	}
	
	// Depth
	hasDepth = true;
	if (!tag.get("depth", depth, false)) {
		hasDepth = false;
		depth = 1.0;
	}
	
	// Mask
	if (hasColor && !hasDepth) {
		mask = GL_COLOR_BUFFER_BIT;
	} else if (hasDepth && !hasColor) {
		mask = GL_DEPTH_BUFFER_BIT;
	} else {
		mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	}
}


/** Clears the current framebuffer with the node's color. */
void Clear::apply() {
	
	if (hasColor)
		glClearColor(color.x, color.y, color.z, color.w);
	if (hasDepth)
		glClearDepth(depth);
	glClear(mask);
}


/** @return String comprised of the object's attributes. */
string Clear::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	if (mask & GL_COLOR_BUFFER_BIT) {
		stream << " color='" << color.x << " "
		                     << color.y << " "
		                     << color.z << " "
		                     << color.w << "'";
	}
	if (mask & GL_DEPTH_BUFFER_BIT) {
		stream << " depth='" << depth << "'";
	}
	return stream.str();
}

