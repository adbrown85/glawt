/*
 * Painter.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Painter.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"
Painter *painter;


void display(void) {
	
	// Clear
	Window::clear();
	
	// Paint
	painter->paint();
	
	// Flush
	Window::flush();
}


int main(int argc,
         char *argv[]) {
	
	try {
		
		// Initialize
		Window::init(argc, argv);
		BasicFactory::install();
		Tester::open("Painter.xml");
		Window::setDisplay(&display);
		
		// Start
		painter = new Painter(Tester::getScene());
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

