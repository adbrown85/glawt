/*
 * Outline.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Outline.hpp"
bool Outline::loaded = false;
GLfloat Outline::points[24][3];
GLubyte Outline::indices[24], Outline::map[8][3];



/**
 * Creates a new Outline.
 * 
 * @param size
 *     Length of the Outline's sides.
 */
Outline::Outline(float size) {
	
	// Initialize
	initialize();
	this->size = size;
	setColor(1.0, 1.0, 1.0);
}



/**
 * Draws the Outline.
 */
void Outline::draw() const {
	
	// Enable arrays
	glVertexPointer(3, GL_FLOAT, 0, points);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	// Draw vertices
	glPushMatrix(); {
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(position.x, position.y, position.z);
		glScalef(size*1.002, size*1.002, size*1.002);
		glTranslatef(-0.5, -0.5, -0.5);
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, indices);
	} glPopMatrix();
	
	// Reset
	glDisableClientState(GL_VERTEX_ARRAY);
}



/**
 * Initializes the Outline.
 */
void Outline::initialize() {
	
	// Initialize vertices of class
	if (!loaded) {
		initializeMap();
		initializePoints();
		initializeIndices();
		loaded = true;
	}
	
	// Store type
	type = "Outline";
}



/**
 * Initializes the indices used to draw the Outline's faces.
 */
void Outline::initializeIndices() {
	
	// Copy to class
	for (int i=0; i<24; i++)
		this->indices[i] = i;
}



void Outline::initializeMap() {
	
	GLubyte map[8][3] = {{ 0,  7, 21},
	                     { 1,  2, 16},
	                     { 3,  4, 19},
	                     { 5,  6, 22},
	                     { 8, 15, 17},
	                     { 9, 10, 20},
	                     {11, 12, 23},
	                     {13, 14, 18}};
	
	// Copy to class
	for (int i=0; i<8; i++)
		for (int j=0; j<3; j++)
			this->map[i][j] = map[i][j];
}



/**
 * Initializes the static points array of the class.
 */
void Outline::initializePoints() {
	
	GLfloat points[8][3] = {{1.0, 1.0, 1.0},
	                        {0.0, 1.0, 1.0},
	                        {0.0, 0.0, 1.0},
	                        {1.0, 0.0, 1.0},
	                        {0.0, 1.0, 0.0},
	                        {1.0, 1.0, 0.0},
	                        {1.0, 0.0, 0.0},
	                        {0.0, 0.0, 0.0}};
	int i;
	
	// Copy to class
	for (int pt=0; pt<8; pt++) {
		for (int va=0; va<3; va++) {
			i = map[pt][va];
			for (int co=0; co<3; co++)
				this->points[i][co] = points[pt][co];
		}
	}
}



/**
 * Sets the color of the entire Outline.
 * 
 * @param r
 *     Red component.
 * @param g
 *     Green component.
 * @param b
 *     Blue component.
 */
void Outline::setColor(float r,
                       float g,
                       float b) {
	
	// Copy
	color[0] = r;
	color[1] = g;
	color[2] = b;
}




/**
 * Simple test program.
 */
/*
int main(int argc, char **argv) {
	
	using namespace std;
	Outline o1(3.0);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Outline" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	cout << "Map: " << endl;
	for (int i=0; i<4; i++) {
		for (int j=0; j<3; j++)
			cout << (int)Outline::map[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Points: " << endl;
	for (int i=0; i<8; i++) {
		cout << i << ": ";
		for (int j=0; j<3; j++)
			cout << Outline::points[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Indices: " << endl;
	for (int i=0; i<4; i++) {
		for (int j=0; j<2; j++)
			cout << (int)Outline::indices[i*2+j] << " ";
		cout << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Outline" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
