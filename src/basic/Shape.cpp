/*
 * Shape.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"


/** Creates a shape from an XML tag.
 * 
 * @param tag XML tag with attributes for Drawable.
 * @param traits Structure of shape parameters.
 */
Shape::Shape(const Tag &tag, ShapeTraits traits) : Drawable(tag) {
	
	// Copy
	this->count = traits.count;
	this->mode = traits.mode;
	this->usage = traits.usage;
	tag.get("name", name, false, false);
	
	// Store vertex attributes
	list<string>::iterator it;
	int i=0;
	for (it=traits.attributes.begin(); it!=traits.attributes.end(); ++it) {
		VertexAttribute va;
		va.name = *it;
		va.number = i;
		this->attributes.push_back(va);
		++i;
	}
}


/** Finds a program to bind the shape's vertex attributes to.
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


/** Renders the shape. */
void Shape::draw() const {
	
	list<VertexAttribute>::const_iterator it;
	
	// Enable buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	// Enable attributes
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		glEnableVertexAttribArray(it->location);
		glVertexAttribPointer(it->location,
		                      3,
		                      GL_FLOAT,
		                      false,
		                      0,
		                      (void*)offset(it->number));
	}
	
	// Draw
	glDrawArrays(mode, 0, count);
	
	// Disable attributes
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		glDisableVertexAttribArray(it->location);
	}
	
	// Disable buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/** Loads the vertex data into the vertex buffer so it's ready to render. */
void Shape::finalize() {
	
	// Initialize the buffer
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, offset(attributes.size()), NULL, usage);
	
	// Get locations of attributes in program
	list<VertexAttribute>::iterator it;
	for (it=attributes.begin(); it!=attributes.end(); ) {
		it->location = program->getAttributeLocation(it->name);
		if (it->location == -1)
			it = attributes.erase(it);
		else
			++it;
	}
	
	// Initialize attributes
	initAttributes();
}


string Shape::toString() const {
	
	ostringstream stream;
	
	stream << Drawable::toString();
	if (!name.empty()) {
		stream << " name='" << name << "'";
	}
	return stream.str();
}

