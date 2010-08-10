/*
 * Branch.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Branch.hpp"


/** Initializes attributes.
 * 
 * @throws NodeException if not given a name.
 */
Branch::Branch(const Tag &tag) : Node(tag), Nameable(tag) {
	
	// Follow
	follow = true;
	
	// Name
	if (!hasName()) {
		NodeException e(getTag());
		e << "[Branch] Must have a name.";
		throw e;
	}
}


/** @return String comprised of the node's attributes. */
string Branch::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << getName() << "'"
	       << " follow='" << (follow?'T':'F') << "'";
	return stream.str();
}

