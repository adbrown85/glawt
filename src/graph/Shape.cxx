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
 * Fake class for testing Shape.
 */
class FakeShape : public Shape {
	public:
		void draw() const {};
};



/**
 * Unit test for Shape.
 */
int main() {
	
	FakeShape items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Print
	cout << "Shapes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		items[i].print();
	
	// Style
	cout << "Setting style of 1..." << endl;
	items[0].setStyle(GL_TEXTURE_3D);
	cout << "Shapes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		items[i].print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
