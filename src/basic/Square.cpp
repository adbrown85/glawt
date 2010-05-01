/*
 * Square.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Square.hpp"
bool Square::loaded = false;
GLfloat Square::coords[4][3], Square::normals[4][3], Square::points[4][3];
GLint Square::coordsOffset, Square::normalsOffset, Square::pointsOffset;
GLuint Square::dataBuffer, Square::indicesBuffer;
GLushort Square::indices[4];


/**
 * Creates a new %Square from an XML tag.
 * 
 * @param tag XML tag with "size" attribute.
 */
Square::Square(const Tag &tag) : Shape(tag) {
	
	// Basics
	style = GL_TEXTURE_2D;
	
	// Initialize vertices
	if (!loaded) {
		initPoints();
		initCoords();
		initIndices();
		initNormals();
		initBuffers();
		loaded = true;
	}
}


/**
 * Draws the square.
 */
void Square::draw() const {
	
	// Enable buffers and arrays
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glEnableVertexAttribArray(pointsLoc);
	glEnableVertexAttribArray(normalsLoc);
	glEnableVertexAttribArray(coordsLoc);
	
	// Draw
	glVertexAttribPointer(pointsLoc, 3, GL_FLOAT, false, 0, (void*)pointsOffset);
	glVertexAttribPointer(normalsLoc, 3, GL_FLOAT, false, 0, (void*)normalsOffset);
	glVertexAttribPointer(coordsLoc, 3, GL_FLOAT, false, 0, (void*)coordsOffset);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, 0);
	
	// Disable buffers and arrays
	glDisableVertexAttribArray(pointsLoc);
	glDisableVertexAttribArray(normalsLoc);
	glDisableVertexAttribArray(coordsLoc);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Square::initBuffers() {
	
	int dataSize;
	
	// Calculate sizes and offsets
	dataSize = sizeof(points) + sizeof(normals) + sizeof(coords);
	pointsOffset = 0;
	normalsOffset = pointsOffset + sizeof(points);
	coordsOffset = normalsOffset + sizeof(normals);
	
	// Points and coordinates
	glGenBuffers(1, &dataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, pointsOffset, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, normalsOffset, sizeof(normals), normals);
	glBufferSubData(GL_ARRAY_BUFFER, coordsOffset, sizeof(coords), coords);
	
	// Indices
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


void Square::initCoords() {
	
	GLfloat coords[4][3] = {{1.0, 1.0, 0.0},
	                        {0.0, 1.0, 0.0},
	                        {0.0, 0.0, 0.0},
	                        {1.0, 0.0, 0.0}};
	
	// Copy to class
	for (int i=0; i<4; i++)
		for (int j=0; j<3; j++)
			this->coords[i][j] = coords[i][j];
}


/**
 * Initializes the indices used to draw the square's faces.
 */
void Square::initIndices() {
	
	// Copy to class
	for (int i=0; i<4; i++)
		this->indices[i] = i;
}


void Square::initNormals() {
	
	for (int i=0; i<4; ++i) {
		this->normals[i][0] = 0.0;
		this->normals[i][1] = 0.0;
		this->normals[i][2] = 1.0;
	}
}


/**
 * Initializes the static points array of the class.
 */
void Square::initPoints() {
	
	GLfloat points[4][3] = {{+0.5, +0.5, 0.0},
	                        {-0.5, +0.5, 0.0},
	                        {-0.5, -0.5, 0.0},
	                        {+0.5, -0.5, 0.0}};
	
	// Copy to class
	for (int i=0; i<4; i++)
		for (int j=0; j<3; j++)
			this->points[i][j] = points[i][j];
}

