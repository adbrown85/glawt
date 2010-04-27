/*
 * Uniform.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"
#include "Tester.hpp"
#include "ShapeFactory.hpp"
#include "ShaderFactory.hpp"
#include "TextureFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new ShapeFactory());
		Tester::install(new TextureFactory());
		Tester::install(new ShaderFactory());
		Tester::open("Uniform.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

