/*
 * Framebuffer.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"



Framebuffer::Framebuffer() {
	
	// Initialize
	className = "Framebuffer";
	this->handle = 0;
}



/**
 * Binds the %Framebuffer.
 */
void Framebuffer::apply() {
	
	// Bind
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
}



/**
 * Generates the %Framebuffer.
 */
void Framebuffer::finalize() {
	
	// Generate and bind
	glGenFramebuffers(1, &handle);
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
}



/**
 * Finds a %Framebuffer.
 * 
 * @param node
 *     Node to start looking.
 * @param
 *     Pointer to the %Framebuffer.
 */
void Framebuffer::find(Node *node,
                       Framebuffer *&pointer) {
	
	// Search
	node = node->parent;
	while (node != NULL) {
		pointer = dynamic_cast<Texture2D*>(node);
		if (pointer != NULL)
			break;
		node = node->parent;
	}
}



/**
 * Unbinds the %Framebuffer.
 */
void Framebuffer::remove() {
	
	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



/**
 * Forms a string from the framebuffer's attributes.
 */
string Framebuffer::toString() const {
	
	stringstream stream;
	
	stream << Node::toString()
	       << " han='" << handle << "'";
	return stream.str();
}

