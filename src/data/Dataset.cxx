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
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create
		Dataset dataset("input/king.vlb");
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
