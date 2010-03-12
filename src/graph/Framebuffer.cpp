/*
 * Framebuffer.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
bool Framebuffer::active=false;


/**
 * Creates a new %Framebuffer.
 */
Framebuffer::Framebuffer() {
	
	// Initialize
	className = "Framebuffer";
	this->handle = 0;
}


/**
 * Creates a new %Framebuffer from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Framebuffer::Framebuffer(const Tag &tag) {
	
	// Initialize
	className = "Framebuffer";
	this->handle = 0;
}


/**
 * Deletes the %Framebuffer.
 */
Framebuffer::~Framebuffer() {
	
	// Delete the framebuffer
	glDeleteFramebuffers(1, &handle);
}


/**
 * Binds the %Framebuffer.
 */
void Framebuffer::apply() {
	
	// Bind
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	active = true;
	
	// Clear
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


/**
 * Generates the %Framebuffer in OpenGL and binds it.
 */
void Framebuffer::associate() {
	
	// Generate and bind
	glGenFramebuffers(1, &handle);
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
}


/**
 * Finds a %Framebuffer.
 * 
 * @param node
 *     Node to start looking.
 * @param pointer
 *     Pointer to the %Framebuffer.
 */
void Framebuffer::find(Node *node,
                       Framebuffer *&pointer) {
	
	// Search
	node = node->getParent();
	while (node != NULL) {
		pointer = dynamic_cast<Framebuffer*>(node);
		if (pointer != NULL)
			break;
		node = node->getParent();
	}
}


/**
 * Unbinds the %Framebuffer.
 */
void Framebuffer::remove() {
	
	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	active = false;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


/**
 * Forms a string from the framebuffer's attributes.
 */
string Framebuffer::toString() const {
	
	ostringstream stream;
	
	// Insert attributes
	stream << Node::toString()
	       << " handle='" << handle << "'";
	return stream.str();
}

