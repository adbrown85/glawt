/*
 * Link.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Link.hpp"


/** Initialize attributes. */
Link::Link(const Tag &tag) : Node(tag) {
	
	tag.get("to", to, true, true);
}


/** Finds the group and adds its children. 
 * 
 * @throws NodeException if the group cannot be found.
 */
void Link::establish() {
	
	Node::iterator it;
	
	// Find the group
	group = Group::find(this, to);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Link] Could not find group with name '" << to << "'";
		throw e;
	}
	
	// Get children from group
	for (it=group->begin(); it!=group->end(); ++it) {
		addChild(*it);
	}
}


/** Sets the link as the parent of each of its children. */
void Link::relink() {
	
	Node::iterator ni;
	
	// Make sure children's parents point to this link
	for (ni=begin(); ni!=end(); ++ni) {
		(*ni)->setParent(this);
	}
}


/** @return Adds @e of attributes to description. */
string Link::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " to='" << to << "'"
	       << " children='" << children.size() << "'";
	return stream.str();
}

