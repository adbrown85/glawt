/*
 * Texture2D.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture2D.hpp"


/** Initializes @e image and @e size. */
Texture2D::Texture2D(const Tag &tag) : Texture(GL_TEXTURE_2D,tag) {
	
	// Initialize
	this->image = NULL;
	tag.get("size", size, false);
}


/** Generates the texture.
 * 
 * Is done here rather than @c finalize() because other nodes might need to get 
 * the texture's handle.
 */
void Texture2D::associate() {
	
	// Find unit
	Texture::associate();
	
	// Generate
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &handle);
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


/** Loads or just allocates a blank texture. */
void Texture2D::finalize() {
	
	void *pixels;
	
	// Load the image or specify defaults
	if (!filename.empty()) {
		image = new Image(filename);
		format = image->getFormat();
		size = image->getWidth();
		pixels = image->getData();
	} else {
		format = GL_RGBA;
		size = this->size;
		pixels = NULL;
	}
	
	// Create the texture
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D,                   // target
	             0,                               // level
	             format,                          // internalFormat
	             size,                            // width
	             size,                            // height
	             0,                               // border
	             format,                          // format
	             GL_UNSIGNED_BYTE,                // type
	             pixels);                         // pixels
	
	// Set parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


/** How much memory the texture uses if uncompressed. */
GLint Texture2D::getRawFootprint() const {
	
	switch (format) {
	case GL_RGB:
		return size * size * 4;
	case GL_RGBA:
		return size * size * 3;
	}
}


/** Forms a string from the object's attributes. */
string Texture2D::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Texture::toString();
	stream << " size='" << size << "'";
	return stream.str();
}

