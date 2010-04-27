/*
 * Square.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Square.hpp"
#include "Tester.hpp"
#include "ShaderFactory.hpp"
#include "ShapeFactory.hpp"
#include "TextureFactory.hpp"
#include "TransformFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new ShaderFactory());
		Tester::install(new ShapeFactory());
		Tester::install(new TextureFactory());
		Tester::install(new TransformFactory());
		Tester::open("Square.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

