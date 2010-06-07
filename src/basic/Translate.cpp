/*
 * Translate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Translate.hpp"


/** Creates a new %Translate from an XML tag.
 * 
 * @param tag XML tag with "x", "y", and "z" values.
 */
Translate::Translate(const Tag &tag) : Transformation(tag) {
	
	// Initialize
	tag.get("x", x, false);
	tag.get("y", y, false);
	tag.get("z", z, false);
}


/** Adds a vector to this translation. */
void Translate::add(const Vector &B) {
	
	// Add components
	x += B.x;
	y += B.y;
	z += B.z;
	fireEvent();
}


/** Performs the translation. */
void Translate::apply() {
	
	// Translate
	glPushMatrix();
	glTranslatef(x, y, z);
}


/** Finds a translate node above another. */
Translate* Translate::find(Node *node) {
	
	Node *curr;
	Translate *translate;
	
	curr = node->getParent();
	while (curr != NULL) {
		translate = dynamic_cast<Translate*>(curr);
		if (translate != NULL)
			return translate;
		curr = curr->getParent();
	}
	return NULL;
}


/** Add the translate to the matrix before sorting. */
void Translate::applyTo(Matrix &matrix) {
	
	Matrix T(1.0, 0.0, 0.0,  +x,
	         0.0, 1.0, 0.0,  +y,
	         0.0, 0.0, 1.0,  +z,
	         0.0, 0.0, 0.0, 1.0);
	
	// Add in translation
	matrix = matrix * T;
}


/** Restores transformation that was in effect before translate was applied. */
void Translate::remove() {
	
	// Restore
	glPopMatrix();
}


/** Sets "x", "y", or "z". */
bool Translate::setAttribute(pair<string,string> attribute) {
	
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
		fireEvent();
		return true;
	} else {
		return false;
	}
}


/** Forms a string from the object's attributes. */
string Translate::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " x='" << x << "'"
	       << " y='" << y << "'"
	       << " z='" << z << "'";
	return stream.str();
}

