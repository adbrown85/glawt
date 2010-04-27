/*
 * Fullscreen.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Fullscreen.hpp"
#include "Tester.hpp"
#include "ShapeFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new ShapeFactory());
		Tester::open("Fullscreen.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

