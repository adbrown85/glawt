/*
 * Renderbuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Renderbuffer.hpp"


/** Initializes the @e type, @e format, and @e size of the renderbuffer.
 * 
 * @throws NodeException if @e type not recognized.
 */
Renderbuffer::Renderbuffer(const Tag &tag) : Attachment(tag) {
	
	string format;
	
	// Type
	if (getType() == "color") {
		tag.get("format", format, false, true);
		if (format == "float") {
			setFormat(GL_RGBA32F);
		} else {
			setFormat(GL_RGBA);
		}
	} else {
		setFormat(GL_DEPTH_COMPONENT);
	}
	
	// Size
	if (!tag.get("size", size, false)) {
		size = CANVAS_WIDTH;
	}
}


/** Deletes the underlying OpenGL renderbuffer object. */
Renderbuffer::~Renderbuffer() {
	
	glDeleteRenderbuffers(1, &handle);
}


/** Creates an underlying OpenGL renderbuffer object. */
void Renderbuffer::associate() {
	
	// Generate
	glGenRenderbuffers(1, &handle);
	
	// Find framebuffer and enqueue
	Attachment::associate();
}


/** Creates storage for the renderbuffer and attaches it to the framebuffer. */
void Renderbuffer::attach() {
	
	// Bind
	glBindRenderbuffer(GL_RENDERBUFFER, handle);
	
	// Create the storage
	glRenderbufferStorage(GL_RENDERBUFFER,                // target
	                      format,                         // internalformat
	                      size,                           // width
	                      size);                          // height
	
	// Attach to framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,             // target
	                          getLocation(),              // attachment
	                          GL_RENDERBUFFER,            // renderbuffertarget
	                          handle);                    // renderbuffer
}


/** Retrieves a value from the renderbuffer at @e x, @e y.*/
Vector Renderbuffer::read(int x, int y) const {
	
	GLfloat pixels[4];
	Vector result;
	
	// Bind
	glBindFramebuffer(GL_READ_FRAMEBUFFER, getFramebuffer()->getHandle());
	glBindRenderbuffer(GL_RENDERBUFFER, handle);
	
	// Read
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, pixels);
	result.set(pixels[0], pixels[1], pixels[2], pixels[3]);
	
	// Unbind
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	
	// Finish
	return result;
}


/** Adds @e size to the node's description. */
string Renderbuffer::toString() const {
	
	ostringstream stream;
	
	stream << Attachment::toString();
	stream << " size='" << size << "'";
	return stream.str();
}

