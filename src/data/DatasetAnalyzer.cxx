/*
 * DatasetAnalyzer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetAnalyzer.hpp"


int main(int argc,
         char *argv[]) {
	
	Dataset *dataset;
	GLushort minimum, maximum;
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		filename = "../../textures/bunny.vlb";
	} else if (argc == 2) {
		filename = argv[1];
	} else {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetAnalyzer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Run
	try {
		dataset = new Dataset(filename);
		dataset->load(true);
		DatasetAnalyzer::findRange(dataset, minimum, maximum);
		cout << " minimum: " << minimum << endl;
		cout << " maximum: " << maximum << endl;
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "DatasetAnalyzer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

