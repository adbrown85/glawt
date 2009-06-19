/*
 * Matrix.hpp
 *    Matrix class with floats.
 *
 * Author
 *    Andy Brown <andybrown85@gmail.com>
 */
#ifndef __MATRIX_HEADER__
#define __MATRIX_HEADER__
#include <cmath>
#include <iomanip>
#include <iostream>



class Matrix {
	
	
	private :
		
		float det(int n) const;
	
	
	public:
		
		float arr[4][4];
		int size;
		
		Matrix();
		Matrix(float a0, float a1, float a2, float a3,
		       float b0, float b1, float b2, float b3,
		       float c0, float c1, float c2, float c3,
		       float d0, float d1, float d2, float d3);
		
		float& operator()(int i, int j);
		friend Matrix operator*(const Matrix & m1, const Matrix &m2);
		
		void print();
		
		float get(int i, int j) const {return arr[i][j];}
		float getDeterminant() const;
		int getColumns() const {return size;}
		Matrix getInverse() const;
		int getRows() const {return size;}
		int getSize() const {return size;}
		Matrix getSubmatrix(int i, int j) const;
};

#endif
