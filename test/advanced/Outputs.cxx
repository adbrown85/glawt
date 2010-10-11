/*
 * Outputs.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Outputs.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	// Install tags
	AdvancedFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Outputs.xml");
	Tester::start();
	
	// Finish
	return 0;
}

