/*
 * Preprocessor.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Preprocessor.hpp"


int main(int argc,
         char *argv[]) {
	
	Preprocessor *pp;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Preprocessor" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Parse
		pp = new Preprocessor("Preprocessor.glsl");
		pp->start();
		
		// Results
		cout << "Boundaries:" << endl;
		pp->printBoundaries();
		cout << "  " << setw(2) <<  0 << " " << pp->getFileForLine( 0) << endl;
		cout << "  " << setw(2) << 15 << " " << pp->getFileForLine(15) << endl;
		cout << "  " << setw(2) << 31 << " " << pp->getFileForLine(31) << endl;
		cout << "\nDefines:" << endl;
		pp->printDefines();
		cout << "\nLines:" << endl;
		pp->printLines();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Preprocessor" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

