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
	cout << endl;
	
	// Test
	scene.setFilename("Display.xml");
	display = new Display(&scene, &interpreter);
	display->install(&menu);
	display->install(&keyboard);
	display->install(&mouse);
	display->start(argc, argv, "Display");
	
	// Finish
	return 0;
}

