/*
 * Square.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <string>
#include <vector>
#include "Square.hpp"
using namespace std;
void display(void);
void init(string);
Square *square;



/**
 * Unit test for Square.
 */
int main(int argc,
         char *argv[]) {
	
	// Initialize
	init("Square");
	
	// Create objects
	try {
		cout << "Creating objects..." << endl;
		square = new Square(2.0, true);
		square->print();
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
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
	square->draw();
	
	// Finish
	glFlush();
}
