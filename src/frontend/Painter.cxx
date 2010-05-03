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
Scene *scene;


void keyboard(unsigned char key,
              int x,
              int y) {
	
	switch (toupper(key)) {
	case 27:
		exit(0);
		break;
	case 'A':
		scene->addAllToSelection();
		Window::refresh();
		break;
	case 'D':
		scene->removeAllFromSelection();
		Window::refresh();
		break;
	default:
		break;
	}
}


void display(void) {
	
	// Clear
	Window::clear();
	
	// Paint
	painter->start();
	
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
		Window::setKeyboard(&keyboard);
		
		// Start
		scene = Tester::getScene();
		painter = new Painter(scene);
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

