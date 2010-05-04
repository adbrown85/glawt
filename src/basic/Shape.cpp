/*
 * Shape.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"


/**
 * Creates a shape from an XML tag.
 * 
 * @param tag XML tag with "size" attribute.
 */
Shape::Shape(const Tag &tag) : Selectable(tag) {
	
	string style;
	
	// Style
	if (tag.get("style", style, false)) {
		if (style == "3d") {
			this->style = GL_TEXTURE_3D;
		} else if (style == "2d") {
			this->style = GL_TEXTURE_2D;
		} else {
			Exception e;
			e << tag.getFilename() << ":" << tag.getLine() << ": ";
			e << "[Shape] Style '" << style << "' not supported.";
			throw e;
		}
	} else {
		this->style = GL_TEXTURE_3D;
	}
}


/**
 * Finds a program to bind the shape's vertex attributes to.
 * 
 * @throws const_char* if a program cannot be found.
 */
void Shape::associate() {
	
	// Find program
	program = Program::find(parent);
	if (program == NULL) {
		Exception e;
		e << tag.getFilename() << ":" << tag.getLine() << ": ";
		e << "[Shape] No shader program found to bind attributes to.";
		throw e;
	}
}


/**
 * @warning if a location for the shape's points are not found.
 */
void Shape::finalize() {
	
	GLint location;
	
	// Check point location in program
	location = program->getAttributeLocation(POINT_NAME);
	if (location == -1) {
		cerr << "[Shape] Could not find attribute location for '"
		     << POINT_NAME << "'" << endl;
	}
}


/**
 * Forms a string from the object's attributes.
 */
string Shape::toString() const {
	
	string styleStr;
	ostringstream stream;
	
	// Format
	styleStr = style==GL_TEXTURE_2D ? "2D" : "3D";
	
	// Make stream
	stream << Node::toString();
	stream << " " << Selectable::toString();
	stream << " sty='" << styleStr << "'";
	return stream.str();
}

