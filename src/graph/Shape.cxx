/*
 * Shape.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
		FakeShape(const Tag &tag) : Shape(tag) {}
		void draw() const {};
};


/**
 * Unit test for Shape.
 */
int main() {
	
	FakeShape *shape;
	/* int randomNum; */
	Matrix rotMatrix;
	Tag tag;
	/* Translation trans[NUMBER_OF_ITEMS]; */
	Node root;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Tag
	try {
		cout << "Testing tag..." << endl;
		tag.setAttribute("size", "5.5");
		tag.setAttribute("style", "3D");
		shape = new FakeShape(tag);
		shape->print();
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Print
	cout << "\nBuilding tree... " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		shape = new FakeShape(tag);
		root.addChild(shape);
	}
	root.printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
/*
	// Print
	cout << "\nBuilding tree... " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		root.addChild(&trans[i]);
		trans[i].addChild(&shapes[i]);
	}
	root.printTree();
	
	// Randomize
	cout << "\nRandomizing..." << endl;
	srand(time(NULL));
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		randomNum = rand() % 10;
		trans[i].set(randomNum, randomNum, randomNum);
	}
	* 
	// Sort by depth
	cout << "\nSorting by depth..." << endl;
	root.sortByDepth(rotMatrix);
	root.printTree();
*/
}

