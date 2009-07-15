/*
 * Selectable-test.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Selectable.hpp"
using namespace std;



int main() {
	
	Selectable item;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selectable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	cout << boolalpha;
	cout << "Original: " << endl;
	cout << "  " << item << endl;
	
	// Select, deselect
	cout << "Select: " << endl;
	item.select();
	cout << "  " << item << endl;
	cout << "Deselect: " << endl;
	item.deselect();
	cout << "  " << item << endl;
	
	// Toggle
	cout << "Toggle: " << endl;
	for (int i=0; i<5; ++i) {
		item.toggleSelected();
		cout << "  " << item << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selectable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
