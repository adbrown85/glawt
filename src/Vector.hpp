/*
 * Vector.h
 *		General three-dimensional vector.
 *
 * Author
 *		Andrew Brown
 */
#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#include <iostream>
using namespace std;



class Vector {
	
	
	public:
		
		float x, y, z;
		
		Vector();
		Vector(float x, float y, float z);
		Vector& operator=(const Vector& other);
		friend Vector operator+(const Vector& left, const Vector& right);
		friend Vector operator-(const Vector& left, const Vector& right);
		friend Vector operator*(const Vector& left, float right);
		friend Vector operator*(const Vector& left, const Vector& right);
		friend Vector operator/(const Vector& left, float right);
		friend Vector operator/(const Vector& left, const Vector& right);
		friend ostream& operator<<(ostream& out, const Vector& vect);
		
		void add(float x, float y);
		float dot(const Vector& other);
		static void fill(float array[3], float x, float y, float z);
		float length();
		void normalize();
		Vector perpendicular();
		void print();
		void set(float val);
		void set(float x, float y);
		void set(float x, float y, float z);
		void setAverage(float x, float y, float z);
		Vector unit();
};

#endif
