/*
 * Box.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Box.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	// Install tags
	BasicFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Box.xml");
	Tester::start();
	
	// Finish
	return 0;
}

