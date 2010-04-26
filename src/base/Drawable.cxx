/*
 * Drawable.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Drawable.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;


class FakeDrawable : public Drawable {
	
	public: 
		FakeDrawable() {}
		FakeDrawable(const Tag &tag) : Drawable(tag) {}
		void draw() const {}
};


void print(const FakeDrawable &item) {
	
	cout << "  " << item.toString() << endl;
}


int main() {
	
	FakeDrawable *drawable;
	FakeDrawable items[NUMBER_OF_ITEMS];
	Tag tag;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test tag
	cout << "\nTag:" << endl;
	tag.attributes["size"] = "8.0";
	drawable = new FakeDrawable(tag);
	print(*drawable);
	
	// Initialize
	cout << "\nOriginal: " << endl;
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

