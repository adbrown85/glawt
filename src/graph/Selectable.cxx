/*
 * Selectable.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Selectable.hpp"
using namespace std;


class FakeSelectable : public Selectable {
public:
	FakeSelectable() : Selectable(1.0) {}
	void draw() const {}
};


void print(const FakeSelectable &item) {
	
	cout << "  " << item.toString() << endl;
}


int main() {
	
	FakeSelectable item;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selectable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	cout << boolalpha;
	cout << "Original: " << endl;
	print(item);
	
	// Select, deselect
	cout << "Select: " << endl;
	item.select();
	print(item);
	cout << "Deselect: " << endl;
	item.deselect();
	print(item);
	
	// Toggle
	cout << "Toggle: " << endl;
	for (int i=0; i<5; ++i) {
		item.toggleSelected();
		print(item);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selectable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

