/*
 * Quaternion.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Quaternion.hpp"


Quaternion::Quaternion() {
	
	s = 1.0;
	v.set(0.0, 0.0, 0.0);
}


Quaternion::Quaternion(float angle, const Vector &axis) {
	
	set(angle, axis);
}


/** Returns a matrix representing the rotation. */
Matrix Quaternion::getMatrix() const {
	
	float xx2, yy2, zz2, xy2, xz2, yz2, sx2, sy2, sz2;
	Matrix C;
	
	// Calculate matrix
	xx2 = v.x * v.x * 2;
	yy2 = v.y * v.y * 2;
	zz2 = v.z * v.z * 2;
	xy2 = v.x * v.y * 2;
	xz2 = v.x * v.z * 2;
	yz2 = v.y * v.z * 2;
	sx2 = s * v.x * 2;
	sy2 = s * v.y * 2;
	sz2 = s * v.z * 2;
	C(0,0) = 1.0 - yy2 - zz2;
	C(0,1) = xy2 - sz2;
	C(0,2) = xz2 + sy2;
	C(1,0) = xy2 + sz2;
	C(1,1) = 1.0 - xx2 - zz2;
	C(1,2) = yz2 - sx2;
	C(2,0) = xz2 - sy2;
	C(2,1) = yz2 + sx2;
	C(2,2) = 1.0 - xx2 - yy2;
	
	// Finish
	return C;
}


void Quaternion::normalize() {
	
	float mag;

	// Divide by magnitude
	mag = sqrt(s*s + v.x*v.x + v.y*v.y + v.z*v.z);
	s /= mag;
	v /= mag;
}


Quaternion Quaternion::operator*(const Quaternion& B) {
	
	Quaternion C;
	
	// Calculate scalar and vector
	C.s = s * B.s - dot(v,B.v);
	C.v = (B.v * s) + (v * B.s) + cross(v,B.v);
	return C;
}


void Quaternion::print() {
	
	cout << "  " << toString() << endl;
}


void Quaternion::rotate(float angle, const Vector &axis) {
	
	Quaternion B(angle, axis);
	
	// Combine with current rotation
	*this = B * (*this);
}


void Quaternion::set(float angle, const Vector &axis) {
	
	float cosAngleHalved,
	      sinAngleHalved,
	      angleHalved,
	      angleHalvedInRadians;
	
	// Initialize
	angleHalved = angle * 0.5;
	angleHalvedInRadians = Numeric::toRadians(angleHalved);
	cosAngleHalved = cos(angleHalvedInRadians);
	sinAngleHalved = sin(angleHalvedInRadians);
	
	// Set
	s = cosAngleHalved;
	v = axis * sinAngleHalved;
	
	// Normalize
	normalize();
}


string Quaternion::toString() const {
	
	stringstream stream;
	
	// Make string
	stream << "Quaternion"
	       << " s='" << s << "'"
	       << " x='" << v.x << "'"
	       << " y='" << v.y << "'"
	       << " z='" << v.z << "'";
	return stream.str();
}

