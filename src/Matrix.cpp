/*
 * Matrix.hpp
 *    Matrix class with floats.
 *
 * Author
 *    Andy Brown <andybrown85@gmail.com>
 */
#include "Matrix.hpp"



/**
 * Creates the identity matrix.
 */
Matrix::Matrix() {
	
	// Initialize
	size = 4;
	for (int i=0; i<size; i++)
		for (int j=0; j<size; j++)
			arr[i][j] = 0.0;
	
	// Set ones on diagonal
	for (int i=0; i<size; i++)
		arr[i][i] = 1.0;
}



/**
 * Creates a matrix from several values.
 */
Matrix::Matrix(float a0, float a1, float a2, float a3,
               float b0, float b1, float b2, float b3,
               float c0, float c1, float c2, float c3,
               float d0, float d1, float d2, float d3) {
	
	// Set sizes
	size = 4;
	
	// Set positions
	arr[0][0] = a0;
	arr[0][1] = a1;
	arr[0][2] = a2;
	arr[0][3] = a3;
	arr[1][0] = b0;
	arr[1][1] = b1;
	arr[1][2] = b2;
	arr[1][3] = b3;
	arr[2][0] = c0;
	arr[2][1] = c1;
	arr[2][2] = c2;
	arr[2][3] = c3;
	arr[3][0] = d0;
	arr[3][1] = d1;
	arr[3][2] = d2;
	arr[3][3] = d3;
}



/**
 * Calculate the determinant of a part of the matrix.
 */
float Matrix::det(int n) const {
	
	float po, rec, ret=0;
	int i=0, j=0, times;
	
	// Ending condition
	if (n == 2)
		ret = arr[0][0]*arr[1][1] - arr[0][1]*arr[1][0];
	
	// Recursion
	else {
		for (i=0; i<n; i++) {
			po = pow(-1, i+j);
			rec = getSubmatrix(i,j).getDeterminant();
			ret += po * arr[i][j] * rec;
		}
	}
	
	// Return
	return ret;
}



/**
 * Calculate the determinant of the entire matrix.
 */
float Matrix::getDeterminant() const {
	
	return det(getRows());
}



/**
 * Get the inverse of this matrix.
 */
Matrix Matrix::getInverse() const {
	
	float ds, dm, po;
	Matrix b;
	
	// Get determinant of entire matrix
	dm = getDeterminant();
	
	// Calculate
	for (int i=0; i<size; ++i) {
		for (int j=0; j<size; ++j) {
			po = pow(-1, i+j);
			ds = getSubmatrix(j,i).getDeterminant();
			b(i,j) = po * ds / dm;
		}
	}
	
	// Finish
	b.size = size;
	return b;
}



/**
 * Returns one of the elements in the matrix.
 * 
 * @param i
 *     Row of the element.
 * @param j
 *     Column of the element.
 */
float& Matrix::operator()(int i, int j) {
	
	if (i < 0 || i >= size)
		throw "Matrix: i out of bounds.";
	if (j < 0 || j >= size)
		throw "Matrix: j out of bounds.";
	return arr[i][j];
}



/**
 * Multiplies two matrices together.
 * 
 * Currently the Matrix class is fixed as a 4x4 matrix, but if it was not and 
 * matrices could have variables sizes, Matrix a needs to have the same number 
 * of columns as Matrix b has rows.
 */
Matrix operator*(const Matrix & a, const Matrix &b) {
	
	Matrix c;
	
	// Check if matrices can't be multiplied
	if (a.getColumns() != b.getRows())
		throw "Matrix: Matrices cannot be multiplied.";
	
	// Multiply rows of A with columns in B
	for (int i=0; i<c.getRows(); ++i) {
		for (int j=0; j<c.getColumns(); ++j) {
			c(i,j) = 0.0;
			for (int k=0; k<a.getColumns(); k++)
				c(i,j) += a.get(i,k) * b.get(k,j);
		}
	}
	return c;
}



/**
 * Prints the matrix out.
 */
void Matrix::print() {
	
	using namespace std;
	
	// Print all entries
	cout << fixed << setprecision(3);
	for (int i=0; i<size; i++) {
		int j=0;
		cout << "[" << setw(7) << arr[i][j];
		for (j=1; j<size; j++)
			cout << ", " << setw(7) << arr[i][j];
		cout << "]" << endl;
	}
	
	// Reset
	cout << resetiosflags(ios_base::floatfield) << setprecision(6);
}



/**
 * Returns a new matrix with row i and column j deleted.
 */
Matrix Matrix::getSubmatrix(int i, int j) const {
	
	int bi=0, bj=0;
	Matrix b;
	
	// Copy everything but row i and j
	for (int ai=0; ai<size; ++ai) {
		if (ai == i)
			continue;
		bj = 0;
		for (int aj=0; aj<size; ++aj) {
			if (aj == j)
				continue;
			b(bi,bj) = arr[ai][aj];
			++bj;
		}
		++bi;
	}
	
	// Finish
	b.size = this->size - 1;
	return b;
}



/**
 * Simple test program.
 */
int main() {
	
	using namespace std;
	Matrix m1( 4.0, 3.0, 8.0, 7.0,
	           3.0, 2.0, 4.0, 6.0,
	           1.0, 6.0, 4.0, 5.0,
	           1.0, 2.0, 3.0, 4.0);
	Matrix m2, m3;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Matrix" << endl;
	cout << "****************************************" << endl;
	
	// Original
	cout << endl;
	cout << "Original: " << endl;
	m1.print();
	
	// Determinant
	cout << endl;
	cout << "Determinant: " << endl;
	cout << m1.getDeterminant() << endl;
	
	// Inverse
	cout << endl;
	cout << "Inverse: " << endl;
	m2 = m1.getInverse();
	m2.print();
	
	// Identity
	cout << endl;
	cout << "Identity: " << endl;
	m3 = m1 * m2;
	m3.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Matrix" << endl;
	cout << "****************************************" << endl;
	return 0;
}
