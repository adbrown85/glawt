/*
 * Shader.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Shader.hpp"
using namespace std;
void display(void);
void init(string);



/**
 * Unit test for Shader and Program.
 */
int main(int argc,
         char *argv[]) {
	
	Program program;
	Shader *shader;
	
	// Initialize
	init("Shader");
	
	// Load source code into shader
	shader = new Shader("fragment", "glsl/coordinates.glsl");
	shader->print();
	cout << endl;
	shader->list();
	
	// Make graph
	program.addChild(shader);
	
	// Associate and finalize graph
	program.associateTree();
	program.finalizeTree();
	
	// Start display
	program.apply();
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
	glBegin(GL_QUADS); {
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 1.0,  1.0, 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0,  1.0, 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 1.0, -1.0, 0.0);
	} glEnd();
	
	// Finish
	glFlush();
}
