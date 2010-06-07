/*
 * Cull.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cull.hpp"


/** Creates a new %Cull object from a tag.
 * 
 * @param tag XML tag containing "faces" attribute.
 * @throws Exception if @e faces attribute not supported.
 * @throws NodeException if value for @e faces attribute not supported.
 */
Cull::Cull(const Tag &tag) : Node(tag) {
	
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
		NodeException e(tag);
		e << "[Cull] Value '" << facesString << "' for 'faces' not supported.";
		throw e;
	}
}


/** Enables culling. */
void Cull::apply() {
	
	if (enabled) {
		glEnable(GL_CULL_FACE);
		glCullFace(faces);
	} else {
		glDisable(GL_CULL_FACE);
	}
}


/** Restores backface culling. */
void Cull::remove() {
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


/** Forms a string from the object's attributes. */
string Cull::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " faces='" << facesString << "'";
	return stream.str();
}

