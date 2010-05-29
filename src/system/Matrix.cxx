/*
 * Matrix.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Matrix.hpp"
#include <cassert>
#include <ctime>


class MatrixTest {
public:
	void setUp();
	void testDeterminant();
	void testInverse();
	void testInverseTime();
	void testMultiplyTime();
	void testSetFromArray();
	void testTranspose();
	void testVectorMultiply();
	void testVectorMultiplyTime();
private:
	float TOLERANCE, ITERATIONS;
	Matrix m1, m2, m3;
};

void MatrixTest::setUp() {
	
	cout << "Setting up..." << endl;
	TOLERANCE = 0.000001;
	ITERATIONS = 100000;
	m1 = Matrix( 4.0, 3.0, 8.0, 7.0,
	             3.0, 2.0, 4.0, 6.0,
	             1.0, 6.0, 4.0, 5.0,
	             1.0, 2.0, 3.0, 4.0);
	m1.print();
}

void MatrixTest::testDeterminant() {
	
	float result;
	
	cout << "\nTesting determinant..." << endl;
	result = m1.getDeterminant();
	cout << "  " << result << endl;
	assert(result == 69);
}

void MatrixTest::testInverse() {
	
	cout << "\nTesting inverse..." << endl;
	m2 = m1.getInverse();
	m2.print();
	cout << "  ------------------------------------" << endl;
	m3 = m1 * m2;
	m3.print();
	for (int i=0; i<4; ++i)
		assert(fabs(m3(i,i)-1.0) < TOLERANCE);
	for (int i=0; i<3; ++i) {
		for (int j=i+1; j<4; ++j)
			assert(fabs(m3(i,j)-0.0) < TOLERANCE);
	}
	for (int i=1; i<4; ++i) {
		for (int j=0; j<i; ++j)
			assert(fabs(m3(i,j)-0.0) < TOLERANCE);
	}
}

void MatrixTest::testInverseTime() {
	
	clock_t beg, end;
	
	cout << "\nTesting inverse time..." << endl;
	beg = clock();
	for (int i=0; i<ITERATIONS; ++i)
		m1.getInverse();
	end = clock();
	cout << "  " << (end-beg) << " clocks." << endl;
	cout << "  " << ((double)end-beg) / CLOCKS_PER_SEC << " seconds." << endl;
}

void MatrixTest::testMultiplyTime() {
	
	clock_t beg, end;
	
	cout << "\nTesting operator* time..." << endl;
	beg = clock();
	for (int i=0; i<ITERATIONS; ++i)
		m1 * m2;
	end = clock();
	cout << "  " << (end-beg) << " clocks." << endl;
	cout << "  " << ((double)end-beg) / CLOCKS_PER_SEC << " seconds." << endl;
}

void MatrixTest::testSetFromArray() {
	
	float arr[16] = { 1.0,  2.0,  3.0,  4.0,
	                  5.0,  6.0,  7.0,  8.0,
	                  9.0, 10.0, 11.0, 12.0,
	                 13.0, 14.0, 15.0, 16.0};
	
	cout << "\nSetting from array..." << endl;
	m2.set(arr);
	m2.print();
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			assert(arr[i*4+j] == m2(j,i));
		}
	}
}

void MatrixTest::testTranspose() {
	
	cout << "\nTesting transpose..." << endl;
	m3 = m1.getTranspose();
	m3.print();
}

void MatrixTest::testVectorMultiply() {
	
	Vector v1(1.0, 1.0, 1.0, 1.0), v2;
	
	cout << "\nTesting Vector multiply..." << endl;
	v2 = m2 * v1;
	cout << "  " << v2 << endl;
}

void MatrixTest::testVectorMultiplyTime() {
	
	clock_t beg, end;
	Vector v;
	
	cout << "\nTesting vector multiply time..." << endl;
	beg = clock();
	for (int i=0; i<ITERATIONS; ++i)
		m1 * v;
	end = clock();
	cout << "  " << (end-beg) << " clocks." << endl;
	cout << "  " << ((double)end-beg) / CLOCKS_PER_SEC << " seconds." << endl;
}


int main() {
	
	MatrixTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Matrix" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testDeterminant();
	test.testInverse();
	test.testTranspose();
	test.testVectorMultiply();
	test.testSetFromArray();
	test.testMultiplyTime();
	test.testVectorMultiplyTime();
	test.testInverseTime();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Matrix" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

