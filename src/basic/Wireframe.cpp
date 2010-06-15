/*
 * Wireframe.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Wireframe.hpp"


Wireframe::Wireframe(const Tag &tag) : Node(tag) {
	
	if (!tag.get("faces", faces, false)) {
		faces = "both";
	}
	if (faces == "both") {
		mode = GL_FRONT_AND_BACK;
	} else if (faces == "front") {
		mode = GL_FRONT;
	} else if (faces == "back") {
		mode = GL_BACK;
	}
}


void Wireframe::apply() {
	
	glPushAttrib(GL_POLYGON_BIT);
	if (mode == GL_FRONT_AND_BACK) {
		glDisable(GL_CULL_FACE);
	} else {
		glEnable(GL_CULL_FACE);
		if (mode == GL_FRONT) {
			glCullFace(GL_BACK);
		} else {
			glCullFace(GL_FRONT);
		}
	}
	glPolygonMode(mode, GL_LINE);
}


void Wireframe::remove() {
	
	glPopAttrib();
}


string Wireframe::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " faces='" << faces << "'";
	return stream.str();
}

