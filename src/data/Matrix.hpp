/*
 * Matrix.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Four-by-four matrix with multiplication and inversion.
 */
class Matrix {
	
	public:
		
		float arr[4][4];
		int size;
		
		Matrix();
		Matrix(float a0, float a1, float a2, float a3,
		       float b0, float b1, float b2, float b3,
		       float c0, float c1, float c2, float c3,
		       float d0, float d1, float d2, float d3);
		
		float get(int i, int j) const;
		void getArray(float array[16]);
		float getDeterminant() const;
		int getColumns() const;
		Matrix getInverse() const;
		int getRows() const;
		int getSize() const;
		Matrix getSubmatrix(int i, int j) const;
		float& operator()(int i, int j);
		friend Matrix operator*(const Matrix &A, const Matrix &B);
		friend Vector operator*(const Matrix &A, const Vector &B);
		void print();
		void set(float array[16]);
	
	private :
		
		float det(int n) const;
};


/**
 * @return an element in the array
 * 
 * @param i Row index
 * @param j Column index
 */
inline float Matrix::get(int i,
                         int j) const {
	return arr[i][j];
}


/**
 * @return the number of columns
 */
inline int Matrix::getColumns() const {
	return size;
}


/**
 * @return the number of rows.
 */
inline int Matrix::getRows() const {
	return size;
}



#endif
