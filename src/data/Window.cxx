/*
 * Window.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Window.hpp"



int main(int argc,
         char *argv[]) {
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Window" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	Window::init(argc, argv);
	Window::create("Window");
	Window::start();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Window" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

