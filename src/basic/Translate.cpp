/*
 * Translate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Translate.hpp"


/** Creates a new %Translate from an XML tag.
 * 
 * @param tag XML tag with "value", "x", "y", or "z" attributes.
 */
Translate::Translate(const Tag &tag) : Transformation(tag) {
	
	if (!tag.get("value", value, false)) {
		tag.get("x", value.x, false);
		tag.get("y", value.y, false);
		tag.get("z", value.z, false);
	}
	value.w = 1.0;
}


/** Adds a vector to this translation. */
void Translate::add(const Vector &B) {
	
	value.x += B.x;
	value.y += B.y;
	value.z += B.z;
	fireEvent();
}


/** Performs the translation. */
void Translate::apply() {
	
	glPushMatrix();
	glTranslatef(value.x, value.y, value.z);
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
	
	Matrix T(1.0, 0.0, 0.0,  +value.x,
	         0.0, 1.0, 0.0,  +value.y,
	         0.0, 0.0, 1.0,  +value.z,
	         0.0, 0.0, 0.0, 1.0);
	
	// Add in translation
	matrix = matrix * T;
}


/** Restores transformation that was in effect before translate was applied. */
void Translate::remove() {
	
	glPopMatrix();
}


/** Sets "x", "y", or "z" in value. */
bool Translate::setAttribute(pair<string,string> attribute) {
	
	bool changed=false;
	string key=Text::toLower(attribute.first);
	
	if (key == "x") {
		value.x = atof(attribute.second.c_str());
		changed = true;
	} else if (key == "y") {
		value.y = atof(attribute.second.c_str());
		changed = true;
	} else if (key == "z") {
		value.z = atof(attribute.second.c_str());
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
	stream << " x='" << value.x << "'"
	       << " y='" << value.y << "'"
	       << " z='" << value.z << "'";
	return stream.str();
}

