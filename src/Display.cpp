/*
 * Display.cpp
 *     3D display for items.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Scene *Display::scene=NULL;
State *Display::state;
Interpreter *Display::interp;
Outline Display::outline(1.0);
std::vector<Control*> Display::cons;



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
	glTranslatef(scene->position.x, scene->position.y, 0.0);
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		item = scene->items[i];
		if (item->isShown()) {
			item->draw();
			if (item->isSelected()) {
				outline.copy(*item);
				outline.draw();
			}
		}
	}
	
	// Refresh
	glutSwapBuffers();
}



/**
 * Installs a control into the display.
 * 
 * @param control
 *     Pointer to an object implementing the Control interface.
 */
void Display::install(Control *control) {
	
	cons.push_back(control);
}



/**
 * Draws the overlay on the display.
 */
void Display::overlay() {
	
	std::cerr << "Display::overlay()" << std::endl;
	
	// Draw overlay
}



/**
 * Starts the display.
 * 
 * @param title
 *     Text to be shown on the window's title bar.
 * @param scene
 *     Pointer to a Scene with items.  Needs to be constructed first.
 */
void Display::start(std::string title,
                    Scene *scene,
                    State *state) {
	
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
	for (int i=0; i<cons.size(); i++)
		cons[i]->install();
	
	// Start
	glutMainLoop();
}



/**
 * Simple test program.
 */
#include "Box.hpp"
#include "Keyboard.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"
#include "Interpreter.hpp"
int main(int argc, char *argv[]) {
	
	using namespace std;
	const int count=2;
	Box b1(2.0), b2(3.0);
	float x;
	Keyboard keyboard;
	Menu menu;
	Mouse mouse;
	Scene scene(640, 480);
	State state;
	Interpreter inter(&scene, &state);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	b1.setPosition(-1.0, 0.0, 0.0);
	b2.setPosition( 2.0, 0.0, 0.0);
	scene.add(&b1);
	scene.add(&b2);
	menu.initialize(&scene, &state, &inter);
	keyboard.initialize(&scene, &state, &inter);
	mouse.initialize(&scene, &state, &inter);
	Display::install(&menu);
	Display::install(&keyboard);
	Display::install(&mouse);
	Display::start("Display Test Program", &scene, &state);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
