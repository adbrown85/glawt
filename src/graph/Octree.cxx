/*
 * Octree.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Octree.hpp"
#include "Tester.hpp"
#include "ShaderFactory.hpp"
#include "ShapeFactory.hpp"
#include "TextureFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new ShaderFactory());
		Tester::install(new ShapeFactory());
		Tester::install(new TextureFactory());
		Tester::open("Octree.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

