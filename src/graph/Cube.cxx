/*
 * Cube.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cube.hpp"
#include "Tester.hpp"
#include "ShapeFactory.hpp"
#include "ShaderFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new ShaderFactory());
		Tester::install(new ShapeFactory());
		Tester::open("Cube.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

