/*
 * Box.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Box.hpp"
using namespace std;



/**
 * Unit test for Box.
 */
int main() {
	
	Box boxA(3), boxB(8);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Box" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Static
	cout << "Map: " << endl;
	for (int i=0; i<8; i++) {
		for (int j=0; j<3; j++)
			cout << (int)Box::map[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Points: " << endl;
	for (int i=0; i<24; i++) {
		cout << i << ": ";
		for (int j=0; j<3; j++)
			cout << Box::points[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Indices: " << endl;
	for (int i=0; i<6; i++) {
		for (int j=0; j<4; j++)
			cout << (int)Box::indices[i*4+j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << "Coordinates: " << endl;
	for (int i=0; i<24; i++) {
		cout << i << ": ";
		for (int j=0; j<3; j++)
			cout << Box::coordinates[i][j] << " ";
		cout << endl;
	}
	
	// Test objects
	cout << endl;
	cout << "Box " << boxA.getID() << ": " << boxA.getSize() << endl;
	cout << endl;
	cout << "Colors: " << endl;
	for (int i=0; i<24; i++) {
		for (int j=0; j<3; j++)
			cout << boxA.colors[i][j] << " ";
		cout << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Box" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
