/*
 * Vector.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Vector.hpp"


/** Four-component vector initialized to all zeroes (except w=1.0). */
Vector::Vector() {
	
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
	size = 4;
}


/** Four-component vector initialized to one value. */
Vector::Vector(float value) {
	
	x = value;
	y = value;
	z = value;
	w = value;
	size = 4;
}


/** Two-component vector. */
Vector::Vector(float x, float y) {
	
	this->x = x;
	this->y = y;
	this->z = 0.0;
	this->w = 1.0;
	size = 2;
}


/** Three-component vector. */
Vector::Vector(float x, float y, float z) {
	
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1.0;
	size = 3;
}


/** Four-component vector. */
Vector::Vector(float x, float y, float z, float w) {
	
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	size = 4;
}


Vector& Vector::operator=(const Vector &B) {
	
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


Vector& Vector::operator+=(const Vector &B) {
	
	// Add components
	x += B.x;
	y += B.y;
	z += B.z;
	w += B.w;
	return *this;
}


Vector& Vector::operator-=(const Vector &B) {
	
	// Subtract components
	x -= B.x;
	y -= B.y;
	z -= B.z;
	w -= B.w;
	return *this;
}


Vector& Vector::operator*=(const Vector &B) {
	
	// Multiply components
	x *= B.x;
	y *= B.y;
	z *= B.z;
	w *= B.w;
	return *this;
}


Vector& Vector::operator/=(const Vector &B) {
	
	// Multiply components
	x /= B.x;
	y /= B.y;
	z /= B.z;
	w /= B.w;
	return *this;
}


Vector& Vector::operator+=(float b) {
	
	// Add components
	x += b;
	y += b;
	z += b;
	w += b;
	return *this;
}


Vector& Vector::operator-=(float b) {
	
	// Subtract components
	x += b;
	y += b;
	z += b;
	w += b;
	return *this;
}


Vector& Vector::operator*=(float b) {
	
	// Multiple components
	x *= b;
	y *= b;
	z *= b;
	w *= b;
	return *this;
}


Vector& Vector::operator/=(float b) {
	
	float bInv=1/b;
	
	// Multiple components
	x *= bInv;
	y *= bInv;
	z *= bInv;
	w *= bInv;
	return *this;
}


bool operator==(const Vector &A, const Vector &B) {
	
	return (A.x==B.x) && (A.y==B.y) && (A.z==B.z) && (A.w==B.w);
}


Vector operator+(const Vector &A, const Vector &B) {
	
	Vector C;
	
	// Add components
	C.x = A.x + B.x;
	C.y = A.y + B.y;
	C.z = A.z + B.z;
	C.w = A.w + B.w;
	C.size = A.size;
	return C;
}


Vector operator-(const Vector &A, const Vector &B) {
	
	Vector C;
	
	// Subtract components
	C.x = A.x - B.x;
	C.y = A.y - B.y;
	C.z = A.z - B.z;
	C.w = A.w - B.w;
	C.size = A.size;
	return C;
}


Vector operator*(const Vector &A, const Vector &B) {
	
	Vector C;
	
	// Multiply components
	C.x = A.x * B.x;
	C.y = A.y * B.y;
	C.z = A.z * B.z;
	C.w = A.w * B.w;
	C.size = A.size;
	return C;
}


Vector operator/(const Vector &A, const Vector &B) {
	
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


Vector operator+(const Vector &A, float b) {
	
	return Vector(A.x+b, A.y+b, A.z+b, A.w+b);
}


Vector operator-(const Vector &A, float b) {
	
	return Vector(A.x-b, A.y-b, A.z-b, A.w-b);
}


Vector operator*(const Vector &A, float b) {
	
	Vector C;
	
	// Multiply components
	C.x = A.x * b;
	C.y = A.y * b;
	C.z = A.z * b;
	C.w = A.w * b;
	C.size = A.size;
	return C;
}


Vector operator/(const Vector &A, float b) {
	
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


ostream& operator<<(ostream &out, const Vector &A) {
	
	float com[] = {A.x, A.y, A.z, A.w};
	
	// Add to stream
	out << fixed << setprecision(2);
	out << "[";
	if (A.size != 0)
		out << com[0];
	for (int i=1; i<A.size; i++)
		out << ", " << com[i];
	out << "]";
	out << resetiosflags(ios_base::floatfield);
	out << setprecision(6);
	return out;
}


/** @throws Exception if the index is out of bounds. */
float& Vector::operator[](int i) {
	
	// Return correct component
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default:
			throw Exception("[Vector] Index out of bounds.");
	}
}


/** @throws Exception if the index is out of bounds. */
float Vector::operator[](int i) const {
	
	// Return correct component
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default:
			throw Exception("[Vector] Index out of bounds.");
	}
}


/** @return vector perpendicular to the plane formed by two vectors. */
Vector cross(const Vector &A, const Vector &B) {
	
	Vector C;
	
	// Calculate
	C.x = (A.y * B.z) - (A.z * B.y);
	C.y = (A.z * B.x) - (A.x * B.z);
	C.z = (A.x * B.y) - (A.y * B.x);
	C.w = 1.0;
	return C;
}


/** @return projection of one vector onto another. */
float dot(const Vector &A, const Vector &B) {
	
	// Calculate
	if (A.size == 2)
		return A.x*B.x + A.y*B.y;
	else
		return A.x*B.x + A.y*B.y + A.z*B.z;
}


/** @throws Exception if index out of bounds. */
float Vector::get(int i) const {
	
	// Return correct component
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default:
			throw Exception("[Vector] Index out of bounds.");
	}
}


/** @return length of the vector. */
float Vector::length() const {
	
	// Return root of sum of squares
	if (size == 2)
		return sqrt(x*x + y*y);
	else
		return sqrt(x*x + y*y + z*z);
}


/** @return component-wise maximum of the two vectors */
Vector max(const Vector &A, const Vector &B) {
	
	return Vector(max(A.x,B.x), max(A.y,B.y), max(A.z,B.z), max(A.w,B.w));
}


/** @return component-wise minimum of the two vectors */
Vector min(const Vector &A, const Vector &B) {
	
	return Vector(min(A.x,B.x), min(A.y,B.y), min(A.z,B.z), min(A.w,B.w));
}


/** @return Unit length version of the vector. */
Vector normalize(Vector vector) {
	
	float len;
	
	// Divide by length
	len = vector.length();
	if (len == 0.0) {
		vector = Vector();
	} else {
		vector /= len;
		vector.w = 1.0;
	}
	return vector;
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


void Vector::toArray(float array[4]) {
	
	for (int i=0; i<4; ++i) {
		array[i] = get(i);
	}
}

