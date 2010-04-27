/*
 * Texture2D.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture2D.hpp"
#include "Tester.hpp"
#include "ShapeFactory.hpp"
#include "ShaderFactory.hpp"
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
		Tester::open("Texture2D.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

