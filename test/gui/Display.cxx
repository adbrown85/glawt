/*
 * Display.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
#include "Delegate.hpp"
#include "Keyboard.hpp"
//#include "Menu.hpp"
#include "Mouse.hpp"


/**
 * Simple test program for Display.
 */
int main(int argc,
         char *argv[]) {
	
	Display *display;
	Scene *scene;
	Delegate *delegate;
	
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
		delegate = new Delegate(scene);
		delegate->run(Command::OPEN, "Display.xml");
		
		// Add display and controls
		display = new Display(delegate);
		display->add(new Keyboard(delegate));
		display->add(new Menu(delegate));
		display->add(new Mouse(delegate));
		
		// Start
		Window::start();
	}
	catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

