/*
 * Tester.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"


/**
 * Simple GLUT application for testing nodes with XML files.
 */
int main(int argc,
         char *argv[]) {
	
	// Start
	try {
		Tester::init(argc, argv);
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}

