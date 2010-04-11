/*
 * Slice.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include <GL/glut.h>
#include "Slice.hpp"
void display(void);
void init(int argc, char *argv[], string);
void keyboard(unsigned char,int,int);
void special(int,int,int);
Dataset *dataset=NULL;
float xText, yText;
int height, width;
Slice *slice=NULL;


int main(int argc,
         char *argv[]) {
	
	string filename;
	
	// Handle arguments
	if (argc == 1)
		filename = "../../input/bear.vlb";
	else if (argc == 2)
		filename = argv[1];
	else {
		cerr << "Usage: " << argv[0] 
		     << " [<filename>]" << endl;
		exit(1);
	}
	
	try {
		
		// Create sequence and slice
		dataset = new Dataset(filename);
		slice = new Slice(dataset, 0);
		
		// Initialize display
		width = dataset->getWidth();
		height = dataset->getHeight();
		xText = ((float)width - 15) / width;
		yText = ((float)height - 30) / height;
		init(argc, argv, "Slice");
		dataset->print();
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Start display
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMainLoop();
}


/**
 * GLUT display callback.
 */
void display(void) {
	
	char buffer[4];
	
	// Draw slice
	glRasterPos2f(-1.00, -1.00);
	slice->draw();
	
	// Add index
	glRasterPos2f(-xText, +yText);
	sprintf(buffer, "%d", slice->getIndex());
	for (size_t i=0; i<strlen(buffer); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,
		                    buffer[i]);
	
	// Finish
	glutSwapBuffers();
}


/**
 * Initializes the GLUT display.
 */
void init(int argc,
          char *argv[],
          string title) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << title << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_LUMINANCE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glViewport(0, 0, width, height);
}


/**
 * GLUT special keys callback.
 */
void special(int key,
             int x,
             int y) {
	
	switch(key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_RIGHT:
			slice->next();
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
			slice->previous();
			glutPostRedisplay();
			break;
	}
}


/**
 * GLUT keyboard callback.
 */
void keyboard(unsigned char key,
              int x,
              int y) {
	
	switch(key) {
		case 'f':
		case 'n':
			slice->next();
			glutPostRedisplay();
			break;
		case 'b':
		case 'p':
			slice->previous();
			glutPostRedisplay();
			break;
	}
}

