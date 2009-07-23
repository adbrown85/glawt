/*
 * Shader.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Shader.hpp"
using namespace std;
void display(void);



/**
 * Unit test for Shader and Program.
 */
int main(int argc,
         char *argv[]) {
	
	Program program;
	Shader shader;
	string filename="Shader.glsl";
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader, Program" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Uniform");
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.33, 0.1, 100.0);
	
	// Install shader into program
	shader.load('f', filename);
	program.addChild(&shader);
	
	// Associate and finalize graph
	program.associate();
	shader.associate();
	program.finalize();
	program.apply();
	
	// Start display
	glutDisplayFunc(display);
	glutMainLoop();
}



/**
 * GLUT display callback.
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
