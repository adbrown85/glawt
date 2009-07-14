/*
 * Identifiable-test.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Identifiable.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;



int main() {
	
	Identifiable items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Identifiable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	cout << "Original: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Identifiable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
