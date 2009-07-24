/*
 * Shape.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"



/**
 * Creates a shape with a 2D texture.
 */
Shape::Shape() {
	
	// Initialize
	className = "Shape";
	style = GL_TEXTURE_2D;
}



ostream& operator<<(ostream& stream,
                    const Shape& shape) {
	
	string style;
	
	// Format and print
	style = shape.style==GL_TEXTURE_2D ? "2D" : "3D";
	stream << static_cast<Node>(shape) << " "
	       << static_cast<Selectable>(shape) << ", "
	       << "sty=" << style;
	return stream;
}
