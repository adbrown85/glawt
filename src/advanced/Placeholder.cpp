/*
 * Placeholder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Placeholder.hpp"


/** Initializes attributes. */
Placeholder::Placeholder(const Tag &tag) : Node(tag), Nameable(tag) {
	
	if (!hasName()) {
		NodeException e(tag);
		e << "[Placeholder] Placeholder must have name.";
		throw e;
	}
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


/** @return String made of the node's attributes. */
string Placeholder::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << getName() << "'";
	return stream.str();
}

