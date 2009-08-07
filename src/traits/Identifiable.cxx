/*
 * Identifiable-test.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <cassert>
#include <iostream>
#include "Identifiable.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;



void print(const Identifiable item) {
	
	cout << "  " << item.toString() << endl;
}



int main() {
	
	Identifiable *identifiable, items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Identifiable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Check assignment of IDs
	cout << "Asserting assignment of IDs: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		print(items[i]);
		assert(items[i].getID() == i);
	}
	
	// Check find by ID
	cout << "Asserting find by ID: " << endl;
	identifiable = Identifiable::findByID(2);
	cout << "  " << identifiable->getID() << endl;
	assert(identifiable->getID() == 2);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Identifiable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
