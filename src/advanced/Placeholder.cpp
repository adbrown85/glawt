/*
 * Placeholder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Placeholder.hpp"


/** Initializes attributes. */
Placeholder::Placeholder(const Tag &tag) : Node(tag) {
	
	// Name
	tag.get("name", name, true, false);
}


/** Makes sure the placeholder is in a group. */
void Placeholder::associate() {
	
	Group *group;
	
	// Look for group
	group = Group::find(this);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Placeholder] Placeholder needs to be in group.";
		throw e;
	}
}


/** Sets the %Placeholder's child.
 * 
 * Use NULL to clear.
 */
void Placeholder::setChild(Node *node) {
	
	// Store child or clear
	if (node != NULL) {
		children[0] = node;
	} else {
		children.clear();
	}
}


string Placeholder::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << name << "'";
	return stream.str();
}

