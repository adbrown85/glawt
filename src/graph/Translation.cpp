/*
 * Translation.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Translation.hpp"



Translation::Translation(float x,
                         float y,
                         float z) : Vector(x,y,z) {
	
	// Initialize
	className = "Translation";
}




/**
 * Adds a vector to this translation.
 */
void Translation::add(const Vector &B) {
	
	// Add components
	x += B.x;
	y += B.y;
	z += B.z;
}



/**
 * Performs the translation.
 */
void Translation::apply() {
	
	// Translate
	glPushMatrix();
	glTranslatef(x, y, z);
}



/**
 * Add the translation to the matrix before sorting.
 */
void Translation::sortByDepthBeg(Matrix &matrix) {
	
	Matrix transMatrix(1.0, 0.0, 0.0,  +x,
	                   0.0, 1.0, 0.0,  +y,
	                   0.0, 0.0, 1.0,  +z,
	                   0.0, 0.0, 0.0, 1.0);
	
	// Add in translation
	matrix = matrix * transMatrix;
}



/**
 * Remove the translation from the matrix after sorting.
 */
void Translation::sortByDepthEnd(Matrix &matrix) {
	
	Matrix transMatrix(1.0, 0.0, 0.0,  -x,
	                   0.0, 1.0, 0.0,  -y,
	                   0.0, 0.0, 1.0,  -z,
	                   0.0, 0.0, 0.0, 1.0);
	
	// Remove translation
	matrix = matrix * transMatrix;
}



/**
 * Prints the Translation with a small indent.
 */
void Translation::print() const {
	
	cout << "  " << toString() << endl;
}



/**
 * Restores transformation that was in effect before Translation was applied.
 */
void Translation::remove() {
	
	// Restore
	glPopMatrix();
}



string Translation::toString() const {
	
	stringstream stream;
	
	stream << Node::toString();
	stream << " x='" << x << "'"
	       << " y='" << y << "'"
	       << " z='" << z << "'";
	return stream.str();
}
