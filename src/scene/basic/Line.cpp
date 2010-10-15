/*
 * Line.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Line.hpp"


Line::Line(const Tag &tag) : Shape(tag,getTraits()) {
	
	tag.get("from", from);
	tag.get("to", to);
}


ShapeTraits Line::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 2;
	traits.mode = GL_LINES;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.attributes.push_back("MCVertex");
	return traits;
}


void Line::updateBuffer() {
	
	updateBufferPoints();
}


void Line::updateBufferPoints() {
	
	GLfloat points[2][3] = {{from[0], from[1], from[2]},
	                        {to[0], to[1], to[2]}};
	
	setBufferData("MCVertex", points);
}

