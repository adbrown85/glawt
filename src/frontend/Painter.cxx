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
	
	// Reset
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	
	// Paint
	painter->paint();
	glFlush();
}


int main(int argc,
         char *argv[]) {
	
	Scene *scene;
	
	try {
		
		// Initialize
		BasicFactory::install();
		Tester::init(argc, argv);
		Tester::setCallback("display", &display);
		Tester::open("Painter.xml");
		
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

