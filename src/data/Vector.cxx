/*
 * Vector.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Vector.hpp"


/**
 * Unit test for Vector.
 */
int main(int argc,
         char *argv[]) {
	
	Vector A(2, 2, 2);
	Vector B(3, 4, 5);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Vector" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test print
	cout << "Printing vectors:" << endl;
	cout << "  A: " << A << endl;
	cout << "  B: " <<  B << endl;
	
	// Plus/minus
	cout << "\nPlus/minus of A, B:" << endl;
	cout << "  " <<  A + B << endl;
	cout << "  " <<  A - B << endl;
	
	// Multiply/divide
	cout << "\nMultiply/divide of A, B:" << endl;
	cout << "  " <<  A * B << endl;
	cout << "  " <<  A / B << endl;
	
	// Double/half
	cout << "\nDouble/half of A:" << endl;
	cout << "  " <<  A * 2 << endl;
	cout << "  " <<  A / 2 << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Vector" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

