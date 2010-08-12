/*
 * Texture3D.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture3D.hpp"


/** Creates the texture and underlying dataset. */
Texture3D::Texture3D(const Tag &tag) : Texture(GL_TEXTURE_3D, tag) {
	
	dataset = new Dataset(getFilename());
	if (!tag.get("compress", compress, false)) {
		compress = false;
	}
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
	glActiveTexture(GL_TEXTURE0 + getUnit());
	glBindTexture(GL_TEXTURE_3D, getHandle());
	
	// Pass the texture to OpenGL
	tellStartingCompression();
	glTexImage3D(GL_TEXTURE_3D,           // Target
	             0,                       // Mipmap level
	             getInternalFormat(),     // Internal format
	             dataset->getWidth(),     // Width
	             dataset->getHeight(),    // Height
	             dataset->getDepth(),     // Depth
	             0,                       // Border
	             GL_LUMINANCE,            // Format
	             dataset->getType(),      // Type
	             dataset->getData());     // Data
	tellStoppingCompression();
	tellFootprint();
	
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


/** How much memory the texture uses if uncompressed. */
GLint Texture3D::getRawFootprint() const {
	
	return dataset->getFootprint();
}


/** @return Type based on compress flag. */
GLenum Texture3D::getInternalFormat() const {
	
	return compress ? GL_COMPRESSED_RGB : GL_LUMINANCE;
}


/** Inform user we're starting to compress the texture. */
void Texture3D::tellStartingCompression() {
	
	if (compress) {
		ticks = clock();
		glog << "[Texture3D] Compressing texture... ";
	}
}


/** Inform user we finished compressing the texture and show the time. */
void Texture3D::tellStoppingCompression() {
	
	if (compress) {
		glog << ((double)(clock()-ticks))/CLOCKS_PER_SEC << "s" << endl;
		if (isCompressed()) {
			glog << "[Texture3D] Successfully compressed texture." << endl;
		} else {
			glog << "[Texture3D] Did not compress texture." << endl;
		}
	}
}


/** Inform user of the footprint in megabytes. */
void Texture3D::tellFootprint() {
	
	double footprintInMB;
	
	footprintInMB = (double)getFootprint() / 1048576;
	glog << "[Texture3D] Footprint = " << footprintInMB << " MB" << endl;
}


/** Adds the <i>compress</i> flag to the node's description. */
string Texture3D::toString() const {
	
	ostringstream stream;
	
	stream << Texture::toString();
	stream << " compress=" << compress?'T':'F';
	return stream.str();
}

