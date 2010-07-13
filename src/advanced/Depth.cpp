/*
 * Depth.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Depth.hpp"


/** Initializes @e mode and @e clear. 
 * 
 * @throws NodeException if value for @e mode unrecognized.
 */
Depth::Depth(const Tag &tag) : Node(tag) {
	
	string mode;
	
	tag.get("mode", mode, true, true);
	if (mode == "never") {
		this->mode = GL_NEVER;
	} else if (mode == "less") {
		this->mode = GL_LESS;
	} else if (mode == "equal") {
		this->mode = GL_EQUAL;
	} else if (mode == "lequal") {
		this->mode = GL_LEQUAL;
	} else if (mode == "greater") {
		this->mode = GL_GREATER;
	} else if (mode == "notequal") {
		this->mode = GL_NOTEQUAL;
	} else if (mode == "gequal") {
		this->mode = GL_GEQUAL;
	} else if (mode == "always") {
		this->mode = GL_ALWAYS;
	} else {
		NodeException e(tag);
		e << "[Depth] Value '" << mode << "' for mode unrecognized.";
		throw e;
	}
}


/** Changes the depth function to @e mode and clears the depth buffer. */
void Depth::apply() {
	
	glDepthFunc(mode);
}


/** Restores the default depth function. */
void Depth::remove() {
	
	glDepthFunc(GL_LESS);
}


/** Adds @e mode to the node description. */
string Depth::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " mode='" << Text::toLower(tag["mode"]) << "'";
	return stream.str();
}

