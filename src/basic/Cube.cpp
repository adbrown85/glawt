/*
 * Cube.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cube.hpp"


/** Initializes the coordinates in the vertex buffer. */
void Cube::updateBufferCoords() {
	
	GLfloat coords[24][3];
	
	// Fill buffer with coords array
	toArray(coords, Vector(0.0,0.0,1.0), Vector(1.0,1.0,0.0));
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(2), sizeof(coords), coords);
}

