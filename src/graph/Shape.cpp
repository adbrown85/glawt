/*
 * Shape.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"



/**
 * Creates a shape.
 * 
 * @param size
 *     Size of the shape.
 */
Shape::Shape(float size) : Selectable(size) {
	
	// Initialize
	className = "Shape";
	style = GL_TEXTURE_2D;
}



/**
 * Creates a shape from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Shape::Shape(const Tag &tag) : Selectable(tag) {
	
	string message, style;
	
	// Initialize
	className = "Shape";
	
	// Style
	if (tag.get("style", style, false)) {
		if (style.compare("3d") == 0)
			this->style = GL_TEXTURE_3D;
		else if (style.compare("2d") == 0)
			this->style = GL_TEXTURE_2D;
		else {
			message = "[Gander,Shape] Style '";
			message += style + "' not supported.";
			throw message.c_str();
		}
	}
	else
		this->style = GL_TEXTURE_3D;
}



/**
 * Computes the shape's depth using the matrix.
 */
void Shape::computeDepth(Matrix &matrix) {
	
	Vector pos(0,0,0,1);
	
	// Multiply position by matrix
	pos = matrix * pos;
	depth = pos.z;
}



/**
 * Forms a string from the object's attributes.
 */
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

