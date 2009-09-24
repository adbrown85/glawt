/*
 * DatasetHeader.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetHeader.hpp"



int main(int argc,
         char *argv[]) {
	
	string filename;
	
	// Handle arguments
	if (argc == 1)
		filename = "input/king.vlb";
	else if (argc == 2)
		filename = argv[1];
	else {
		cerr << "Usage: " << argv[0] 
		     << " [<filename>]" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetHeader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		DatasetHeader header(filename);
		header.print();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetHeader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
