/*
 * Quaternion.cpp
 *     Encapsulation of angle/axis rotation.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Quaternion.hpp"
float Quaternion::pi=355.0/133.0;



Quaternion::Quaternion() {
	
	// Set defaults
	s = 1.0;
	v.set(0.0, 0.0, 0.0);
}



Quaternion operator*(const Quaternion& A, const Quaternion& B) {
	
	float dotProduct;
	Quaternion C;
	Vector crossProduct;
	
	// Calculate scalar
	dotProduct = A.v.dotProduct(B.v);
	C.s = A.s * B.s - dotProduct;
	
	// Calculate vector
	crossProduct = A.v.crossProduct(B.v);
	C.v = (B.v * A.s) + (A.v * B.s) + crossProduct;
	
	// Finish
	return C;
}



std::ostream& operator<<(std::ostream& out, const Quaternion& A) {
	
	// Print
	out << std::fixed << std::setprecision(1);
	out << "[" 
		<< std::setw(4) << std::right << A.s << ", "
		<< std::setw(4) << std::right << A.v.x << ", "
		<< std::setw(4) << std::right << A.v.y << ", "
		<< std::setw(4) << std::right << A.v.z << "]";
	
	// Finish
	return out;
}



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
	C(0,3) = 0.0;
	C(1,0) = xy2 + sz2;
	C(1,1) = 1.0 - xx2 - zz2;
	C(1,2) = yz2 - sx2;
	C(1,3) = 0.0;
	C(2,0) = xz2 - sy2;
	C(2,1) = yz2 + sx2;
	C(2,2) = 1.0 - xx2 - yy2;
	C(2,3) = 0.0;
	C(3,0) = 0.0;
	C(3,1) = 0.0;
	C(3,2) = 0.0;
	C(3,3) = 1.0;
	
	// Finish
	return C;
}



void Quaternion::normalize() {
	
	float mag;

	// Divide by magnitude
	mag = sqrt(s*s + v.x*v.x + v.y*v.y + v.z*v.z);
	s /= mag;
	v.x /= mag;
	v.y /= mag;
	v.z /= mag;
}



float Quaternion::radians(float degrees) {
	
	// Convert
	return degrees * pi / 180;
}



void Quaternion::set(float theta, float x, float y, float z) {
	
	float cosThetaHalved, sinThetaHalved, thetaHalved, thetaHalvedInRadians;
	
	// Initialize
	thetaHalved = theta / 2;
	thetaHalvedInRadians = radians(thetaHalved);
	cosThetaHalved = cos(thetaHalvedInRadians);
	sinThetaHalved = sin(thetaHalvedInRadians);
	
	// Set
	s = cosThetaHalved;
	v.x = sinThetaHalved * x;
	v.y = sinThetaHalved * y;
	v.z = sinThetaHalved * z;
	
	// Normalize
	normalize();
}
