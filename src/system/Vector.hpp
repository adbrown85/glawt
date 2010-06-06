/*
 * Vector.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "common.h"
#include <cmath>
#include <iomanip>
#include "Exception.hpp"
using namespace std;


/** @brief Four-component vector with dot and cross product capabilities.
 * @ingroup system
 */
class Vector {
public:
	int size;
	float x, y, z, w;
public:
	Vector();
	Vector(float value);
	Vector(float x, float y);
	Vector(float x, float y, float z);
	Vector(float x, float y, float z, float w);
	Vector& operator=(const Vector &B);
	Vector& operator+=(const Vector &B);
	Vector& operator-=(const Vector &B);
	Vector& operator*=(const Vector &B);
	Vector& operator/=(const Vector &B);
	Vector& operator+=(float b);
	Vector& operator-=(float b);
	Vector& operator*=(float b);
	Vector& operator/=(float b);
	float& operator[](int i);
	float operator[](int i) const;
	float length() const;
	float get(int i) const;
	void set(float x, float y);
	void set(float x, float y, float z);
	void set(float x, float y, float z, float w);
public:
	friend bool operator==(const Vector &A, const Vector &B);
	friend Vector operator+(const Vector &A, const Vector &B);
	friend Vector operator-(const Vector &A, const Vector &B);
	friend Vector operator*(const Vector &A, const Vector &B);
	friend Vector operator/(const Vector &A, const Vector &B);
	friend Vector operator+(const Vector &A, float b);
	friend Vector operator-(const Vector &A, float b);
	friend Vector operator*(const Vector &A, float b);
	friend Vector operator/(const Vector &A, float b);
	friend ostream& operator<<(ostream& out, const Vector& A);
	friend Vector cross(const Vector& A, const Vector& B);
	friend float dot(const Vector& A, const Vector &B);
	friend Vector min(const Vector &A, const Vector &B);
	friend Vector max(const Vector &A, const Vector &B);
	friend Vector normalize(Vector vector);
};


#endif
