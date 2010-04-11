/*
 * Display.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Box.hpp"
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
	scene.setFilename("input/basic.xml");
	Display::install(&menu);
	Display::install(&keyboard);
	Display::install(&mouse);
	Display::start(argc, argv, "Display", &scene, &interpreter);
	
	// Finish
	return 0;
}

