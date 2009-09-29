/*
 * Target.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"



/**
 * Creates a new %Target linked to a %Texture2D.
 * 
 * @param link
 *     Name of the %Texture2D object.
 */
Target::Target(string link) {
	
	// Initialize
	className = "Target";
	this->link = link;
}



/**
 * Creates a new %Target from an XML tag.
 */
Target::Target(const Tag &tag) {
	
	// Initialize
	className = "Target";
	tag.get("link", link);
}



/**
 * Finds the texture to use for the color buffer.
 */
void Target::associate() {
	
	Framebuffer *framebuffer;
	Texture2D *texture;
	
	// Find the framebuffer
	Framebuffer::find(this, framebuffer);
	if (framebuffer == NULL)
		throw "[Gander,Target] Could not find framebuffer.";
	framebufferHandle = framebuffer->getHandle();
	
	// Find the texture
	Texture2D::find(this, texture, link);
	if (texture == NULL)
		throw "[Gander,Target] Could not find texture with correct name.";
	textureHandle = texture->getHandle();
	size = texture->getSize();
}



/**
 * Attaches the target to the %Framebuffer.
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
		throw "[Gander,Target] Framebuffer is not complete!";
}



/**
 * Forms a string from the Target's attributes.
 */
string Target::toString() const {
	
	stringstream stream;
	
	stream << Node::toString()
	       << " size='" << size << "'"
	       << " link='" << link << "'"
	       << " text='" << textureHandle << "'"
	       << " fram='" << framebufferHandle << "'";
	return stream.str();
}

