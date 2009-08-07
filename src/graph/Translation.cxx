/*
 * Translation.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Translation.hpp"
#define NUMBER_OF_ITEMS 4



int main() {
	
	Translation items[4];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Print
	cout << "Printing items: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		items[i].print();
	
	// Print
	cout << "Changing: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i].set(i, i, i);
		items[i].print();
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
