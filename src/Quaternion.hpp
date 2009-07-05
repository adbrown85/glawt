/*
 * Quaternion.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __QUATERNION_HEADER__
#define __QUATERNION_HEADER__
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"



/**
 * @brief
 *     Encapsulation of a rotation that avoids gimbal lock.
 */
class Quaternion {
	
	
	public:
		
		Quaternion();
		
		Matrix getMatrix() const;
		void normalize();
		static float radians(float degrees);
		void set(float angle, float x, float y, float z);
		
		friend Quaternion operator*(const Quaternion &A,
		                            const Quaternion &B);
		friend std::ostream& operator<<(std::ostream &out,
		                                const Quaternion &A);
	
	
	private :
		
		float s;
		Vector v;
		
		static float pi;
};

#endif
