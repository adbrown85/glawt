/*
 * Matrix.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Matrix.hpp"



int main() {
	
	float arr[16] = { 1.0,  2.0,  3.0,  4.0,
	                  5.0,  6.0,  7.0,  8.0,
	                  9.0, 10.0, 11.0, 12.0,
	                 13.0, 14.0, 15.0, 16.0};
	Matrix m1( 4.0, 3.0, 8.0, 7.0,
	           3.0, 2.0, 4.0, 6.0,
	           1.0, 6.0, 4.0, 5.0,
	           1.0, 2.0, 3.0, 4.0);
	Matrix m2, m3;
	Vector v1(1.0, 1.0, 1.0, 1.0), v2;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Matrix" << endl;
	cout << "****************************************" << endl;
	
	// Original
	cout << "\nShowing original..." << endl;
	m1.print();
	
	// Determinant
	cout << "\nCalculating determinant..." << endl;
	cout << "  " << m1.getDeterminant() << endl;
	
	// Inverse
	cout << "\nCalculating inverse..." << endl;
	m2 = m1.getInverse();
	m2.print();
	
	// Identity
	cout << "\nCalculating identity from original and inverse..." << endl;
	m3 = m1 * m2;
	m3.print();
	
	// Vector
	cout << "\nMultiplying by Vector..." << endl;
	v2 = m2 * v1;
	cout << "  " << v2 << endl;
	
	// Array
	cout << "\nSetting from array..." << endl;
	m2.set(arr);
	m2.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Matrix" << endl;
	cout << "****************************************" << endl;
}
