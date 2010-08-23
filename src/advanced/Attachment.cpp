/*
 * Attachment.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Attachment.hpp"


/** Initialize attributes.
 * 
 * @throws NodeException if @e type is not "color" or "depth".
 */
Attachment::Attachment(const Tag &tag) : Attachable(tag), Nameable(tag) {
	
	// From tag
	if (!tag.get("type", type, false, true))
		type = "color";
	
	// Others
	location = -1;
	framebuffer = NULL;
	
	// Check
	if (type != "color" && type != "depth") {
		NodeException e(getTag());
		e << "[Attachment] Type must be color or depth.";
		throw e;
	}
}


/** Finds the first framebuffer above this node and enqueue it.
 * 
 * @throws NodeException if framebuffer cannot be found.
 */
void Attachment::associate() {
	
	// Find the framebuffer and enqueue it to be attached
	framebuffer = Scout<Framebuffer>::locate(getParent());
	if (framebuffer == NULL) {
		NodeException e(tag);
		e << "[Attachment] Could not find framebuffer.";
		throw e;
	}
	framebuffer->enqueue(type, this);
}


/** @return first attachment above another node with the correct name. */
Attachment* Attachment::find(Node *node, const string &name) {
	
	Framebuffer *framebuffer;
	Attachment *attachment;
	Node::iterator it;
	
	// First find framebuffer
	framebuffer = Scout<Framebuffer>::locate(node);
	if (framebuffer == NULL) {
		return NULL;
	}
	
	// Then look in framebuffer's children for it
	for (it=framebuffer->begin(); it!=framebuffer->end(); ++it) {
		attachment = dynamic_cast<Attachment*>(*it);
		if ((attachment != NULL) && (attachment->getName() == name)) {
			return attachment;
		}
	}
	return NULL;
}


/** @return string comprised of the object's name and attributes. */
string Attachment::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << Nameable::toString();
	stream << " framebuffer='" << framebuffer->getHandle() << "'";
	stream << " index='" << index << "'"
	       << " type='" << type << "'";
	return stream.str();
}

