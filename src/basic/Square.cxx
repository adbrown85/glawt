/*
 * Square.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Square.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		BasicFactory::install();
		Window::init(argc, argv);
		Tester::open("Square.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

