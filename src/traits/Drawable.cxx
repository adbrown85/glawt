/*
 * Drawable.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Drawable.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;



/**
 * Fake class providing stubs for abstract methods.
 */
class FakeDrawable : public Drawable {
	
	public: 
		void draw() const {}
};



void print(const FakeDrawable &item) {
	
	cout << "  " << item.toString() << endl;
}



/**
 * Unit test for Drawable.
 */
int main() {
	
	FakeDrawable items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	cout << "Original: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		print(items[i]);
	
	// Sizes
	cout << "\nSetting sizes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].setSize(i+1);
		print(items[i]);
	}
	cout << "Copying size (4 to 1):" << endl;
	items[0].copySizeOf(items[3]);
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		print(items[i]);
	
	// Visibility
	cout << "\nShowing:" << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].show();
		print(items[i]);
	}
	cout << "Hiding:" << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].hide();
		print(items[i]);
	}
	cout << "Toggling:" << endl;
	for (int j=0; j<3; ++j) {
		if (j != 0)
			cout << "  ---------------------" << endl;
		for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
			items[i].toggleVisibility();
			print(items[i]);
		}
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
