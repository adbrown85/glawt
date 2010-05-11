/*
 * Tester.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"
Scene Tester::scene;
Traverser *Tester::traverser;


/** GLUT display callback. */
void Tester::display(void) {
	
	// Clear
	Window::clear();
	
	// Draw
	Window::applyView();
	traverser->start();
	Window::write(scene.getFilename());
	
	// Finish
	Window::flush();
}


/** Creates a window, opens the scene, and prepares it. */
void Tester::open(const string &filename) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << FileUtility::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	Window::create(filename);
	Window::setDisplay(&display);
	
	// Open and prepare
	try {
		scene.open(filename);
		scene.prepare();
		scene.print();
		traverser = new Traverser(&scene);
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}


/** Starts the window's main loop, catching any exceptions. */
void Tester::start() {
	
	try {
		Window::start();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

