/*
 * Shape.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"



/**
 * Creates a shape with a 2D texture.
 * 
 * @param size
 *     Size of the shape.
 */
Shape::Shape(float size) : Selectable(size) {
	
	// Initialize
	className = "Shape";
	style = GL_TEXTURE_2D;
}



string Shape::toString() const {
	
	string styleStr;
	stringstream stream;
	
	// Format
	styleStr = style==GL_TEXTURE_2D ? "2D" : "3D";
	
	// Make stream
	stream << Node::toString();
	stream << " " << Selectable::toString();
	stream << " sty='" << styleStr << "'";
	return stream.str();
}
