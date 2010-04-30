/*
 * Target.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"


/**
 * Creates a new %Target from an XML tag.
 * 
 * @param XML tag with "link" attribute.
 */
Target::Target(const Tag &tag) : 
               Node("Target") {
	
	// Initialize
	className = "Target";
	tag.get("link", link, true, false);
}


/**
 * Finds the texture to use for the color buffer.
 * 
 * @throws const_char* if cannot find framebuffer node.
 * @throws const_char* if cannot find texture with correct name.
 */
void Target::associate() {
	
	Framebuffer *framebuffer;
	Texture2D *texture;
	
	// Find the framebuffer
	Framebuffer::find(this, framebuffer);
	if (framebuffer == NULL)
		throw "[Target] Could not find framebuffer.";
	framebufferHandle = framebuffer->getHandle();
	
	// Find the texture
	Texture2D::find(this, texture, link);
	if (texture == NULL) {
		ostringstream msg;
		msg << "[Target] Could not find texture with name '" << link
		    << "'.";
		throw msg.str().c_str();
	}
	textureHandle = texture->getHandle();
	size = texture->getSize();
}


/**
 * Attaches the target to the Framebuffer.
 * 
 * @throws const_char* if Framebuffer is not complete.
 */
void Target::finalize() {
	
	// Bind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
	
	// Attach the texture
	glFramebufferTexture2D(GL_FRAMEBUFFER,
	                       GL_COLOR_ATTACHMENT0,
	                       GL_TEXTURE_2D,
	                       textureHandle,
	                       0);
	
	// Check status
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw "[Target] Framebuffer is not complete!";
}


/**
 * Forms a string from the Target's attributes.
 */
string Target::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString()
	       << " size='" << size << "'"
	       << " link='" << link << "'"
	       << " text='" << textureHandle << "'"
	       << " fram='" << framebufferHandle << "'";
	return stream.str();
}

