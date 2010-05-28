/*
 * Matrix.hpp
 * 
 * Author
 *    Andrew Brown <adb1413@rit.edu>
 */
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "common.h"
#include <cmath>
#include <iomanip>
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief Four-by-four matrix with multiplication and inversion.
 */
class Matrix {
public:
	Matrix();
	Matrix(float a0, float a1, float a2, float a3,
	       float b0, float b1, float b2, float b3,
	       float c0, float c1, float c2, float c3,
	       float d0, float d1, float d2, float d3);
	float getDeterminant() const;
	int getColumns() const;
	Matrix getInverse() const;
	int getRows() const;
	int getSize() const;
	Matrix getTranspose() const;
	float& operator()(int i, int j);
	float operator()(int i, int j) const;
	friend Matrix operator*(const Matrix &A, const Matrix &B);
	friend Vector operator*(const Matrix &A, const Vector &B);
	void print();
	void set(float array[16]);
	void toArray(float *array);
protected:
	Matrix getSubmatrix(int i, int j) const;
	float det(int n) const;
private:
	Matrix(int size);
	float arr[4][4];
	int size;
};

/** Calculate the determinant of the entire matrix. */
inline float Matrix::getDeterminant() const {return det(size);}

/** @return the number of columns */
inline int Matrix::getColumns() const {return size;}

/** @return the number of rows. */
inline int Matrix::getRows() const {return size;}




#endif
