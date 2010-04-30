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
Shape::Shape(const string &className,
             const Tag &tag) : Selectable(className, tag) {
	
	string style;
	
	// Style
	if (tag.get("style", style, false)) {
		if (style == "3d") {
			this->style = GL_TEXTURE_3D;
		} else if (style == "2d") {
			this->style = GL_TEXTURE_2D;
		} else {
			ostringstream msg;
			msg << "[Shape] Style '" << style << "' not supported.";
			throw msg.str().c_str();
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
		throw "[Shape] No shader program found to bind attributes to.";
	}
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
 * Finds vertex attribute locations in the current shader program.
 * 
 * @throws const_char* if a location for the vertex points cannot be found.
 * @note Does not throw an error in case shaders do not use an attribute.
 */
void Shape::finalize() {
	
	// Find locations in program
	pointsLoc = glGetAttribLocation(program->getHandle(), "MCVertex");
	normalsLoc = glGetAttribLocation(program->getHandle(), "MCNormal");
	coordsLoc = glGetAttribLocation(program->getHandle(), "TexCoord0");
	
	// Check
	if (pointsLoc == -1)
		throw "[Shape] Could not find location for 'MCVertex'";
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

