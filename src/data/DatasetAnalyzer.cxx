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
	DatasetAnalyzer analyzer;
	GLushort minimum, maximum;
	string filename;
	clock_t ticks;
	
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
	
	try {
		
		// Initialize
		dataset = new Dataset(filename);
		dataset->load(true);
		analyzer.setDataset(dataset);
		
		// Range
		cout << "\nPrinting range..." << endl;
		ticks=clock();
		analyzer.printRange();
		cout << (double)(clock()-ticks)/CLOCKS_PER_SEC << "s" << endl;
		
		// Histogram
		cout << "\nPrinting histogram..." << endl;
		ticks=clock();
		analyzer.printHistogram();
		cout << (double)(clock()-ticks)/CLOCKS_PER_SEC << "s" << endl;
	}
	catch (Exception &e) {
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

