/*
 * Quaternion.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Matrix.hpp"
#include "Vector.hpp"
using namespace std;



/**
 * @brief
 *     Encapsulation of a rotation that avoids gimbal lock.
 * @ingroup data
 */
class Quaternion {
	
	
	public:
		
		Quaternion();
		Matrix getMatrix() const;
		Quaternion operator*(const Quaternion &B);
		void print();
		void set(float angle,
		         float x,
		         float y,
		         float z);
		string toString();
	
	
	private :
		
		float s;
		Vector v;
		
		static float PI;
		
		void normalize();
		static float radians(float degrees);
};

#endif
