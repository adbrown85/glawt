/*
 * Framebuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
bool Framebuffer::active=false;


/** Initializes the chains in the framebuffer. */
Framebuffer::Framebuffer(const Tag &tag) : Applicable(tag) {
	
	// Initialize
	this->handle = 0;
	chains["color"] = Chain(GL_COLOR_ATTACHMENT0, getMaxColorAttachments());
}


/** Deletes the underlying OpenGL framebuffer object. */
Framebuffer::~Framebuffer() {
	
	glDeleteFramebuffers(1, &handle);
}


/** Activates all the color attachments using glDrawBuffers. */
void Framebuffer::activate() {
	
	Chain *chain;
	GLenum *buffers;
	GLsizei n;
	
	// Create the array
	chain = getChain("color");
	n = chain->attachables.size();
	if (n > getMaxDrawBuffers()) {
		n = getMaxDrawBuffers();
		cerr << tag.getLocation();
		cerr << "[Framebuffer] Only using first " << n
		     << " attachments." << endl;
	}
	buffers = new GLenum[n];
	
	// Fill it
	for (int i=0; i<n; ++i) {
		buffers[i] = GL_COLOR_ATTACHMENT0 + i;
	}
	
	// Pass it
	glDrawBuffers(n, buffers);
	
	// Finish
	delete[] buffers;
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


/** Queues an attachable item to be attached.
 * 
 * @param type Either @e color or @e depth.
 * @param item Item to be attached.
 * @throws NodeException if type not supported.
 * @throws NodeException if maximum attachments for a slot will be exceeded.
 * 
 * @todo Fix maximum check.
 */
void Framebuffer::attach(const string &type, Attachable *item) {
	
	Chain *chain;
	
	// Add to list in slot
	chain = getChain(type);
	chain->attachables.push_back(item);
	
	// Check if the maximum was exceeded
	if (chain->attachables.size() > chain->max) {
		NodeException e(tag);
		e << "[Framebuffer] Maximum amount of attachable items exceeded.";
		throw e;
	}
}


/** Attaches each chain of attachments. */
void Framebuffer::attach() {
	
	map<string,Chain>::iterator it;
	
	for (it=chains.begin(); it!=chains.end(); ++it) {
		attach(it->second);
	}
}


/** Attaches each attachment in a chain of attachments. */
void Framebuffer::attach(Chain &chain) {
	
	GLint index;
	list<Attachable*>::iterator it;
	
	index = 0;
	for (it=chain.attachables.begin(); it!=chain.attachables.end(); ++it) {
		(*it)->setIndex(index);
		(*it)->setLocation(chain.base + index);
		(*it)->attach();
		++index;
	}
}


/** Attaches all the attachments and checks if the framebuffer is complete.
 * 
 * @throws NodeException if maximum slots.
 */
void Framebuffer::finalize() {
	
	// Make sure the framebuffer is bound
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	
	// Attach
	attach();
	verify();
	activate();
	
	// Restore default framebuffer
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
Chain* Framebuffer::getChain(const string &name) {
	
	map<string,Chain>::iterator it;
	
	it = chains.find(name);
	if (it != chains.end()) {
		return &(it->second);
	} else {
		NodeException e(tag);
		e << "[Framebuffer] Unsupported attachment type '" << name << "'.";
		throw e;
	}
}


GLint Framebuffer::getMaxDrawBuffers() {
	
	GLint value;
	
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &value);
	return value;
}


GLint Framebuffer::getMaxColorAttachments() {
	
	GLint value;
	
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &value);
	return value;
}


/** Unbinds the %Framebuffer. */
void Framebuffer::remove() {
	
	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	active = false;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


/** Checks to make sure the framebuffer is complete.
 * 
 * @throws NodeException if framebuffer is not complete.
 */
void Framebuffer::verify() {
	
	// Check status
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		NodeException e(tag);
		e << "[Framebuffer] Needs attachments to be complete.";
		throw e;
	}
}


/** Forms a string from the object's attributes. */
string Framebuffer::toString() const {
	
	ostringstream stream;
	
	// Insert attributes
	stream << Node::toString()
	       << " handle='" << handle << "'";
	return stream.str();
}

