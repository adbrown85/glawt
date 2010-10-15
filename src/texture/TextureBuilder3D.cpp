/*
 * TextureBuilder3D.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureBuilder3D.hpp"


/** Fills the texture with data from a dataset. */
void TextureBuilder3D::assemble(const string &filename, bool compress) {
	
	Dataset *dataset;
	GLenum format;
	
	// Load the dataset
	dataset = new Dataset(filename);
	dataset->load();
	
	// Determine format
	if (compress) {
		format = PixelFormat::getCompressedFormat(GL_LUMINANCE);
	} else {
		format = GL_LUMINANCE;
	}
	
	// Upload to texture
	glTexImage3D(GL_TEXTURE_3D,           // Target
	             0,                       // Mipmap level
	             format,                  // Internal format
	             dataset->getWidth(),     // Width
	             dataset->getHeight(),    // Height
	             dataset->getDepth(),     // Depth
	             0,                       // Border
	             GL_LUMINANCE,            // Format
	             dataset->getType(),      // Type
	             dataset->getData());     // Data
	
	// Cleanup
	delete dataset;
}


/** @throw Exception because not currently supported. */
void TextureBuilder3D::assemble(const TextureOrder &order) {
	
	throw Exception("[TextureBuilder3D] Cannot build blank 3D texture.");
}


/** Sets filtering and wrapping parameters. */
void TextureBuilder3D::complete() {
	
	// Filtering
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Wrapping
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
}

