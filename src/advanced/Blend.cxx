/*
 * Blend.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Blend.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"
#include "AdvancedFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	// Test
	try {
		BasicFactory::install();
		AdvancedFactory::install();
		Window::init(argc, argv);
		Tester::open("Blend.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

