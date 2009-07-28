/*
 * Slice.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <GL/glut.h>
#include "Slice.hpp"
void display(void);
void init(string);
void newSlice(int offset);
void special(int,int,int);
int number=0, width=512;
Sequence *sequence;
Slice *slice=NULL;



int main(int argc,
         char *argv[]) {
	
	// Initialize
	init("Slice");
	
	// Create sequence and slice
	try {
		sequence = new Sequence("/home/andy/Desktop/bunny");
		newSlice(+1);
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Start display
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutMainLoop();
}



void newSlice(int direction) {
	
	// Delete old slice
	if (slice != NULL)
		delete slice;
	
	// Find new number based on direction
	if (direction < 0) {
		if (number == 1)
			number = sequence->getSize();
		else
			--number;
	}
	else {
		if (number == sequence->getSize())
			number = 1;
		else
			++number;
	}
	
	// Make new slice
	slice = new Slice(sequence, width, number);
}



/**
 * GLUT display callback.
 */
void display(void) {
	
	// Draw
	glDrawPixels(slice->getWidth(),
	             slice->getWidth(),
	             GL_LUMINANCE,
	             GL_UNSIGNED_SHORT,
	             slice->getData());
	
	// Finish
	glutSwapBuffers();
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_LUMINANCE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(width, width);
	glutCreateWindow(title.c_str());
	
	// Set up viewport
	glViewport(0, 0, width, width);
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
			newSlice(+1);
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
			newSlice(-1);
			glutPostRedisplay();
			break;
	}
}

