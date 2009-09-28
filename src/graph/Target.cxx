/*
 * Target.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"
#include "Scene.hpp"
void init(string);



int main(int argc,
         char *argv[]) {
	
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Target" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	init("Target");
	try {
		scene.addToRoot(new Texture2D("mytexture", 512, 512));
		scene.addToLast(new Framebuffer());
		scene.addToLast(new Target("mytexture"));
		scene.prepare();
		scene.print();
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Target" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}





/**
 * Initializes the GLUT display.
 */
void init(string title) {
	
	char **argv;
	int argc=0;
	
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

