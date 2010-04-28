/*
 * Display.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
#include "Interpreter.hpp"
#include "Keyboard.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"


/**
 * Simple test program for Display.
 */
int main(int argc,
         char *argv[]) {
	
	Display *display;
	Scene *scene;
	
	// Banner
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create scene
		scene = new Scene(512, 512);
		scene->setFilename("Display.xml");
		
		// Start display
		display = new Display(scene, "Display", argc, argv);
		display->install(new Keyboard(display->getInterpreter(), scene));
		display->install(new Menu(display->getInterpreter(), scene));
		display->install(new Mouse(display->getInterpreter(), scene));
		display->start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

