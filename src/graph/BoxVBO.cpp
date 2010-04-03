/*
 * BoxVBO.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BoxVBO.hpp"
bool BoxVBO::loaded = false;
GLfloat BoxVBO::points[24][3];
GLubyte BoxVBO::map[8][3];
GLuint BoxVBO::indicesBuffer=0, BoxVBO::pointsBuffer=0;
GLushort BoxVBO::indices[24];


BoxVBO::BoxVBO(float size) :
               Shape(size) {
	
	init();
}


BoxVBO::BoxVBO(const Tag &tag) :
               Shape(tag) {
	
	init();
}


void BoxVBO::draw() const {
	
	// Enable
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glEnableVertexAttribArray(0);
	
	// Draw
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glPushMatrix(); {
		glScalef(size, size, size);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
	} glPopMatrix();
	
	// Disable
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void BoxVBO::init() {
	
	// Class name
	className = "BoxVBO";
	
	// Attributes
	if (!loaded) {
		initIndices();
		initMap();
		initPoints();
		initBuffers();
		loaded = true;
	}
}


void BoxVBO::initBuffers() {
	
	// Points
	glGenBuffers(1, &pointsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	// Indices
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


/**
 * Initializes the indices used to draw the box's faces.
 */
void BoxVBO::initIndices() {
	
	// Copy to class
	for (int i=0; i<24; ++i)
		this->indices[i] = i;
}


/**
 * Initializes the %Box class's static map that determines which points used in 
 * glDrawElements correspond to the standard eight points of a cube.
 */
void BoxVBO::initMap() {
	
	GLubyte map[8][3] = {{1,  8, 18},
	                     {0, 13, 19},
	                     {2, 11, 23},
	                     {3, 14, 22},
	                     {4,  9, 17},
	                     {5, 12, 16},
	                     {7, 10, 20},
	                     {6, 15, 21}};
	
	// Copy to class
	for (int i=0; i<8; ++i)
		for (int j=0; j<3; ++j)
			this->map[i][j] = map[i][j];
}


/**
 * Initializes the %BoxVBO class's static points array.
 */
void BoxVBO::initPoints() {
	
	GLfloat points[8][3] = {{-0.5, +0.5, +0.5},
	                        {+0.5, +0.5, +0.5},
	                        {-0.5, -0.5, +0.5},
	                        {+0.5, -0.5, +0.5},
	                        {-0.5, +0.5, -0.5},
	                        {+0.5, +0.5, -0.5},
	                        {-0.5, -0.5, -0.5},
	                        {+0.5, -0.5, -0.5}};
	int m;
	
	// Copy to class
	for (int i=0; i<8; ++i) {
		for (int v=0; v<3; ++v) {
			m = map[i][v];
			for (int c=0; c<3; ++c)
				this->points[m][c] = points[i][c];
		}
	}
}

