/*
 * Texture3D.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture3D.hpp"
using namespace std;
void display(void);
void init(string);



/**
 * Unit test for Texture3D.
 */
int main(int argc,
         char *argv[]) {
	
	Texture3D *texture;
	
	// Test
	init("Texture3D");
	
	// Create texture
	texture = new Texture3D("input/alpha4x4.dat");
	texture->associate();
	
	// Attributes
	cerr << "Attributes:" << endl;
	texture->print();
	
	// Slices
	cerr << "\nSlices:" << endl;
	for (int i=0; i<texture->getWidth(); ++i) {
		texture->printSlice(i);
		cerr << endl;
	}
	
	// Start display
	glutDisplayFunc(display);
	glutMainLoop();
}



/**
 * Initializes the GLUT display.
 */
void init(string title) {
	
	char **argv;
	int argc=0;
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << title << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(640, 480);
	glutCreateWindow(title.c_str());
	
	// Set up viewport
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.33, 1.0, 100.0);
	glEnable(GL_BLEND);
}



/**
 * GLUT display callback.
 */
void display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	
	// Draw
	glBegin(GL_QUADS); {
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 1.0,  1.0, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0,  1.0, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 1.0, -1.0, 0.0);
	} glEnd();
	
	// Finish
	glFlush();
}
