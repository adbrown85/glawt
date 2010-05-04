/*
 * Cull.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cull.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	// Install tags
	AdvancedFactory::install();
	
	// Start
	Tester::init(argc, argv);
	Tester::open("Cull.xml");
	Tester::start();
	
	// Finish
	return 0;
}

