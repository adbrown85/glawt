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
	try {
		Tester::initialize(argc, argv);
		Tester::open(argv[1]);
		Tester::start();
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	return 0;
}

