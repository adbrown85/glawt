/*
 * Display.cpp
 *     3D display for items.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Scene *Display::scene=NULL;
Delegate *Display::delegate=NULL;
vector<Control*> Display::controls;
vector<Manipulator*> Display::manipulators;



/**
 * Draws the scene in the window.
 */
void Display::display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Paint
	Painter::paint(*scene, manipulators);
	
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
void Display::start(std::string title,
                    Scene *scene,
                    Delegate *delegate) {
	
	char **argv;
	int argc=0, width, height, x=100, y=100;
	vector<Manipulator*> manipulators;
	
	// Copy
	height = scene->getHeight();
	width = scene->getWidth();
	Display::scene = scene;
	Display::delegate = delegate;
	
	// Initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Initialize view
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 50.0);
	
	// Open and prepare scene
	try {
		delegate->run(Command::OPEN, scene->getFilename());
		scene->prepare();
		scene->print();
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
	
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
