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
Scale::Scale(const Tag &tag) : Transform(tag) {
	
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
	fireEvent(NodeEvent(this, NodeEvent::MODIFY));
}


/** Performs the transformation. */
void Scale::apply() {
	
	glPushMatrix();
	glScalef(x, y, z);
}


void Scale::applyTo(Matrix &matrix) {
	
	Matrix T( x , 0.0, 0.0, 0.0,
	         0.0,  y , 0.0, 0.0,
	         0.0, 0.0,  z , 0.0,
	         0.0, 0.0, 0.0, 1.0);
	
	matrix = matrix * T;
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


/** Sets "x", "y", or "z". */
bool Scale::setAttribute(pair<string,string> attribute) {
	
	bool changed=false;
	string key=Text::toLower(attribute.first);
	
	if (key == "x") {
		x = atof(attribute.second.c_str());
		changed = true;
	} else if (key == "y") {
		y = atof(attribute.second.c_str());
		changed = true;
	} else if (key == "z") {
		z = atof(attribute.second.c_str());
		changed = true;
	}
	
	if (changed) {
		fireEvent(NodeEvent(this, NodeEvent::MODIFY));
		return true;
	} else {
		return false;
	}
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

