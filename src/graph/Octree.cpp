/*
 * Octree.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "Octree.hpp"


Octree::Octree(const Tag &tag):
               Texture(tag) {
	
	className = "Octree";
	array = NULL;
	dataset = NULL;
	size = 0;
	tag.get("link", link, true);
}


/**
 * @todo Should recursively delete root.
 */
Octree::~Octree() {
	
	if (array != NULL)
		delete[] array;
}


/**
 * Finds the 3D texture the octree should generate itself from.
 * 
 * @throws const_char* if the octree could not find the 3D texture.
 */
void Octree::associate() {
	
	Texture3D *texture3d;
	
	// Units
	Texture::associate();
	
	// Find texture3d
	texture3d = Texture3D::find(this, link);
	if (texture3d == NULL) {
		ostringstream message;
		message << "[Octree] Could not find "
		        << link
		        << " texture.";
		throw message.str().c_str();
	}
	
	// Get dataset
	dataset = texture3d->getDataset();
}


/**
 * Builds an octree and then creates a texture from it.
 */
void Octree::finalize() {
	
	OctreeBuilder builder(dataset);
	
	cerr << "[Octree] Building octree..." << endl;
	root = builder.build();
	size = builder.getTotalNodes();
	load();
}


void Octree::load() {
	
	// Get the data
	array = new unsigned char[size];
	
	// Create the texture
	glGenTextures(1, &handle);
/*
	glBindTexture(GL_TEXTURE_1D, handle);
	glTexImage1D(GL_TEXTURE_1D,          // target
	             0,                      // level
	             GL_INTENSITY,           // internalFormat
	             size,                   // width
	             0,                      // border
	             GL_LUMINANCE,           // format
	             GL_UNSIGNED_BYTE,       // type
	             data);                  // data
*/
}


string Octree::toString() const {
	
	ostringstream stream;
	
	stream << Texture::toString();
	stream << " size='" << size << "'";
	return stream.str();
}

