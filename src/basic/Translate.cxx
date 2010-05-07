/*
 * Translate.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include "Translate.hpp"
#include "BasicFactory.hpp"
#include "Tester.hpp"
#include "Window.hpp"


/** Unit test for Translate. */
int main(int argc,
         char *argv[]) {
	
	// Install tags
	BasicFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Translate.xml");
	Tester::start();
	
	// Finish
	return 0;
}

