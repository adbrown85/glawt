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
 * @param inClipSpace
 *     Draw the square in clip space.
 */
Square::Square(float size,
               bool inClipSpace) : Shape() {
	
	// Class name
	className = "Square";
	this->size = size;
	this->inClipSpace = inClipSpace;
	
	// Initialize vertices
	if (!loaded) {
		initPoints();
		initIndices();
		loaded = true;
	}
}



/**
 * Draws the square.
 */
void Square::draw() const {
	
	// Enable arrays
	glVertexPointer(3, GL_FLOAT, 0, points);
	glTexCoordPointer(3, GL_FLOAT, 0, points);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	// Draw after loading identity matrices
	if (inClipSpace) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix(); {
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix(); {
				glLoadIdentity();
				glScalef(size, size, size);
				glTranslatef(-0.5, -0.5, -0.5);
				glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
			} glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		} glPopMatrix();
	}
	
	// Draw as normal
	else {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix(); {
			glScalef(size, size, size);
			glTranslatef(-0.5, -0.5, -0.5);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
		} glPopMatrix();
	}
	
	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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



string Square::toString() const {
	
	char inClipSpaceChar;
	stringstream stream;
	
	// Format
	inClipSpaceChar = inClipSpace ? 'T' : 'F';
	
	// Make string
	stream << Shape::toString();
	stream << " ics='" << inClipSpaceChar << "'";
	return stream.str();
}
