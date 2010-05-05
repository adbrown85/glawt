/*
 * Matrix.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#include "Matrix.hpp"


/** Creates the identity matrix. */
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


/** Creates a matrix from explicit values. */
Matrix::Matrix(float a0, float a1, float a2, float a3,
               float b0, float b1, float b2, float b3,
               float c0, float c1, float c2, float c3,
               float d0, float d1, float d2, float d3) {
	
	// Set size
	size = 4;
	
	// Set positions
	arr[0][0] = a0; arr[0][1] = a1; arr[0][2] = a2; arr[0][3] = a3;
	arr[1][0] = b0; arr[1][1] = b1; arr[1][2] = b2; arr[1][3] = b3;
	arr[2][0] = c0; arr[2][1] = c1; arr[2][2] = c2; arr[2][3] = c3;
	arr[3][0] = d0; arr[3][1] = d1; arr[3][2] = d2; arr[3][3] = d3;
}


/** Creates an uninitialized matrix */
Matrix::Matrix(int size) {
	
	this->size = size;
}


/** Calculate the determinant of a part of the matrix. */
float Matrix::det(int n) const {
	
	float po, rec, ret=0;
	int i=0, j=0;
	
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


/** Get the inverse of this matrix. */
Matrix Matrix::getInverse() const {
	
	float dmInv, ds, po;
	Matrix b;
	
	// Get determinant of entire matrix
	dmInv = 1 / getDeterminant();
	
	// Calculate
	for (int i=0; i<size; ++i) {
		for (int j=0; j<size; ++j) {
			po = pow(-1, i+j);
			ds = getSubmatrix(j,i).getDeterminant();
			b.arr[i][j] = po * ds * dmInv;
		}
	}
	
	// Finish
	b.size = size;
	return b;
}


/** @return a new matrix with row i and column j deleted. */
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


/** @return matrix with rows and columns switched. */
Matrix Matrix::getTranspose() const {
	
	Matrix B(3);
	
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j) {
			B.arr[i][j] = arr[j][i];
		}
	}
	return B;
}


/** Returns one of the elements in the matrix. */
float& Matrix::operator()(int i, int j) {
	
	if (i < 0 || i >= size)
		throw Exception("[Matrix] Index out of bounds.");
	if (j < 0 || j >= size)
		throw Exception("[Matrix] Index out of bounds.");
	return arr[i][j];
}


/** Returns one of the elements in the matrix. */
float Matrix::operator()(int i, int j) const {
	
	if (i < 0 || i >= size)
		throw Exception("[Matrix] Index out of bounds.");
	if (j < 0 || j >= size)
		throw Exception("[Matrix] Index out of bounds.");
	return arr[i][j];
}


/** Multiplies two matrices together. */
Matrix operator*(const Matrix &A, const Matrix &B) {
	
	Matrix C(4);
	
	// Multiply rows of A with columns in B
	for (int i=0; i<C.size; ++i) {
		for (int j=0; j<C.size; ++j) {
			C.arr[i][j] = 0.0;
			for (int k=0; k<A.size; ++k)
				C.arr[i][j] += A.arr[i][k] * B.arr[k][j];
		}
	}
	return C;
}


/** Multiplies a matrix with a vector.*/
Vector operator*(const Matrix &A, const Vector &B) {
	
	Vector C;
	
	// Multiply rows of A with columns in B
	for (int i=0; i<C.size; ++i) {
		C[i] = 0.0;
		for (int k=0; k<C.size; ++k)
			C[i] += A.arr[i][k] * B[k];
	}
	return C;
}


/** Pretty prints the matrix to standard out. */
void Matrix::print() {
	
	// Print all entries
	cout << fixed << setprecision(3) << right;
	for (int i=0; i<size; i++) {
		int j=0;
		cout << "  ";
		cout << "[" << setw(7) << arr[i][j];
		for (j=1; j<size; j++)
			cout << ", " << setw(7) << arr[i][j];
		cout << "]" << endl;
	}
	
	// Reset
	cout << resetiosflags(ios_base::floatfield) << setprecision(6);
}


/** Sets the Matrix from values in the array (column-major order). */
void Matrix::set(float array[16]) {
	
	for (int j=0; j<4; j++)
		for (int i=0; i<4; i++)
			arr[i][j] = array[j*4+i];
}


/** Puts the matrix into a single-subscript array (column-major order). */
void Matrix::toArray(float *array) {
	
	for (int j=0; j<size; ++j)
		for (int i=0; i<size; ++i)
			array[j*size+i] = (*this)(i,j);
}


