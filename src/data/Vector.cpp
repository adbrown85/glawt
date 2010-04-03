/*
 * Vector.cpp
 *     General three-dimensional vector.
 * 
 * Author
 *     Andrew Brown
 */
#include "Matrix.hpp"


Vector::Vector() {
	
	// Set components
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
	size = 4;
}


Vector::Vector(float x, float y) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = 0.0;
	this->w = 1.0;
	size = 2;
}


Vector::Vector(float x, float y, float z) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1.0;
	size = 3;
}


Vector::Vector(float x, float y, float z, float w) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	size = 4;
}


Vector& Vector::operator=(const Vector& B) {
	
	// Check for self-assignment
	if (this == &B)
		return *this;
	
	// Set components
	x = B.x;
	y = B.y;
	z = B.z;
	w = B.w;
	size = B.size;
	return *this;
}


Vector operator*(const Vector& A, float b) {
	
	Vector C;
	
	// Multiply components
	C.x = A.x * b;
	C.y = A.y * b;
	C.z = A.z * b;
	C.w = A.w * b;
	C.size = A.size;
	return C;
}


Vector operator*(const Vector& A, const Vector& B) {
	
	Vector C;
	
	// Multiply components
	C.x = A.x * B.x;
	C.y = A.y * B.y;
	C.z = A.z * B.z;
	C.w = A.w * B.w;
	C.size = A.size;
	return C;
}


Vector operator/(const Vector& A, float b) {
	
	Vector C;
	
	// Divide components
	if (b != 0) {
		C.x = A.x / b;
		C.y = A.y / b;
		C.z = A.z / b;
		C.w = A.w / b;
	}
	C.size = A.size;
	return C;
}


Vector operator/(const Vector& A, const Vector& B) {
	
	Vector C;
	
	// Divide components
	if (B.x != 0)
		C.x = A.x / B.x;
	if (B.y != 0)
		C.y = A.y / B.y;
	if (B.z != 0)
		C.z = A.z / B.z;
	if (B.w != 0)
		C.w = A.w / B.w;
	C.size = A.size;
	return C;
}


Vector operator+(const Vector& A, const Vector& B) {
	
	Vector C;
	
	// Add components
	C.x = A.x + B.x;
	C.y = A.y + B.y;
	C.z = A.z + B.z;
	C.w = A.w + B.w;
	C.size = A.size;
	return C;
}


Vector operator-(const Vector& A, const Vector& B) {
	
	Vector C;
	
	// Subtract components
	C.x = A.x - B.x;
	C.y = A.y - B.y;
	C.z = A.z - B.z;
	C.w = A.w - B.w;
	C.size = A.size;
	return C;
}


std::ostream& operator<<(std::ostream& out, const Vector& A) {
	
	float com[] = {A.x, A.y, A.z, A.w};
	
	// Add to stream
	out << std::fixed << std::setprecision(2);
	out << "[";
	if (A.size != 0)
		out << com[0];
	for (int i=1; i<A.size; i++)
		out << ", " << com[i];
	out << "]";
	out << std::resetiosflags(std::ios_base::floatfield);
	out << std::setprecision(6);
	return out;
}


float& Vector::operator()(int i) {
	
	// Return correct component
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw "[Vector] Index out of bounds.";
	}
}


Vector Vector::crossProduct(const Vector &B) const {
	
	Vector C;
	
	// Calculate
	C.x = (y * B.z) - (z * B.y);
	C.y = (z * B.x) - (x * B.z);
	C.z = (x * B.y) - (y * B.x);
	C.w = 1.0;
	
	// Finish
	return C;
}


float Vector::dotProduct(const Vector &B) const {
	
	// Calculate
	if (size == 2)
		return x*B.x + y*B.y;
	else
		return x*B.x + y*B.y + z*B.z;
}


/**
 * @throws const_char* if index out of bounds.
 */
float Vector::get(int i) const {
	
	// Return correct component
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw "[Vector] Index out of bounds.";
	}
}


Vector Vector::getNormalized() const {
	
	float len;
	Vector C;
	
	// Divide by length
	len = this->length();
	if (len == 0.0) {
		C.x = 0.0;
		C.y = 0.0;
		C.z = 0.0;
		C.w = 1.0;
	}
	else {
		C.x = x / len;
		C.y = y / len;
		C.z = z / len;
		C.w = 1.0;
	}
	C.size = size;
	return C;
}


float Vector::length() const {
	
	// Return root of sum of squares
	if (size == 2)
		return sqrt(x*x + y*y);
	else
		return sqrt(x*x + y*y + z*z);
}


void Vector::set(float x, float y) {
	
	// Set components
	this->x = x;
	this->y = y;
	size = 2;
}


void Vector::set(float x, float y, float z) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = z;
	size = 3;
}


void Vector::set(float x, float y, float z, float w) {
	
	// Set components
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	size = 4;
}

