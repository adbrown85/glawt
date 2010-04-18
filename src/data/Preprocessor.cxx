/*
 * Preprocessor.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Preprocessor.hpp"
Preprocessor *pp;


void testFileForLine(int line) {
	
	cout << "  " << setw(2) << line 
	     << " " << pp->getFileForLine(line) << endl;
}


void testRealLineNumber(int line) {
	
	cout << "  " << setw(2) << line 
	     << " " << pp->getRealLineNumber(line) << endl;
}


int main(int argc,
         char *argv[]) {
	
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
		cout << "\nDefines:" << endl;
		pp->printDefines();
		cout << "\nLines:" << endl;
		pp->printLines();
		
		// Files for lines
		cout << "\nFiles for lines:" << endl;
		testFileForLine(1);
		testFileForLine(15);
		testFileForLine(31);
		
		// Line numbers
		cout << "\nLine numbers:" << endl;
		testRealLineNumber(1);
		testRealLineNumber(15);
		testRealLineNumber(31);
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

