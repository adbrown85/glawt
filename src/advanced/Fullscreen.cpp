/*
 * Fullscreen.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Fullscreen.hpp"
bool Fullscreen::loaded = false;
GLfloat Fullscreen::coordinates[4][3];
GLubyte Fullscreen::indices[4];
GLfloat Fullscreen::points[4][3];


/**
 * Creates a new %Fullscreen from an XML tag.
 * 
 * @param tag XML tag.
 */
Fullscreen::Fullscreen(const Tag &tag) : Drawable(tag) {
	
	// Initialize
	this->size = 2.0;
	if (!loaded) {
		initCoordinates();
		initIndices();
		initPoints();
		loaded = true;
	}
}


/**
 * Draws the %Fullscreen.
 */
void Fullscreen::draw() const {
	
	// Load identity matrices
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	// Draw
	glVertexPointer(3, GL_FLOAT, 0, points);
	glTexCoordPointer(3, GL_FLOAT, 0, coordinates);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	// Restore matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


/**
 * Initializes the static coordinates array of the class.
 */
void Fullscreen::initCoordinates() {
	
	GLfloat coordinates[4][3] = {{1.0, 1.0, 0.0},
	                             {0.0, 1.0, 0.0},
	                             {0.0, 0.0, 0.0},
	                             {1.0, 0.0, 0.0}};
	
	// Copy to class
	for (int i=0; i<4; ++i)
		for (int j=0; j<4; ++j)
			this->coordinates[i][j] = coordinates[i][j];
}


/**
 * Initializes the static indices array of the class.
 */
void Fullscreen::initIndices() {
	
	// Copy to class
	for (int i=0; i<4; i++)
		this->indices[i] = i;
}


/**
 * Initializes the static points array of the class.
 */
void Fullscreen::initPoints() {
	
	GLfloat points[4][3] = {{+1.0, +1.0, -1.0},
	                        {-1.0, +1.0, -1.0},
	                        {-1.0, -1.0, -1.0},
	                        {+1.0, -1.0, -1.0}};
	
	// Copy to class
	for (int i=0; i<4; i++)
		for (int j=0; j<3; j++)
			this->points[i][j] = points[i][j];
}

