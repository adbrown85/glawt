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
                     string name) : Texture(filename, name),
                                    dataset(filename) {
	
	// Initialize
	className = "Texture3D";
	type = "3D";
}



/**
 * Creates a new texture by processing another texture.
 * 
 * @param effect
 *     Indicates which effect to use.
 * @param name
 *     Indicates which dataset to use.
 */
/*
Texture3D::Texture3D(string effect,
                     string name) {
	
	Dataset *dataset;
	Texture3D *texture3d;
	
	// Find dataset
	texture3d = find(name);
	dataset = texture3d->getDataset();
	
	// 
	Effect::apply(effect, *dataset, this->dataset);
}
*/



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
 * Finds another Texture3D by name.
 * 
 * @return
 *     Pointer to the Texture3D.
 */
Texture3D* Texture3D::find(string name) {
	
	bool found;
	Node *node;
	Texture3D *texture3d;
	string message;
	
	// Initialize
	found = false;
	node = parent;
	
	// Look for matching node up the tree
	while (node != NULL) {
		texture3d = dynamic_cast<Texture3D*>(node);
		if (texture3d == NULL) {
			node = node->getParent();
			continue;
		}
		if (name.compare(texture3d->getName()) == 0) {
			found = true;
			break;
		}
	}
	
	// Finish
	if (!found) {
		message = "Texture3D: Could not find Texture3D with name '";
		message += name;
		message += "'!";
		throw message.c_str();
	}
	return texture3d;
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

