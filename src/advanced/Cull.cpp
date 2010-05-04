/*
 * Cull.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cull.hpp"


/**
 * Creates a new %Cull object from a tag.
 * 
 * @param tag XML tag containing "faces" attribute.
 * @throws const_char* if value for "faces" attribute not supported.
 */
Cull::Cull(const Tag &tag) : Applicable(tag) {
	
	// Handle faces and enabled
	tag.get("faces", facesString, true);
	enabled = true;
	if (facesString == "front")
		faces = GL_FRONT;
	else if (facesString == "back")
		faces = GL_BACK;
	else if (facesString == "both")
		faces = GL_FRONT_AND_BACK;
	else if (facesString == "none")
		enabled = false;
	else {
		ostringstream msg;
		msg << "[Cull] Value '" << facesString 
		    << "' for 'faces' attributes not supported.";
		throw msg.str().c_str();
	}
}


/**
 * Enables culling.
 */
void Cull::apply() {
	
	if (enabled) {
		glEnable(GL_CULL_FACE);
		glCullFace(faces);
	} else {
		glDisable(GL_CULL_FACE);
	}
}


/**
 * Restores backface culling.
 */
void Cull::remove() {
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


/**
 * Forms a string from the object's attributes.
 */
string Cull::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " faces='" << facesString << "'";
	return stream.str();
}

