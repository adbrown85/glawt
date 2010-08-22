/*
 * PixelFormat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "PixelFormat.hpp"
map<string,GLenum> PixelFormat::formats;
bool PixelFormat::loaded=false;


/** @return OpenGL enumeration for a format. */
GLenum PixelFormat::getFormat(const string &format) {
	
	map<string,GLenum>::iterator it;
	
	// Make sure loaded
	load();
	
	// Find value by key
	it = formats.find(format);
	if (it != formats.end()) {
		return it->second;
	} else {
		throw Exception("[PixelFormat] Format not loaded.");
	}
}


/** @return Human-readable string for a format. */
string PixelFormat::getFormat(GLenum format) {
	
	map<string,GLenum>::iterator it;
	
	// Make sure loaded
	load();
	
	// Find key by value
	for (it=formats.begin(); it!=formats.end(); ++it) {
		if (it->second == format) {
			return it->first;
		}
	}
	
	// Not loaded
	throw Exception("[PixelFormat] Format not loaded.");
}


/** Loads the formats. */
void PixelFormat::load() {
	
	// Check
	if (loaded) return;
	
	// Formats
	loadFormats();
	
	// Finish
	loaded = true;
}


void PixelFormat::loadFormats() {
	
	// RGB
	formats["rgb"] = GL_RGB;
	formats["rgb8"] = GL_RGB8;
	formats["compressed_rgb"] = GL_COMPRESSED_RGB;
	
	// RGBA
	formats["rgba"] = GL_RGBA;
	formats["rgba8"] = GL_RGBA8;
	formats["compressed_rgba"] = GL_COMPRESSED_RGBA;
	
	// Individuals
	formats["red"] = GL_RED;
	formats["compressed_red"] = GL_COMPRESSED_RED;
	formats["luminance"] = GL_LUMINANCE;
	
	// Pairs
	formats["rg"] = GL_RG;
	formats["compressed_rg"] = GL_COMPRESSED_RG;
	
	// Other types
	formats["rgba16f"] = GL_RGBA16F;
}

