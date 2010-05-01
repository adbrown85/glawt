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
	Interpreter *interpreter;
	
	// Banner
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Display" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create window
		Window::init(argc, argv);
		Window::create("Display");
		
		// Open scene
		scene = new Scene();
		interpreter = new Interpreter(scene);
		interpreter->run(Command::OPEN, "Display.xml");
		
		// Add display and controls
		display = new Display(interpreter);
		display->add(new Keyboard(interpreter));
		display->add(new Menu(interpreter));
		display->add(new Mouse(interpreter));
		
		// Start
		Window::start();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

