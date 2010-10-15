/*
 * Replacement.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Replacement.hpp"


/** Initialize attributes. */
Replacement::Replacement(const Tag &tag) : Node(tag) {
	
	// Retrieve from tag
	tag.get("of", of, true, true);
}


/** @return String made from the node's attributes. */
string Replacement::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " of='" << of << "'";
	return stream.str();
}

