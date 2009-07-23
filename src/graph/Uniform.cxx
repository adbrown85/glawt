/*
 * Uniform.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <vector>
#include "Program.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
using namespace std;
void display(void);



/**
 * Unit test for Uniform.
 */
int main(int argc,
         char *argv[]) {
	
	Program program;
	Shader shader;
	string filename="Uniform.glsl";
	Uniform *uniform;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Uniform" << endl;
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
	
	// Install program
	shader.load('f', filename);
	program.add(&shader);
	program.install();
	
	// Add uniforms
	uniform = new Uniform("brightness", 0.4f);
	uniform->install(program);
	delete uniform;
	
	// Start display
	glutDisplayFunc(display);
	glutMainLoop();
}



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
