/*
 * Framebuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
bool Framebuffer::active=false;


/** Initializes the slots in the framebuffer. */
Framebuffer::Framebuffer(const Tag &tag) : Applicable(tag) {
	
	FramebufferSlot slot;
	
	// Handle
	this->handle = 0;
	
	// Slots
	slot.base = GL_COLOR_ATTACHMENT0;
	slot.maximum = GL_MAX_COLOR_ATTACHMENTS;
	slots["color"] = slot;
}


/** Deletes the underlying OpenGL framebuffer object. */
Framebuffer::~Framebuffer() {
	
	// Delete the framebuffer
	glDeleteFramebuffers(1, &handle);
}


/** Queues an attachable item to be attached.
 * 
 * @param type Either @e color or @e depth.
 * @param item Item to be attached.
 * @throws NodeException if type not supported.
 * @throws NodeException if maximum attachments for a slot will be exceeded.
 */
void Framebuffer::add(const string &type, Attachable *item) {
	
	FramebufferSlot *slot;
	
	// Add to list in slot
	slot = getSlot(type);
	slot->attachables.push_back(item);
	
	// Check if the maximum was exceeded
	if (slot->attachables.size() > slot->maximum) {
		NodeException e(tag);
		e << "[Framebuffer] Maximum amount of attachable items exceeded.";
		throw e;
	}
}


/** Binds and clears the framebuffer.
 * 
 * @todo Move <i>clear</i> to another node.
 */
void Framebuffer::apply() {
	
	// Bind
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	active = true;
	
	// Clear
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


/** Generates the underlying OpenGL framebuffer object. */
void Framebuffer::associate() {
	
	glGenFramebuffers(1, &handle);
}


/** Attaches all the attachments and checks if the framebuffer is complete.
 * 
 * @throws NodeException if maximum slots.
 * @throws NodeException if framebuffer is not complete.
 */
void Framebuffer::finalize() {
	
	map<string,FramebufferSlot>::iterator si;
	FramebufferSlot *slot;
	list<Attachable*> *attachables;
	GLint index;
	list<Attachable*>::iterator ai;
	
	// Make sure the framebuffer is bound
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	
	// Attach each attachable in each slot
	for (si=slots.begin(); si!=slots.end(); ++si) {
		slot = &(si->second);
		attachables = &(slot->attachables);
		index = 0;
		for (ai=attachables->begin(); ai!=attachables->end(); ++ai) {
			(*ai)->setIndex(index);
			(*ai)->setLocation(slot->base + index);
			(*ai)->attach();
			++index;
		}
	}
	
	// Check status
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		NodeException e(tag);
		e << "[Framebuffer] Needs attachments to be complete.";
		throw e;
	}
	
	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


/** Finds a %Framebuffer above a node.
 * 
 * @param node Node to start looking.
 * @return pointer Pointer to the %Framebuffer.
 */
Framebuffer* Framebuffer::find(Node *node) {
	
	Framebuffer *ptr;
	
	// Search
	node = node->getParent();
	while (node != NULL) {
		ptr = dynamic_cast<Framebuffer*>(node);
		if (ptr != NULL)
			return ptr;
		node = node->getParent();
	}
	return NULL;
}


/** @return Structure holding state for one type of attachment. 
 * 
 * @throws NodeException if type not supported.
 */
FramebufferSlot* Framebuffer::getSlot(const string &name) {
	
	map<string,FramebufferSlot>::iterator it;
	
	it = slots.find(name);
	if (it != slots.end()) {
		return &(it->second);
	} else {
		NodeException e(tag);
		e << "[Framebuffer] Unsupported attachment type '" << name << "'.";
		throw e;
	}
}


/** Unbinds the %Framebuffer. */
void Framebuffer::remove() {
	
	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	active = false;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


/** Forms a string from the object's attributes. */
string Framebuffer::toString() const {
	
	ostringstream stream;
	
	// Insert attributes
	stream << Node::toString()
	       << " handle='" << handle << "'";
	return stream.str();
}

