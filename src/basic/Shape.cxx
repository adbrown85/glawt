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
	Tag tag;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Tag
	try {
		cout << "Testing tag..." << endl;
		tag["size"] = "5.5";
		tag["style"] = "3D";
		shape = new FakeShape(tag);
		cout << "  " << *shape << endl;
	} catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

