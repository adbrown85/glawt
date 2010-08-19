/*
 * Screen.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Screen.hpp"


/** Clears the framebuffer pointer. */
Screen::Screen(const Tag &tag) : Node(tag) {
	
	framebuffer = NULL;
}


/** Finds a Framebuffer ancestor.
 * 
 * @throws NodeException if no Framebuffer ancestor found.
 */
void Screen::associate() {
	
	framebuffer = Scout<Framebuffer>::locate(getParent());
	if (framebuffer == NULL) {
		NodeException e(tag);
		e << "[Framebuffer] Could not find framebuffer ancestor.";
		throw e;
	}
}


/** Binds the default framebuffer. */
void Screen::apply() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


/** Restores the previous framebuffer. */
void Screen::remove() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->getHandle());
}

