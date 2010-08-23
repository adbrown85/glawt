/*
 * Group.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Group.hpp"


/** Initializes attributes.
 * 
 * @throws NodeException if a name is not specified.
 */
Group::Group(const Tag &tag) : Node(tag), Nameable(tag) {
	
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

