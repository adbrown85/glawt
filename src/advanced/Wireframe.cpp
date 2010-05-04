/*
 * Wireframe.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Wireframe.hpp"


Wireframe::Wireframe(const Tag &tag) : Applicable(tag) {
	
}


void Wireframe::apply() {
	
	glPushAttrib(GL_POLYGON_BIT);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void Wireframe::remove() {
	
	glEnable(GL_CULL_FACE);
	glPopAttrib();
}

