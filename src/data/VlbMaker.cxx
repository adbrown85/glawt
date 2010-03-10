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
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "VlbMaker" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	cout << "Testing..." << endl;
	vlbMaker = new VlbMaker("VlbMaker.in", "VlbMaker.out");
	vlbMaker->start();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "VlbMaker" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

