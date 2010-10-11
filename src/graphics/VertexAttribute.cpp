/*
 * VertexAttribute.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "VertexAttribute.hpp"

/** Creates a new vertex attribute. */
VertexAttribute::VertexAttribute() {
	
	this->name = "";
	this->components = 4;
	this->location = -1;
}

VertexAttribute::VertexAttribute(const string &name, GLuint components) {
	
	this->name = name;
	this->components = components;
	this->location = -1;
}

/** Destroys the vertex attribute. */
VertexAttribute::~VertexAttribute() {
	
}
