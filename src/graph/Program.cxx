/*
 * Program.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Program.hpp"
using namespace std;



/**
 * GLUT callback.
 */
void display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0.0, 0.0, -2);
	
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



/**
 * Unit test for Program.
 */
int main(int argc,
         char *argv[]) {
	
	Program program;
	Shader shader;
	string filename="Shader.glsl";
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Program" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Program Test");
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 640.0/480.0, 0.1, 100.0);
	
	// Install program
	shader.load('f', filename);
	program.add(&shader);
	program.install();
	
	// Start display
	glutDisplayFunc(display);
	glutMainLoop();
}
