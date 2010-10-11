/*
 * VertexBufferObject.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "VertexBufferObject.hpp"
int VertexBufferObject::SIZEOF_VEC2 = sizeof(float) * 2;
int VertexBufferObject::SIZEOF_VEC3 = sizeof(float) * 3;
int VertexBufferObject::SIZEOF_VEC4 = sizeof(float) * 4;


/** Creates a new VBO. */
VertexBufferObject::VertexBufferObject() : BufferObject(GL_ARRAY_BUFFER) {
	
	this->interleaved = true;
	this->count = 0;
	this->size = 0;
	this->stride = 0;
	data = NULL;
	current = NULL;
	end = NULL;
}

/** Destroys the data held by the VBO. */
VertexBufferObject::~VertexBufferObject() {
	
	if (data != NULL) {
		delete[] data;
	}
}

/** Allocates space for the VBO.
 * 
 * @note Disables striding. 
 */
void VertexBufferObject::allocate(GLenum usage,
                                  GLuint count,
                                  list<VertexAttribute> &attribs) {
	
	list<VertexAttribute>::iterator it;
	GLuint position;
	
	// Reset
	this->count = count;
	stride = 0;
	positions.clear();
	
	// Compute size and positions
	position = 0;
	for (it=attribs.begin(); it!=attribs.end(); ++it) {
		positions[it->getName()] = position;
		position += sizeof(GLfloat) * it->getComponents();
	}
	size = position * count;
	
	// Recompute positions if not interleaved
	if (!isInterleaved()) {
		for (it=attribs.begin(); it!=attribs.end(); ++it) {
			positions[it->getName()] *= count;
		}
	}
	
	// Allocate local and GPU copy
	data = new GLubyte[size];
	current = data;
	end = data + size;
	BufferObject::allocate(usage, size);
}

/** Move to the next vertex of the same attribute after a put.
 * 
 * @throw Exception if not an interleaved vertex buffer object. 
 */
void VertexBufferObject::enableStriding() {
	
	if (!isInterleaved()) {
		Exception e;
		e << "[VertexBufferObject] Cannot use striding when not interleaved.";
		throw e;
	}
	
	if (!isAllocated()) {
		Exception e;
		e << "[VertexBufferObject] Cannot set striding before allocated.";
	}

	stride = size / count;
}

/** Move to the next vertex in the buffer after a put. */
void VertexBufferObject::disableStriding() {
	
	stride = 0;
}

/** Flushes the data to the video card. */
void VertexBufferObject::flush() {
	
	if (isAllocated()) {
		BufferObject::update(size, data, 0);
	} else {
		Exception e;
		e << "[VertexBufferObject] Cannot flush before being allocated.";
		throw Exception(e);
	}
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBufferObject::put(float x, float y) {
	
	if ((current + SIZEOF_VEC2) > end) {
		throw Exception("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	current += SIZEOF_VEC2 + stride;
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBufferObject::put(float x, float y, float z) {

	if ((current + SIZEOF_VEC3) > end) {
		throw Exception("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	current += SIZEOF_VEC3 + stride;
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBufferObject::put(float x, float y, float z, float w) {
	
	if ((current + SIZEOF_VEC4) > end) {
		throw Exception("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	((GLfloat*)current)[3] = w;
	current += SIZEOF_VEC4 + stride;
}

/** Returns the current position to the beginning of the buffer. */
void VertexBufferObject::rewind() {
	
	current = data;
}

/** Set whether all all attributes for a vertex will be kept together. */
void VertexBufferObject::setInterleaved(bool interleaved) {
	
	if (!isAllocated()) {
		this->interleaved = interleaved;
	} else {
		Exception e;
		e << "[VertexBufferObject] Cannot change interleave after allocated.";
		throw e;
	}
}

/** Moves to the start of an attribute. */
void VertexBufferObject::seek(const string &name) {
	
	map<string,GLuint>::iterator it;
	
	// Find position and add it to data
	it = positions.find(name);
	if (it != positions.end()) {
		current = data + it->second;
	} else {
		Exception e;
		e << "[VertexBufferObject] Attribute '" + name + "' not stored.";
		throw e;
	}
}
