/*
 * Cull.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cull.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"
#include "AdvancedFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		BasicFactory::install();
		AdvancedFactory::install();
		Tester::init(argc, argv);
		Tester::open("Cull.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}
