/*
 * Framebuffer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
#include "Tester.hpp"
#include "RenderFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new RenderFactory());
		Tester::open("Framebuffer.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

