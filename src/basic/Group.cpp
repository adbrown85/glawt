/*
 * Group.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Group.hpp"


/** Initializes attributes.
 * 
 * @throw NodeException if a name is not specified.
 */
Group::Group(const Tag &tag) : Node(tag), Nameable(tag) {
	
}


/** Validates the node was created correctly. */
void Group::verify() {
	
	if (!hasName()) {
		NodeException e(getTag());
		e << "[Group] Must have name.";
		throw e;
	}
}


/** @return String comprised of the node's attributes. */
string Group::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << Nameable::toString();
	return stream.str();
}

