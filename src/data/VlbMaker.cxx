/*
 * VlbMaker.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "VlbMaker.hpp"


int main(int argc,
         char *argv[]) {
	
	VlbMaker *vlbMaker;
	string inFilePath, outFilePath;
	
	// Check arguments
	if (argc == 3) {
		inFilePath = argv[1];
		outFilePath = argv[2];
	} else {
		cout << "Usage: " << argv[0]
		     << " <input>"
		     << " <output>"
		     << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "VlbMaker" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Test
		cout << "Making VLB file..." << endl;
		vlbMaker = new VlbMaker(inFilePath, outFilePath);
		vlbMaker->start();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "VlbMaker" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

