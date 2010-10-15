/*
 * TextureBuilder2D.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureBuilder2D.hpp"


/** Fills the texture with data from an image. */
void TextureBuilder2D::assemble(const string &filename, bool compress) {
	
	Image *image;
	GLenum format;
	
	// Get the image and its format
	image = ImageFactory::create(filename);
	if (compress) {
		format = PixelFormat::getCompressedFormat(image->getFormat());
	} else {
		format = image->getFormat();
	}
	
	// Upload data
	glTexImage2D(GL_TEXTURE_2D,                   // target
	             0,                               // level
	             format,                          // internalFormat
	             image->getWidth(),               // width
	             image->getHeight(),              // height
	             0,                               // border
	             image->getFormat(),              // format
	             GL_UNSIGNED_BYTE,                // type
	             image->getData());               // pixels
	
	// Finish
	delete image;
}


/** Builds a blank texture. */
void TextureBuilder2D::assemble(const TextureOrder &order) {
	
	GLenum format;
	
	// Get format
	format = PixelFormat::getFormat(order.format);
	
	// Allocate
	glTexImage2D(GL_TEXTURE_2D,                   // target
	             0,                               // level
	             format,                          // internalFormat
	             order.width,                     // width
	             order.height,                    // height
	             0,                               // border
	             format,                          // format
	             GL_UNSIGNED_BYTE,                // type
	             NULL);                           // pixels
}


/** Sets filtering and wrapping parameters. */
void TextureBuilder2D::complete() {
	
	// Filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	// Wrapping
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

