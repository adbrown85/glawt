/*
 * Texture3D.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture3D.hpp"


/** Creates the texture and underlying dataset. */
Texture3D::Texture3D(const Tag &tag) : Texture(GL_TEXTURE_3D, tag) {
	
	dataset = new Dataset(filename);
}


/** Deletes the underlying dataset object. */
Texture3D::~Texture3D() {
	
	delete dataset;
}


/** Loads the dataset into texture memory. */
void Texture3D::finalize() {
	
	// Load the dataset
	dataset->load();
	
	// Bind the texture to the right unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_3D, handle);
	
	// Pass the texture to OpenGL
	glTexImage3D(GL_TEXTURE_3D,           // Target
	             0,                       // Mipmap level
	             GL_LUMINANCE,            // Internal format
	             dataset->getWidth(),     // Width
	             dataset->getHeight(),    // Height
	             dataset->getDepth(),     // Depth
	             0,                       // Border
	             GL_LUMINANCE,            // Format
	             dataset->getType(),      // Type
	             dataset->getData());     // Data
	
	// Set parameters
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
}


/** Finds a 3D texture above a node. */
Texture3D* Texture3D::find(Node *node, const string &name) {
	
	Texture3D *texture3d;
	
	while (node != NULL) {
		texture3d = dynamic_cast<Texture3D*>(node);
		if (texture3d != NULL && texture3d->getName()==name) {
			return texture3d;
		} else {
			node = node->getParent();
		}
	}
	return NULL;
}

