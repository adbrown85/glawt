/*
 * Shape.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include <iostream>
#include "Shape.hpp"
#include "Translate.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;


class FakeShape : public Shape {
public:
	FakeShape(const Tag &tag) : Shape(tag) {}
	virtual void draw() const {};
};


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
	} catch (Exception &e) {
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

