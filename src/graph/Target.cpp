/*
 * Target.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"



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
	textureHandle = texture->getUnit();
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

