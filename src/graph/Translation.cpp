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
