/*
 * Box.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iomanip>
#include <iostream>
#include "Box.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;


/**
 * Structure to access Box internals.
 */
struct BoxTester : public Box {
	
	BoxTester(float size) : Box(size) {}
	
	static void testCoords() {
		cout << "Coords: " << endl;
		for (int i=0; i<24; i++) {
			cout << "  " << setw(2) << i << ":";
			for (int j=0; j<3; j++)
				cout << setw(2) << coords[i][j];
			cout << endl;
		}
	}
	
	static void testIndices() {
		cout << "Indices: " << endl;
		for (int i=0; i<6; i++) {
			cout << "  ";
			for (int j=0; j<4; j++)
				cout << setw(2) << (int)indices[i*4+j] << " ";
			cout << endl;
		}
	}
	
	static void testMap() {
		cout << "Map: " << endl;
		for (int i=0; i<8; i++) {
			cout << "  ";
			for (int j=0; j<3; j++)
				cout << setw(2) << (int)map[i][j] << " ";
			cout << endl;
		}
	}
	
	static void testPoints() {
		cout << "Points: " << endl;
		for (int i=0; i<24; i++) {
			cout << "  " << setw(2) << i << ": ";
			for (int j=0; j<3; j++)
				cout << points[i][j] << " ";
			cout << endl;
		}
	}
};


/**
 * Unit test for Box.
 */
int main() {
	
	BoxTester *items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Box" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create items
	cout << "Creating boxes:" << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i] = new BoxTester(i+1);
		items[i]->print();
	}
	
	// Static data
	BoxTester::testCoords();
	BoxTester::testIndices();
	BoxTester::testMap();
	BoxTester::testPoints();
	
	// Object data
	cout << "Sizes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i]->getSize() << endl;
	
	// Deallocate
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		delete items[i];
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Box" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

