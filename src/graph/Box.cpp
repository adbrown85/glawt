/*
 * Box.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Box.hpp"
bool Box::loaded = false;
GLfloat Box::coords[24][3], Box::points[24][3], Box::normals[24][3];
GLubyte Box::indices[24], Box::map[8][3];



/**
 * Creates a new box.
 * 
 * @param size
 *     Length of the box's sides.
 */
Box::Box(float size) : Shape(size) {
	
	// Initialize
	init();
}



/**
 * Creates a new box from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Box::Box(const Tag &tag) : Shape(tag) {
	
	// Initialize
	init();
}



/**
 * Draws the %Box.
 */
void Box::draw() const {
	
	int numberOfActiveUnits;
	
	// Enable vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, points);
	
	// Enable normal arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	
	// Enable texture coordinate arrays
	numberOfActiveUnits = Texture::getNumberOfActiveUnits();
	if (numberOfActiveUnits == 0)
		numberOfActiveUnits = 1;
	for (int i=0; i<numberOfActiveUnits; ++i) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (style == GL_TEXTURE_2D)
			glTexCoordPointer(3, GL_FLOAT, 0, coords);
		else
			glTexCoordPointer(3, GL_FLOAT, 0, points);
	}
	
	// Draw vertices
	glPushMatrix(); {
		glScalef(size, size, size);
		glTranslatef(-0.5, -0.5, -0.5);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	} glPopMatrix();
	
	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	for (int i=0; i<numberOfActiveUnits; ++i) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}



/**
 * Initializes the %Box's attributes.
 */
void Box::init() {
	
	// Class name
	className = "Box";
	
	// Initialize vertices of class
	if (!loaded) {
		initMap();
		initPoints();
		initCoords();
		initNormals();
		initIndices();
		loaded = true;
	}
}



/**
 * Initializes the %Box class's static coordinates array.
 * 
 * Note two-dimensional coordinates for each face are always created here so 
 * that if an image is specified as a texture it will appear correctly on each 
 * face.  When a box is drawn however, if the box's style is GL_TEXTURE_3D the 
 * box's points will be used instead.
 */
void Box::initCoords() {
	
	GLfloat coords[4][3] = {{0.0, 0.0, 0.0},
	                        {0.0, 1.0, 0.0},
	                        {1.0, 0.0, 0.0},
	                        {1.0, 1.0, 0.0}};
	GLubyte map[4][6] = {{ 1,  5,  9, 13, 17, 21},
	                     { 2,  6, 10, 14, 18, 22},
	                     { 0,  4,  8, 12, 16, 20},
	                     { 3,  7, 11, 15, 19, 23}};
	int m;
	
	// Copy to class
	for (int i=0; i<4; i++) {
		for (int v=0; v<6; v++) {
			m = map[i][v];
			for (int c=0; c<3; c++)
				this->coords[m][c] = coords[i][c];
		}
	}
}



/**
 * Initializes the indices used to draw the box's faces.
 */
void Box::initIndices() {
	
	// Copy to class
	for (int i=0; i<24; ++i)
		this->indices[i] = i;
}



/**
 * Initializes the %Box class's static map that determines which points used in 
 * glDrawElements correspond to the standard eight points of a cube.
 */
void Box::initMap() {
	
	GLubyte map[8][3] = {{1,  8, 18},
	                     {0, 13, 19},
	                     {2, 11, 23},
	                     {3, 14, 22},
	                     {4,  9, 17},
	                     {5, 12, 16},
	                     {7, 10, 20},
	                     {6, 15, 21}};
	
	// Copy to class
	for (int i=0; i<8; i++)
		for (int j=0; j<3; j++)
			this->map[i][j] = map[i][j];
}



void Box::initNormals() {
	
	GLfloat normals[6][3] = {{ 0.0,  0.0, +1.0},     // front
	                         { 0.0,  0.0, -1.0},     // back
	                         {-1.0,  0.0,  0.0},     // left
	                         {+1.0,  0.0,  0.0},     // right
	                         { 0.0, +1.0,  0.0},     // top
	                         { 0.0, -1.0,  0.0}};    // bottom
	int m;
	
	// Copy to class
	for (int f=0; f<6; ++f) {
		for (int v=0; v<4; ++v) {
			for (int c=0; c<3; c++)
				this->normals[f*4+v][c] = normals[f][c];
		}
	}
}



/**
 * Initializes the %Box class's static points array.
 */
void Box::initPoints() {
	
	GLfloat points[8][3] = {{0.0, 1.0, 1.0},
	                        {1.0, 1.0, 1.0},
	                        {0.0, 0.0, 1.0},
	                        {1.0, 0.0, 1.0},
	                        {0.0, 1.0, 0.0},
	                        {1.0, 1.0, 0.0},
	                        {0.0, 0.0, 0.0},
	                        {1.0, 0.0, 0.0}};
	int m;
	
	// Copy to class
	for (int i=0; i<8; i++) {
		for (int v=0; v<3; v++) {
			m = map[i][v];
			for (int c=0; c<3; c++)
				this->points[m][c] = points[i][c];
		}
	}
}

