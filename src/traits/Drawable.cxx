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



int main() {
	
	Drawable items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	cout << "Original: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Sizes
	cout << "\nSetting sizes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].setSize(static_cast<float>(i+1));
		cout << "  " << items[i] << endl;
	}
	cout << "Copying size (4 to 1):" << endl;
	items[0].copySizeOf(items[3]);
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Visibility
	cout << "\nShowing:" << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].show();
		cout << "  " << items[i] << endl;
	}
	cout << "Hiding:" << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].hide();
		cout << "  " << items[i] << endl;
	}
	cout << "Toggling:" << endl;
	for (int j=0; j<3; ++j) {
		if (j != 0)
			cout << "  ---------------------" << endl;
		for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
			items[i].toggleVisibility();
			cout << "  " << items[i] << endl;
		}
	}
	
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
