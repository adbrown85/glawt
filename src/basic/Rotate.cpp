/*
 * Rotate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Rotate.hpp"


/** Creates a new %Rotate from an XML tag.
 * 
 * @param tag XML tag with "angle" and "axis" values.
 */
Rotate::Rotate(const Tag &tag) : Transformation(tag) {
	
	tag.get("angle", angle, true);
	tag.get("axis", axis, true);
	axis = normalize(axis);
	quaternion.set(angle, axis);
}


/** Performs the transformation. */
void Rotate::apply() {
	
	glPushMatrix();
	glRotatef(angle, axis.x, axis.y, axis.z);
}


void Rotate::applyTo(Matrix &matrix) {
	
	matrix = matrix * quaternion.getMatrix();
}


/** Restores state before transformation was applied. */
void Rotate::remove() {
	
	glPopMatrix();
}


/** Forms a string from the object's attributes. */
string Rotate::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " angle='" << angle << "'"
	       << " x='" << axis.x << "'"
	       << " y='" << axis.y << "'"
	       << " z='" << axis.z << "'";
	return stream.str();
}

