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
Renderbuffer::Renderbuffer(const Tag &tag) : Attachment(tag,"color") {
	
	string type, format;
	
	// Type
	tag.get("type", type);
	if (type == "color") {
		tag.get("format", format, false, true);
		if (format == "float") {
			setFormat(GL_RGBA32F);
		} else {
			setFormat(GL_RGBA);
		}
	} else if (type == "depth") {
		setFormat(GL_DEPTH_COMPONENT);
	} else {
		NodeException e(tag);
		e << "[Renderbuffer] Type not recognized.";
		throw e;
	}
	setType(type);
	
	// Size
	tag.get("size", size);
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


/** Adds @e size to the node's description. */
string Renderbuffer::toString() const {
	
	ostringstream stream;
	
	stream << Attachment::toString();
	stream << " size='" << size << "'";
	return stream.str();
}

