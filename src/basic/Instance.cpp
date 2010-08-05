/*
 * Instance.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"


/** Initialize attributes. */
Instance::Instance(const Tag &tag) : Node(tag) {
	
	Tag linkTag;
	
	// Name of group
	tag.get("of", of, true, true);
	if (!tag.get("selectable", selectable, false)) {
		selectable = false;
	}
	
	// Create link
	linkTag.setName("link");
	linkTag.setFilename(tag.getFilename());
	linkTag.setLine(tag.getLine());
	linkTag["to"] = of;
	link = new Link(linkTag);
	addChild(link);
}


/** Establishes the link. */
void Instance::associate() {
	
	link->establish();
}


/** Relinks all the children of the link. */
void Instance::finalize() {
	
	link->relink();
}


/** @return String made from the node's attributes. */
string Instance::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " of='" << of << "'"
	       << " selectable='" << (selectable?'T':'F') << "'";
	return stream.str();
}

