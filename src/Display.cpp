/*
 * Display.cpp
 *     3D display for items.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Scene *Display::scene=NULL;



/**
 * Draws the scene in the window.
 */
void Display::display(void) {
	
	int count=0;
	Item *item;
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Draw
	glTranslatef(0.0, 0.0, scene->position.z);
	glRotatef(scene->rotation.x, 1.0, 0.0, 0.0);
	glRotatef(scene->rotation.y, 0.0, 1.0, 0.0);
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		item = scene->items[i];
		item->draw();
	}
	
	// Refresh
	glutSwapBuffers();
}




/**
 * Draws the overlay on the display.
 */
void Display::overlay() {
	
	std::cerr << "Display::overlay()" << std::endl;
	
	// Draw overlay
}



/**
 * Starts the display.  Need to call initialize beforehand.
 * 
 * @param title
 *     Text to be shown on the window's title bar.
 * @param scene
 *     Pointer to a Scene with items.  Needs to be constructed first.
 */
void Display::start(std::string title,
                    Scene *scene) {
	
	char **argv;
	int argc=0, w, h, x=DISPLAY_DEFAULT_X, y=DISPLAY_DEFAULT_Y;
	
	// Copy
	if (scene == NULL)
		std::cerr << "Warning: scene is NULL!" << std::endl;
	h = scene->getHeight();
	w = scene->getWidth();
	Display::scene = scene;
	
	// Initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(w, h);
	glutCreateWindow(title.c_str());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	// Initialize view
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(w)/h, 0.1, 1000.0);
	
	// Register functions
	glutDisplayFunc(Display::display);
	Controls::install(scene);
	Menu::install(scene);
	
	// Start
	glutMainLoop();
}



/**
 * Simple test program.
 */
#include "Box.hpp"
int main(int argc, char *argv[]) {
	
	using namespace std;
	const int count=2;
	Box box[count];
	float x;
	Scene *scene = new Scene(640, 480);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	for (int i=0; i<count; i++) {
		x = (box[i].getID() - 1) * count;
		box[i].setPosition(x, 0.0, 0.0);
		scene->add(&box[i]);
	}
	Display::start("Display Test Program", scene);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
