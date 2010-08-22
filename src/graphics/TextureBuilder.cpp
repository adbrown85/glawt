/*
 * TextureBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureBuilder.hpp"


/** Builds a texture from a file. */
TextureInvoice TextureBuilder::build(const string &filename, bool compress) {
	
	prepare();
	assemble(filename);
	complete();
	package();
	return invoice;
}


/** Builds a texture from an order. */
TextureInvoice TextureBuilder::build(const TextureOrder &order) {
	
	prepare();
	assemble(order);
	complete();
	package();
	return invoice;
}


/** Generates and binds a new texture. */
void TextureBuilder::prepare() {
	
	glGenTextures(1, &invoice.handle);
	glBindTexture(getType(), invoice.handle);
}


/** Records details in the invoice. */
void TextureBuilder::package() {
	
	GLenum format;
	
	// Type
	invoice.type = getType();
	
	// Dimensions
	findParameter(GL_TEXTURE_WIDTH, &invoice.width);
	findParameter(GL_TEXTURE_HEIGHT, &invoice.height);
	findParameter(GL_TEXTURE_DEPTH, &invoice.depth);
	
	// Format
	findParameter(GL_TEXTURE_INTERNAL_FORMAT, (GLint*)(&format));
	invoice.format = PixelFormat::getFormat(format);
}


/** Finds a texture parameter. */
void TextureBuilder::findParameter(GLenum name, GLint *value) {
	
	glGetTexLevelParameteriv(getType(), 0, name, value);
}

