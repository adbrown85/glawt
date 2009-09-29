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
	
	// Handle arguments
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <file>" << endl;
		exit(1);
	}
	
	// Start
	Tester::initialize(argv[1]);
	Tester::open(argv[1]);
	Tester::start();
	
	// Finish
	return 0;
}

