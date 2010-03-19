/*
 * Preprocessor.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
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
		cout << "Defines:" << endl;
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

