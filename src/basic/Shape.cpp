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
 * @throws NodeException if <i>style</i> not supported.
 */
Shape::Shape(const Tag &tag) : Drawable(tag) {
	
	string style;
	
	// Style
	if (tag.get("style", style, false)) {
		if (style == "3d") {
			this->style = GL_TEXTURE_3D;
		} else if (style == "2d") {
			this->style = GL_TEXTURE_2D;
		} else {
			NodeException e(tag);
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
 * @throws NodeException if a program cannot be found.
 */
void Shape::associate() {
	
	// Find program
	program = Program::find(parent);
	if (program == NULL) {
		NodeException e(tag);
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
		cerr << tag.getFilename() << ":" << tag.getLine() << ": ";
		cerr << "[Shape] Could not find attribute location for '"
		     << POINT_NAME << "'." << endl;
	}
}


/**
 * Forms a string from the object's attributes.
 */
string Shape::toString() const {
	
	ostringstream stream;
	
	// Make stream
	stream << Node::toString();
	stream << " " << Drawable::toString();
	stream << " style='" << (GL_TEXTURE_2D?"2D":"3D") << "'";
	return stream.str();
}

