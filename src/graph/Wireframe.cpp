/*
 * Wireframe.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Wireframe.hpp"


Wireframe::Wireframe(const Tag &tag) {
	
	className = "Wireframe";
}


void Wireframe::apply() {
	
	glPushAttrib(GL_POLYGON_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_LINE);
}


void Wireframe::remove() {
	
	glPopAttrib();
}

