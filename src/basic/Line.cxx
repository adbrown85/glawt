/*
 * Line.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BasicFactory.hpp"
#include "Tester.hpp"


int main(int argc,
         char *argv[]) {
	
	// Install tags
	BasicFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Line.xml");
	Tester::start();
	
	// Finish
	return 0;
}

