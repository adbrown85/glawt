/*
 * Translation.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include "Translation.hpp"
#include "BasicFactory.hpp"
#include "Tester.hpp"
#include "Window.hpp"


/**
 * Unit test for Translation.
 */
int main(int argc,
         char *argv[]) {
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		BasicFactory::install();
		Window::init(argc, argv);
		Tester::open("Translation.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

