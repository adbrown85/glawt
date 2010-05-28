/*
 * Quaternion.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include "common.h"
#include <cmath>
#include <iomanip>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Numeric.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief Encapsulation of an axis/angle rotation that avoids gimbal lock.
 */
class Quaternion {
public:
	Quaternion();
	Quaternion(float angle, const Vector &axis);
	Matrix getMatrix() const;
	Quaternion operator*(const Quaternion &B);
	void print();
	void set(float angle, const Vector &axis);
	void rotate(float angle, const Vector &axis);
	string toString() const;
protected:
	void normalize();
private:
	float s;
	Vector v;
};


#endif
