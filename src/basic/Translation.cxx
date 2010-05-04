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
	
	// Install tags
	BasicFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Translation.xml");
	Tester::start();
	
	// Finish
	return 0;
}

