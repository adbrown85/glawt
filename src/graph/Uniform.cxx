/*
 * Uniform.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <string>
#include <vector>
#include "Node.hpp"
#include "Program.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include "Uniform.hpp"
using namespace std;
void display(void);
void init(string);



/**
 * Unit test for Uniform.
 */
int main(int argc,
         char *argv[]) {
	
	Program program;
	Scene scene;
	Shader *shader;
	Texture *textures[2];
	Uniform *uniform;
	
	// Initialize
	init("Uniform");
	
	// Create objects
	try {
		textures[0] = new Texture2D("input/crate.jpg", "secondary");
		textures[1] = new Texture2D("input/stone.jpg", "primary");
		shader = new Shader("fragment", "glsl/texture.glsl");
		uniform = new Uniform("sampler2D", "secondary", 0);
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Put objects in graph
	scene.rootNode.addChild(textures[0]);
	textures[0]->addChild(textures[1]);
	textures[1]->addChild(&program);
	program.addChild(shader);
	program.addChild(uniform);
	
	// Associate and finalize graph
	scene.prepare();
	scene.print();
	
	// Start display
	program.apply();
	textures[0]->apply();
	textures[1]->apply();
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
