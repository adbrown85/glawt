/*
 * Scale.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Scale.hpp"


/** Creates a new %Scale from an XML tag.
 * 
 * @param tag XML tag with "x", "y", and "z" values.
 */
Scale::Scale(const Tag &tag) : Transformation(tag) {
	
	// Values
	if (tag.get("value", value, false)) {
		x = value;
		y = value;
		z = value;
	} else {
		if (!tag.get("x", x, false))
			x = 1.0f;
		if (!tag.get("y", y, false))
			y = 1.0f;
		if (!tag.get("z", z, false))
			z = 1.0f;
	}
}


/** Adds a vector to this scale. */
void Scale::add(const Vector &B) {
	
	// Add components
	x += B.x;
	y += B.y;
	z += B.z;
	fireEvent();
}


/** Performs the transformation. */
void Scale::apply() {
	
	glPushMatrix();
	glScalef(x, y, z);
}


Scale* Scale::find(Node *node) {
	
	Scale *scale;
	
	node = node->getParent();
	while (node != NULL) {
		scale = dynamic_cast<Scale*>(node);
		if (scale != NULL) {
			return scale;
		}
		node = node->getParent();
	}
	return NULL;
}


/** Restores state before transformation was applied. */
void Scale::remove() {
	
	glPopMatrix();
}


/** Forms a string from the object's attributes. */
string Scale::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " x='" << x << "'"
	       << " y='" << y << "'"
	       << " z='" << z << "'";
	return stream.str();
}

