/*
 * Log.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Log.hpp"
using System::log;


int main(int argc, char *argv[]) {
	
	Log::iterator it;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Log" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	log << "This is a message!" << endl;
	log << "This is a message with a " << 1.5 << endl;
	log << "This is a message with a " << 1 << endl;
	
	for (it=log.begin(); it!=log.end(); ++it) {
		cout << "  " << *it << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Log" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

