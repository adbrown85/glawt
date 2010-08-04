/*
 * Duplicate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Duplicate.hpp"


/** Initializes attributes.
 * 
 * @throws NodeException if already given children.
 */
Duplicate::Duplicate(const Tag &tag) : Node(tag) {
	
	// Name of group
	tag.get("of", of, true, true);
}


/** Find group and children. */
void Duplicate::associate() {
	
	// Check children are empty
	if (!children.empty()) {
		NodeException e(tag);
		e << "[Duplicate] Cannot have children.";
		throw e;
	}
	
	// Find group and children
	findGroup();
	findChildren();
}


/** Adds the group's children to the instance's children. */
void Duplicate::findChildren() {
	
	Node::iterator it;
	
	// Get children from group
	for (it=group->begin(); it!=group->end(); ++it) {
		addChild(*it);
	}
}


/** Finds the group named by <i>of</i>.
 * 
 * @throws NodeException if the group cannot be found.
 */
void Duplicate::findGroup() {
	
	// Find the group
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Duplicate] Could not find group with name '" << of << "'";
		throw e;
	}
}


/** Sets the duplicate as the parent of each of its children. */
void Duplicate::relink() {
	
	Node::iterator ni;
	
	// Make sure children's parents point to this instance
	for (ni=begin(); ni!=end(); ++ni) {
		(*ni)->setParent(this);
	}
}


/** @return Adds @e of attributes to description. */
string Duplicate::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " of='" << of << "'";
	return stream.str();
}



