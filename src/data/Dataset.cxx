/*
 * Dataset.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Dataset.hpp"


/**
 * Unit test for Dataset.
 */
int main(int argc,
         char *argv[]) {
	
	string filename;
	
	// Handle arguments
	if (argc != 2) {
		cerr << "Usage " << argv[0]
		     << " <filename>" << endl;
		exit(1);
	}
	filename = argv[1];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create
		Dataset dataset(filename);
		dataset.print();
	}
	catch (char const *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
