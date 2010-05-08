/*
 * Cube.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cube.hpp"


/** Initializes the coordinates in the vertex buffer. */
void Cube::initCoords() {
	
	GLfloat C[8][3] = {{0.0, 0.0, 0.0},   // 0 bottom-left-front
	                   {1.0, 0.0, 0.0},   // 1 bottom-right-front
	                   {0.0, 1.0, 0.0},   // 2 top-left-front
	                   {1.0, 1.0, 0.0},   // 3 top-right-front
	                   {0.0, 0.0, 1.0},   // 4 bottom-left-back
	                   {1.0, 0.0, 1.0},   // 5 bottom-right-back
	                   {0.0, 1.0, 1.0},   // 6 top-left-back
	                   {1.0, 1.0, 1.0}};  // 7 top-right-back
	GLfloat coords[24][3];
	
	// Copy each point to each index it corresponds to
	int index;
	for (int c=0; c<8; ++c) {
		for (int j=0; j<3; ++j) {
			index = indices[c][j];
			for (int k=0; k<3; ++k) {
				coords[index][k] = C[c][k];
			}
		}
	}
	
	// Send to buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset(2), sizeof(coords), coords);
}

