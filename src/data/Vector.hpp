/*
 * Vector.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com
 */
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;



/**
 * @brief
 *     Four-component vector with dot and cross product capabilities.
 * @ingroup data
 */
class Vector {
	
	
	public:
		
		int size;
		float x, y, z, w;
		
		Vector();
		Vector(float x, float y);
		Vector(float x, float y, float z);
		Vector(float x, float y, float z, float w);
		Vector& operator=(const Vector &B);
		friend Vector operator*(const Vector &A, float b);
		friend Vector operator*(const Vector &A, const Vector &B);
		friend Vector operator/(const Vector &A, float b);
		friend Vector operator/(const Vector &A, const Vector &B);
		friend Vector operator+(const Vector &A, const Vector &B);
		friend Vector operator-(const Vector &A, const Vector &B);
		friend std::ostream& operator<<(std::ostream& out, const Vector& A);
		float& operator()(int i);
		
		Vector crossProduct(const Vector& B) const;
		float dotProduct(const Vector &B) const;
		float length() const;
		
		float get(int i) const;
		Vector getNormalized() const;
		void set(float x, float y);
		void set(float x, float y, float z);
		void set(float x, float y, float z, float w);
};

#endif
