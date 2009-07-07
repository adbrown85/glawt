/*
 * Display.cpp
 *     3D display for items.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Scene *Display::scene=NULL;
Outline Display::outline(1.0);
vector<Control*> Display::controls;
vector<Manipulator*> Display::manipulators;



/**
 * Draws the scene in the window.
 */
void Display::display(void) {
	
	float rotationMatrixArray[16];
	Matrix rotationMatrix;
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Transform
	glTranslatef(scene->position.x, scene->position.y, scene->position.z);
	rotationMatrix = scene->getRotationMatrix();
	rotationMatrix.getArray(rotationMatrixArray);
	glMultMatrixf(rotationMatrixArray);
	
	// Draw
	draw(&scene->rootNode);
	
	// Refresh
	glutSwapBuffers();
}



void Display::draw(Node *node) {
	
	Item *item;
	Translation *translation;
	vector<Manipulator*>::iterator mi;
	
	// Item
	if (item = dynamic_cast<Item*>(node)) {
		if (item->isShown()) {
			item->draw();
			if (item->isSelected()) {
				outline.copy(*item);
				outline.draw();
				for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
					(*mi)->copy(*item);
					(*mi)->draw();
				}
			}
			drawChildren(node);
		}
	}
	
	// Translation
	else if (translation = dynamic_cast<Translation*>(node)) {
		translation->apply();
		drawChildren(node);
		translation->restore();
	}
	
	// Node
	else
		drawChildren(node);
}



/**
 * Draws the children of a node.
 */
void Display::drawChildren(Node *node) {
	
	int numberOfChildren;
	
	// Draw each child
	numberOfChildren = node->children.size();
	for (int i=0; i<numberOfChildren; ++i)
		draw(node->children[i]);
}



/**
 * Installs a control into the display.
 * 
 * @param control
 *     Pointer to an object implementing the Control interface.
 */
void Display::install(Control *control) {
	
	// Add to vector
	controls.push_back(control);
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
void Display::start(std::string title, Scene *scene) {
	
	char **argv;
	int argc=0, width, height, x=DISPLAY_DEFAULT_X, y=DISPLAY_DEFAULT_Y;
	vector<Manipulator*> manipulators;
	
	// Copy
	if (scene == NULL)
		std::cerr << "Warning: scene is NULL!" << std::endl;
	height = scene->getHeight();
	width = scene->getWidth();
	Display::scene = scene;
	
	// Initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	// Initialize view
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 1000.0);
	
	// Register functions
	glutDisplayFunc(Display::display);
	for (int i=0; i<controls.size(); i++) {
		manipulators = controls[i]->install(scene);
		for (int j=0; j<manipulators.size(); j++)
			Display::manipulators.push_back(manipulators[j]);
	}
	
	// Start
	glutMainLoop();
}



/**
 * Simple test program.
 */
/*
#include "Box.hpp"
#include "Interpreter.hpp"
#include "Keyboard.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"
int main(int argc, char *argv[]) {
	
	using namespace std;
	Box b1(1.0), b2(3.0);
	Scene scene(640, 480);
	Interpreter interpreter(&scene);
	Keyboard keyboard(&interpreter);
	Menu menu(&interpreter);
	Mouse mouse(&interpreter);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	
	// Test
	cout << endl;
	scene.add(&b1.setPosition(-1.0, 0.0, 0.0));
	scene.add(&b2.setPosition( 2.0, 0.0, 0.0));
	Display::install(&menu);
	Display::install(&keyboard);
	Display::install(&mouse);
	Display::start("Display Test Program", &scene);
	
	// Finish
	return 0;
}
*/
