/*
 * Shape.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <ctime>
#include <iostream>
#include "Shape.hpp"
#include "Translation.hpp"
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
	
	FakeShape shapes[NUMBER_OF_ITEMS];
	int randomNum;
	Matrix rotMatrix;
	Translation trans[NUMBER_OF_ITEMS];
	Node root;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Print
	cout << "Building tree... " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		root.addChild(&trans[i]);
		trans[i].addChild(&shapes[i]);
	}
	root.printTree();
	
	// Style
	cout << "Setting style of first shape..." << endl;
	shapes[0].setStyle(GL_TEXTURE_3D);
	root.printTree();
	
	// Randomize
	cout << "Randomizing..." << endl;
	srand(time(NULL));
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		randomNum = rand() % 10;
		trans[i].set(randomNum, randomNum, randomNum);
	}
	
	// Sort by depth
	cout << "Sorting by depth..." << endl;
	root.sortByDepth(rotMatrix);
	root.printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
