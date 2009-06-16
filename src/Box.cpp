/*
 * Box.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Box.hpp"
bool Box::loaded = false;
GLfloat Box::coordinates[24][3], Box::points[24][3];
GLubyte Box::indices[24], Box::map[8][3];



/**
 * Creates a new box.  Sets the size to id.
 */
Box::Box() {
	
	// Initialize
	initialize();
	this->size = static_cast<float>(id);
}



/**
 * Creates a new box.
 * 
 * @param size
 *     Length of the box's sides.
 */
Box::Box(float size) {
	
	// Initialize
	initialize();
	this->size = size;
}



/**
 * Draws the box.
 */
void Box::draw() const {
	
	// Enable arrays
	glVertexPointer(3, GL_FLOAT, 0, points);
	if (style == GL_TEXTURE_2D)
		glTexCoordPointer(3, GL_FLOAT, 0, coordinates);
	else
		glTexCoordPointer(3, GL_FLOAT, 0, points);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	// Draw vertices
	glPushMatrix(); {
		glTranslatef(position.x, position.y, position.z);
		glScalef(size, size, size);
		glTranslatef(-0.5, -0.5, -0.5);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	} glPopMatrix();
	
	// Disable arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}



/**
 * Initializes the Box.
 */
void Box::initialize() {
	
	// Initialize vertices of class
	if (!loaded) {
		initializeMap();
		initializePoints();
		initializeCoordinates();
		initializeIndices();
		loaded = true;
	}
	
	// Set default colors
	initializeColors();
	
	// Store type
	type = "Box";
}



/**
 * Initializes an object's color array.
 */
void Box::initializeCoordinates() {
	
	GLfloat coordinates[4][3] = {{0.0, 0.0, 0.0},
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
				this->coordinates[m][c] = coordinates[i][c];
		}
	}
}



/**
 * Initializes an object's color array.
 */
void Box::initializeColors() {
	
	GLfloat colors[8][3] = {{0.0, 1.0, 1.0},
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
				this->colors[m][c] = colors[i][c];
		}
	}
}



/**
 * Initializes the indices used to draw the box's faces.
 */
void Box::initializeIndices() {
	
	GLubyte indices[] = { 0,  1,  2,  3,
	                      4,  5,  6,  7,
	                      8,  9, 10, 11,
	                     12, 13, 14, 15,
	                     16, 17, 18, 19,
	                     20, 21, 22, 23};
	
	// Copy to class
	for (int i=0; i<24; i++)
		this->indices[i] = indices[i];
}



void Box::initializeMap() {
	
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



/**
 * Initializes the static points array of the class.
 */
void Box::initializePoints() {
	
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



/**
 * Sets the color of the entire box.
 * 
 * @param r
 *     Red component.
 * @param g
 *     Green component.
 * @param b
 *     Blue component.
 */
void Box::setColor(float r,
                   float g,
                   float b) {
	
	// Set color
	for (int i=0; i<24; i++) {
		colors[i][0] = r;
		colors[i][1] = g;
		colors[i][2] = b;
	}
}




/**
 * Simple test program.
 */
/*
int main(int argc, char **argv) {
	
	using namespace std;
	Box boxA(3), boxB(8);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Box" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	cout << "Map: " << endl;
	for (int i=0; i<8; i++) {
		for (int j=0; j<3; j++)
			cout << (int)Box::map[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Points: " << endl;
	for (int i=0; i<24; i++) {
		cout << i << ": ";
		for (int j=0; j<3; j++)
			cout << Box::boxPoints[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Indices: " << endl;
	for (int i=0; i<6; i++) {
		for (int j=0; j<4; j++)
			cout << (int)Box::indices[i*4+j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Coordinates: " << endl;
	for (int i=0; i<24; i++) {
		cout << i << ": ";
		for (int j=0; j<3; j++)
			cout << Box::coordinates[i][j] << " ";
		cout << endl;
	}
	
	// Test objects
	cout << endl;
	cout << "Box " << boxA.getID() << ": " << boxA.size << endl;
	cout << endl;
	cout << "Colors: " << endl;
	for (int i=0; i<24; i++) {
		for (int j=0; j<3; j++)
			cout << boxA.colors[i][j] << " ";
		cout << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Box" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
