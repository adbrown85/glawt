/*
 * Cube.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cube.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	// Install tags
	BasicFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Cube.xml");
	Tester::start();
	
	// Finish
	return 0;
}

