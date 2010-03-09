/*
 * Square.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Square.hpp"
bool Square::loaded = false;
GLfloat Square::points[4][3];
GLubyte Square::indices[4];


/**
 * Creates a new square.
 * 
 * @param size
 *     Length of the square's sides.
 */
Square::Square(float size) : 
               Shape(size) {
	
	// Initialize
	Square::init();
}


/**
 * Creates a new %Square from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Square::Square(const Tag &tag) :
               Shape(tag) {
	
	// Initialize
	Square::init();
}


/**
 * Draws the square.
 */
void Square::draw() const {
	
	int numberOfActiveUnits;
	
	// Enable vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, points);
	
	// Enable texture coordinate arrays
	numberOfActiveUnits = Texture::getNumberOfActiveUnits();
	if (numberOfActiveUnits == 0)
		numberOfActiveUnits = 1;
	for (int i=0; i<numberOfActiveUnits; ++i) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT, 0, points);
	}
	
	// Draw
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); {
		glScalef(size, size, size);
		glTranslatef(-0.5, -0.5, -0.5);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	} glPopMatrix();
	
	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	for (int i=0; i<numberOfActiveUnits; ++i) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}


/**
 * Initializes attributes common to all constructors.
 */
void Square::init() {
	
	// Name
	className = "Square";
	
	// Initialize vertices
	if (!loaded) {
		initPoints();
		initIndices();
		loaded = true;
	}
}


/**
 * Initializes the indices used to draw the square's faces.
 */
void Square::initIndices() {
	
	// Copy to class
	for (int i=0; i<4; i++)
		this->indices[i] = i;
}


/**
 * Initializes the static points array of the class.
 */
void Square::initPoints() {
	
	GLfloat points[4][3] = {{1.0, 1.0, 0.0},
	                        {0.0, 1.0, 0.0},
	                        {0.0, 0.0, 0.0},
	                        {1.0, 0.0, 0.0}};
	
	// Copy to class
	for (int i=0; i<4; i++)
		for (int j=0; j<3; j++)
			this->points[i][j] = points[i][j];
}

