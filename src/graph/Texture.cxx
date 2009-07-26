/*
 * Texture.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"
using namespace std;
void display(void);



/**
 * Unit test for Texture.
 */
int main(int argc,
         char *argv[]) {
	
	Texture *textures[4];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Texture");
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.33, 1.0, 100.0);
	
	// Create textures
	for (int i=0; i<4; ++i)
		textures[i] = new Texture("Texture.jpg");
	for (int i=0; i<3; ++i)
		textures[i]->addChild(textures[i+1]);
	
	// Prepare scene
	for (int i=0; i<4; ++i)
		textures[i]->associate();
	textures[0]->printTree();
	
	// Simulate traversing graph
	for (int i=0; i<4; ++i)
		textures[i]->apply();
	
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
