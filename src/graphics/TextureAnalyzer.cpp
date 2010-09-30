/*
 * TextureAnalyzer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureAnalyzer.hpp"


/** @return Number of bits used to store each pixel of the texture. */
GLint TextureAnalyzer::getBitsPerPixel() {
	
	// Calculate by format
	switch (getFormat()) {
	case GL_RGB:
	case GL_RGB8:
	case GL_COMPRESSED_RGB:
	case GL_COMPRESSED_SRGB:
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
		return getRGBSize();
	case GL_RGBA:
	case GL_RGBA8:
	case GL_RGBA16F:
	case GL_RGBA32F:
	case GL_COMPRESSED_RGBA:
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		return getRGBASize();
	case GL_LUMINANCE:
		return getLuminanceSize();
	default:
		throw Exception("[TextureAnalyzer] Format not supported.");
	}
}

/** @return Number of bytes used to store each pixel of the texture. */
GLint TextureAnalyzer::getBytesPerPixel() {
	
	return getBitsPerPixel() / 8;
}


GLint TextureAnalyzer::getRedSize() {
	
	GLint size;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_RED_SIZE, &size);
	return size;
}


GLint TextureAnalyzer::getGreenSize() {
	
	GLint size;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_GREEN_SIZE, &size);
	return size;
}


GLint TextureAnalyzer::getBlueSize() {
	
	GLint size;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_BLUE_SIZE, &size);
	return size;
}


GLint TextureAnalyzer::getAlphaSize() {
	
	GLint size;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_ALPHA_SIZE, &size);
	return size;
}


GLint TextureAnalyzer::getLuminanceSize() {
	
	GLint size;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_LUMINANCE_SIZE, &size);
	return size;
}


GLint TextureAnalyzer::getRGBSize() {
	
	return getRedSize() + getGreenSize() + getBlueSize();
}


GLint TextureAnalyzer::getRGBASize() {
	
	return getRGBSize() + getAlphaSize();
}


GLint TextureAnalyzer::getWidth() {
	
	GLint width;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_WIDTH, &width);
	return width;
}


GLint TextureAnalyzer::getHeight() {
	
	GLint height;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_HEIGHT, &height);
	return height;
}


GLint TextureAnalyzer::getDepth() {
	
	GLint depth;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_DEPTH, &depth);
	return depth;
}


GLint TextureAnalyzer::getFootprint() {
	
	if (isCompressed()) {
		return getFootprintCompressed();
	} else {
		return getFootprintRaw();
	}
}


GLint TextureAnalyzer::getFootprintCompressed() {
	
	GLint fp;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &fp);
	return fp;
}


GLint TextureAnalyzer::getFootprintRaw() {
	
	GLint bytes;
	GLint width, height, depth;
	
	width = getWidth();
	height = getHeight();
	depth = getDepth();
	bytes = getBytesPerPixel();
	
	switch (type) {
	case GL_TEXTURE_1D:
		return bytes * (width);
	case GL_TEXTURE_2D:
		return bytes * (width * height);
	case GL_TEXTURE_3D:
		return bytes * (width * height * depth);
	}
}


GLenum TextureAnalyzer::getFormat() {
	
	GLint format;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
	return (GLenum)format;
}


/** @return True if the texture is compressed. */
bool TextureAnalyzer::isCompressed() {
	
	GLint compressed;
	
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_COMPRESSED, &compressed);
	return compressed;
}


void TextureAnalyzer::setTexture(GLenum type, GLuint handle) {
	
	this->type = type;
	this->handle = handle;
	glBindTexture(type, handle);
}

