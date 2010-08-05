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


/** @throws NodeException if the placeholder has children.*/
void Placeholder::check() {
	
	if (!children.empty()) {
		NodeException e(tag);
		e << "[Placeholder] Placeholder should not have children.";
		throw e;
	}
}


/** Copies the children of another node. */
void Placeholder::mimic(Node *node) {
	
	Node::iterator it;
	
	for (it=node->begin(); it!=node->end(); ++it) {
		addChild(*it);
	}
}


string Placeholder::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << name << "'";
	return stream.str();
}

