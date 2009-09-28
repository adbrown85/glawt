/*
 * Framebuffer.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
#include "Scene.hpp"
void init(string);



/**
 * Unit test for %Framebuffer.
 */
int main() {
	
	Scene scene;
	
	// Start
	init("Framebuffer");
	
	// Create scene
	scene.addToRoot(new Framebuffer());
	scene.prepare();
	scene.print();
	
	// Finish
	return 0;
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

