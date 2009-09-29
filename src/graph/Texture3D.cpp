/*
 * Texture3D.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture3D.hpp"



/**
 * Creates a new 3D texture.
 * 
 * @param filename
 *     Path to the file.
 * @param name
 *     Name another node can reference.
 */
Texture3D::Texture3D(string filename,
                     string name) : 
                     Texture(filename, name),
                     dataset(filename) {
	
	// Initialize
	Texture3D::init();
}



/**
 * Creates a new 3D texture from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Texture3D::Texture3D(const Tag &tag) : 
                     Texture(tag),
                     dataset(tag) {
	
	// Initialize
	Texture3D::init();
}



/**
 * Enables 3D texturing, activates a texture unit, and binds the texture to it.
 */
void Texture3D::apply() {
	
	// Enable texturing
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_3D);
}



/**
 * Loads the texture on an available texture unit.
 */
void Texture3D::associate() {
	
	// Load the texture
	Texture::associate();
	load();
}



/**
 * Initializes attributes common to all constructors.
 */
void Texture3D::init() {
	
	// Initialize
	className = "Texture3D";
	type = "3D";
}


/**
 * Loads the dataset as a 3D texture.
 */
void Texture3D::load() {
	
	// Bind the texture to the right unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_3D, handle);
	
	// Pass the texture to OpenGL
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
	glTexImage3D(GL_TEXTURE_3D,           // Target
	             0,                       // Mipmap level
	             GL_LUMINANCE,            // Internal format
	             dataset.getWidth(),      // Width
	             dataset.getHeight(),     // Height
	             dataset.getDepth(),      // Depth
	             0,                       // Border
	             GL_LUMINANCE,            // Format
	             dataset.getType(),       // Type
	             dataset.getData());      // Data
}



/**
 * Disables 3D texturing on the unit so other objects will not be textured.
 */
void Texture3D::remove() {
	
	// Disable texturing
	glActiveTexture(GL_TEXTURE0 + unit);
	glDisable(GL_TEXTURE_3D);
}

