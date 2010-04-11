/*
 * Quaternion.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Quaternion.hpp"


int main() {
	
	Matrix mat;
	Quaternion quaA, quaB, quaC;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Quaternion" << endl;
	cout << "****************************************" << endl;
	
	// Test getMatrix
	cout << "\nTesting 'set' and 'getMatrix'..." << endl;
	cout << "Using 45 degrees..." << endl;
	quaA.set(45, 0, 1, 0);
	quaA.print();
	mat = quaA.getMatrix();
	mat.print();
	
	// Test multiplication
	cout << "\nTesting 'operator*'..." << endl;
	cout << "Using 45 and 30 degrees..." << endl;
	quaA.set(45, 0, 1, 0);
	quaB.set(30, 0, 1, 0);
	quaC = quaA * quaB;
	mat = quaC.getMatrix();
	mat.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Quaternion" << endl;
	cout << "****************************************" << endl;
}

