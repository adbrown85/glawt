/*
 * Texture2D.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture2D.hpp"


/** Initializes @e image and @e size. */
Texture2D::Texture2D(const Tag &tag) : Texture(GL_TEXTURE_2D,tag) {
	
	string text;
	
	// Size
	if (!tag.get("size", size, false)) {
		size = CANVAS_WIDTH;
	}
	
	// Format
	if (tag.get("format", text, false, true)) {
		if (text == "float") {
			format = GL_RGBA16F;
		} else if (text == "rgba") {
			format = GL_RGBA;
		} else if (text == "rgb") {
			format = GL_RGB;
		} else {
			NodeException e(tag);
			e << "[Texture2D] Unrecognized format.";
			throw e;
		}
	} else {
		format = GL_RGBA;
	}
}


/** Loads or just allocates a blank texture. */
void Texture2D::finalize() {
	
	void *pixels;
	Image *image;
	GLenum pixelFormat;
	
	// Load the image or specify defaults
	if (hasFilename()) {
		image = ImageFactory::create(getFilename());
		format = image->getFormat();
		size = image->getWidth();
		pixels = image->getData();
	} else {
		image = NULL;
		format = this->format;
		size = this->size;
		pixels = NULL;
	}
	
	// Specify pixel format
	switch (format) {
	case GL_RGB: pixelFormat = GL_RGB; break;
	default: pixelFormat = GL_RGBA; break;
	}
	
	// Create the texture
	glActiveTexture(GL_TEXTURE0 + getUnit());
	glBindTexture(GL_TEXTURE_2D, getHandle());
	glTexImage2D(GL_TEXTURE_2D,                   // target
	             0,                               // level
	             format,                          // internalFormat
	             size,                            // width
	             size,                            // height
	             0,                               // border
	             pixelFormat,                     // format
	             GL_UNSIGNED_BYTE,                // type
	             pixels);                         // pixels
	
	// Set parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	// Cleanup
	if (image != NULL)
		delete image;
}


/** How much memory the texture uses if uncompressed. */
GLint Texture2D::getRawFootprint() const {
	
	switch (format) {
	case GL_RGB:
		return size * size * 4;
	case GL_RGBA:
		return size * size * 3;
	case GL_RGBA16F:
		return size * size * 4 * 2;
	}
}


/** Forms a string from the object's attributes. */
string Texture2D::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Texture::toString();
	stream << " size='" << size << "'";
	stream << " format='";
	switch (format) {
	case GL_RGB:     stream << "rgb";   break;
	case GL_RGBA:    stream << "rgba";  break;
	case GL_RGBA16F: stream << "float"; break;
	}
	stream << "'";
	return stream.str();
}


/** Finds a %Texture2D with a specific name.
 * 
 * @param node Node to start looking.
 * @param name Name of the node as specified by the user.
 */
Texture2D* Texture2D::find(Node *node, const string &name) {
	
	Texture2D *texture2D;
	
	// Search
	node = node->getParent();
	while (node != NULL) {
		texture2D = dynamic_cast<Texture2D*>(node);
		if ((texture2D != NULL) && (texture2D->getName() == name)) {
			return texture2D;
		}
		node = node->getParent();
	}
	return NULL;
}

