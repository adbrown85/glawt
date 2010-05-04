/*
 * Exception.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Exception.hpp"


int main(int argc,
         char *argv[]) {
	
	int line=45;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Exception" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		Exception e;
		e << "[Gander] This is an exception from " << line << ".";
		throw e;
	} catch (Exception &e) {
		cout << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Exception" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

