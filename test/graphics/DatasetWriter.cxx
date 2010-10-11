/*
 * DatasetWriter.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetWriter.hpp"


int main(int argc,
         char *argv[]) {
	
	DatasetWriter dw;
	int jump=1;
	string input, output;
	
	// Check arguments
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " <input> <output> [<jump>]" << endl;
		exit(1);
	} if (argc > 2) {
		input = argv[1];
		output = argv[2];
	} if (argc > 3) {
		jump = atoi(argv[3]);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetWriter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		cout << "Writing file..." << endl;
		dw.setInput(input);
		dw.setOutput(output);
		dw.setJump(jump);
		dw.write();
	} catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetWriter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

