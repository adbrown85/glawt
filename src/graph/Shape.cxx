/*
 * Shape.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Shape.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;



/**
 * Unit test for Shape.
 */
int main() {
	
	Shape items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Print
	cout << "Shapes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Style
	cout << "Setting style of 1..." << endl;
	items[0].setStyle(GL_TEXTURE_3D);
	cout << "Shapes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
