/*
 * Attachment.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Attachment.hpp"


/** Initializes the name of the attachment. */
Attachment::Attachment(const Tag &tag,
                       const string &type) : Attachable(tag) {
	
	// Initialize
	tag.get("name", name, false, false);
	location = -1;
	framebuffer = NULL;
	this->type = type;
}


/** Finds the first framebuffer above this node and enqueue it.
 * 
 * @throws NodeException if framebuffer cannot be found.
 */
void Attachment::associate() {
	
	// Find the framebuffer and enqueue it to be attached
	framebuffer = Framebuffer::find(this);
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
	framebuffer = Framebuffer::find(node);
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
	stream << " framebuffer='" << framebuffer->getHandle() << "'"
	       << " name='" << name << "'"
	       << " index='" << index << "'"
	       << " type='" << type << "'";
	return stream.str();
}

