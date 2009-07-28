/*
 * Sequence.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Sequence.hpp"



int main(int argc,
         char *argv[]) {
	
	Sequence *sequence;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Sequence" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create
		sequence = new Sequence("/home/andy/Desktop/MRbrain");
		cerr << "Number of files: " << sequence->getSize() << endl;
		cerr << "Filenames: " << endl;
		sequence->printFilenames();
	}
	catch (char const *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Sequence" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


