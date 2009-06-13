/*
 * Vector.cpp
 *     General three-dimensional vector.
 *
 * Author
 *     Andrew Brown
 */
#include "Vector.hpp"


Vector::Vector() {
	
	// Set components
	x = 0;
	y = 0;
	z = 0;
}


Vector::Vector(float x, float y, float z) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector& Vector::operator=(const Vector& other) {
	
	// Check for self-assignment
	if (this == &other)
		return *this;
	
	// Set components
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}


Vector operator+(const Vector& left, const Vector& right) {
	
	Vector temp;
	
	// Add components
	temp.x = left.x + right.x;
	temp.y = left.y + right.y;
	temp.z = left.z + right.z;
	return temp;
}


Vector operator-(const Vector& left, const Vector& right) {
	
	Vector temp;
	
	// Subtract components
	temp.x = left.x - right.x;
	temp.y = left.y - right.y;
	temp.z = left.z - right.z;
	return temp;
}


Vector operator*(const Vector& left, float right) {
	
	Vector temp;
	
	// Multiply components
	temp.x = left.x * right;
	temp.y = left.y * right;
	temp.z = left.z * right;
	return temp;
}


Vector operator*(const Vector& left, const Vector& right) {
	
	Vector temp;
	
	// Multiply components
	temp.x = left.x * right.x;
	temp.y = left.y * right.y;
	temp.z = left.z * right.z;
	return temp;
}


Vector operator/(const Vector& left, float right) {
	
	Vector temp;
	
	// Divide components
	if (right != 0) {
		temp.x = left.x / right;
		temp.y = left.y / right;
		temp.z = left.z / right;
	}
	return temp;
}


Vector operator/(const Vector& left, const Vector& right) {
	
	Vector temp;
	
	// Divide components
	if (right.x != 0)
		temp.x = left.x / right.x;
	if (right.y != 0)
		temp.y = left.y / right.y;
	if (right.z != 0)
		temp.z = left.z / right.z;
	return temp;
}


ostream& operator<<(ostream& out, const Vector& vect) {
	
	// Add to stream
	out << "[" 
		<< vect.x << ", " 
		<< vect.y << ", "
		<< vect.z 
		<< "]";
	return out;
}



void Vector::add(float x, float y) {
	
	// Add to components
	this->x += x;
	this->y += y;
}



float Vector::dot(const Vector& other) {
	
	// Add products of like components
	return x * other.x + y * other.y + z * other.z;
}



void Vector::fill(float array[3],
                  float x,
                  float y,
                  float z) {
	
	// Fill the array with values
	array[0] = x;
	array[1] = y;
	array[2] = z;
}


float Vector::length() {
	
	// Return root of sum of squares
	return sqrt(x*x + y*y + z*z);
}


void Vector::normalize() {
	
	float len = length();
	
	// Divide by length
	if (len == 0) {
		x = 0;
		y = 0;
		z = 0;
	}
	else {
		x /= len;
		y /= len;
		z /= len;
	}
}


Vector Vector::perpendicular() {
	
	Vector temp;
	
	// Find unit vector
	temp = this->unit();
	
	// Negate components
	temp.x = - temp.x;
	temp.y = - temp.y;
	temp.z = - temp.z;
	return temp;
}


void Vector::print() {
	
	// Print values
	cout << *this << endl;
}


void Vector::set(float val) {
	
	// Set components
	this->x = val;
	this->y = val;
	this->z = val;
}


void Vector::set(float x, float y) {
	
	// Set components
	this->x = x;
	this->y = y;
}


void Vector::set(float x, float y, float z) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = z;
}


void Vector::setAverage(float x, float y, float z) {
	
	// Set components
	this->x = (x + this->x) / 2;
	this->y = (y + this->y) / 2;
	this->z = (z + this->z) / 2;
}


Vector Vector::unit() {
	
	// Return root of sum of squares
	return *this / length();
}






/*
void main() {
	
	Vector vA = Vector(2, 2, 2);
	Vector vB = Vector(3, 4, 5);
	
	// TEST PRINT
	cout << "Printing vectors:" << endl;
	cout << vA << endl;
	cout << vB << endl;
	
	// TEST OPERATORS
	cout << "Testing operators:" << endl;
	cout << vA + vB << endl;
	cout << vA - vB << endl;
	cout << vA * vB << endl;
	cout << vA / vB << endl;
	cout << vA / 2 << endl;
	cout << vA * 2 << endl;
}
*/
