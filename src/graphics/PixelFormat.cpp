/*
 * PixelFormat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "PixelFormat.hpp"
map<string,GLenum> PixelFormat::namesToCodes;
map<GLenum,string> PixelFormat::codesToNames;
map<GLenum,GLenum> PixelFormat::codesToCompressCodes;
bool PixelFormat::loaded=false;


/** Adds a format to the store. */
void PixelFormat::addFormat(const string &name, GLenum code) {
	
	namesToCodes[name] = code;
	codesToNames[code] = name;
}


/** @return OpenGL enumeration for a format. */
GLenum PixelFormat::getFormat(const string &name) {
	
	map<string,GLenum>::iterator it;
	
	// Make sure loaded
	load();
	
	// Find code for name
	it = namesToCodes.find(name);
	if (it != namesToCodes.end()) {
		return it->second;
	} else {
		Exception e;
		e << "[PixelFormat] Format '" << name << "' not loaded.";
		throw e;
	}
}


/** @return Human-readable string for a format. */
string PixelFormat::getFormat(GLenum code) {
	
	map<GLenum,string>::iterator it;
	
	// Make sure loaded
	load();
	
	// Find name for code
	it = codesToNames.find(code);
	if (it != codesToNames.end()) {
		return it->second;
	} else {
		Exception e;
		e << "[PixelFormat] Format '" << code << "' not loaded.";
		throw e;
	}
}


/** @return Equivalent compressed format for a regular format. */
GLenum PixelFormat::getCompressedFormat(GLenum code) {
	
	map<GLenum,GLenum>::iterator it;
	
	// Make sure loaded
	load();
	
	// Find compressed code for regular code
	it = codesToCompressCodes.find(code);
	if (it != codesToCompressCodes.end()) {
		return it->second;
	} else {
		Exception e;
		e << "[PixelFormat] Equivalent compressed format not loaded.";
		throw e;
	}
}


/** Loads the formats once. */
void PixelFormat::load() {
	
	// Check
	if (loaded) return;
	
	// Formats
	loadNameConversions();
	loadCompressConversions();
	
	// Finish
	loaded = true;
}


/** Load entries for converting to and from names. */
void PixelFormat::loadNameConversions() {
	
	// RGB
	addFormat("rgb", GL_RGB);
	addFormat("rgb8", GL_RGB8);
	addFormat("compressed_rgb", GL_COMPRESSED_RGB);
	addFormat("compressed_srgb", GL_COMPRESSED_SRGB);
	addFormat("compressed_rgb_s3tc_dxt1", GL_COMPRESSED_RGB_S3TC_DXT1_EXT);
	
	// RGBA
	addFormat("rgba", GL_RGBA);
	addFormat("rgba8", GL_RGBA8);
	addFormat("compressed_rgba", GL_COMPRESSED_RGBA);
	addFormat("compressed_rgba_s3tc_dxt1", GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
	addFormat("compressed_rgba_s3tc_dxt3", GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
	addFormat("compressed_rgba_s3tc_dxt5", GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
	
	// Individuals
	addFormat("red", GL_RED);
	addFormat("compressed_red", GL_COMPRESSED_RED);
	addFormat("luminance", GL_LUMINANCE);
	
	// Pairs
	addFormat("rg", GL_RG);
	addFormat("compressed_rg", GL_COMPRESSED_RG);
	
	// Other types
	addFormat("rgba16f", GL_RGBA16F);
}


/** Load entries for converting to compressed codes. */
void PixelFormat::loadCompressConversions() {
	
	codesToCompressCodes[GL_RGB]       = GL_COMPRESSED_RGB;
	codesToCompressCodes[GL_RGBA]      = GL_COMPRESSED_RGBA;
	codesToCompressCodes[GL_RED]       = GL_COMPRESSED_RED;
	codesToCompressCodes[GL_RG]        = GL_COMPRESSED_RG;
	codesToCompressCodes[GL_LUMINANCE] = GL_COMPRESSED_RGB;
}

