/*
 * Shape.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"
map<string,GLuint> Shape::buffers;


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
	
	// Enable buffer and attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
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
	
	// Disable buffer and attributes
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		glDisableVertexAttribArray(it->location);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/** Loads the vertex data into the vertex buffer so it's ready to render. */
void Shape::finalize() {
	
	list<VertexAttribute>::iterator it;
	
	// Initialize buffer for dynamic shapes or first run of static shapes
	if (usage == GL_DYNAMIC_DRAW || !isBufferStored(getClassName())) {
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, offset(attributes.size()), NULL, usage);
		initAttributes();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		if (usage == GL_STATIC_DRAW) {
			buffers[getClassName()] = buffer;
		}
	}
	
	// Set buffer for static shapes
	if (usage == GL_STATIC_DRAW) {
		buffer = buffers.find(getClassName())->second;
	}
	
	// Get locations of attributes in program
	for (it=attributes.begin(); it!=attributes.end(); ) {
		it->location = program->getAttributeLocation(it->name);
		if (it->location == -1)
			it = attributes.erase(it);
		else
			++it;
	}
}


/** Checks if a buffer already exists for a concrete shape. */
bool Shape::isBufferStored(string className) {
	
	map<string,GLuint>::iterator it;
	
	it = buffers.find(className);
	return it != buffers.end();
}


string Shape::toString() const {
	
	ostringstream stream;
	
	stream << Drawable::toString();
	stream << " buffer='" << buffer << "'";
	if (!name.empty()) {
		stream << " name='" << name << "'";
	}
	return stream.str();
}

