/*
 * Octree.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Octree.hpp"


Octree::Octree(const Tag &tag) : Texture(GL_TEXTURE_1D, tag) {
	
	textureData = NULL;
	dataset = NULL;
	size = 0;
	tag.get("link", link, true, false);
	tag.get("threshold", threshold, false);
}


/**
 * Deletes the texture data.
 * 
 * @todo Should recursively delete root.
 */
Octree::~Octree() {
	
	if (textureData != NULL)
		delete[] textureData;
}


/**
 * Finds the 3D texture the octree should generate itself from.
 * 
 * @throws NodeException if the octree could not find the 3D texture.
 */
void Octree::associate() {
	
	Texture3D *texture3d;
	
	// Units
	Texture::associate();
	
	// Find texture3d
	texture3d = Texture3D::find(this, link);
	if (texture3d == NULL) {
		NodeException e(tag);
		e << "[Octree] Could not find " << link << " texture.";
		throw e;
	}
	
	// Get dataset
	dataset = texture3d->getDataset();
}


/**
 * Builds an octree and then calls load().
 */
void Octree::finalize() {
	
	OctreeBuilder builder(dataset);
	
	// Build
	builder.setThreshold(threshold);
	root = builder.build();
	size = builder.getTotalNodes();
	height = builder.getTreeHeight();
	
	// Load it
	load();
}


/**
 * Loads the octree data into the texture.
 */
void Octree::load() {
	
	// Get the data
	textureData = new unsigned char[size];
	store(root, 0, 0);
	
	// Create the texture
	glActiveTexture(GL_TEXTURE0 + getUnit());
	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, getHandle());
	glTexImage1D(GL_TEXTURE_1D,          // target
	             0,                      // level
	             GL_R8UI,                // internal format
	             size,                   // width
	             0,                      // border
	             GL_RED_INTEGER,         // format
	             GL_UNSIGNED_BYTE,       // type
	             textureData);           // data
	
	// Set parameters
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


/**
 * Recursively stores an octree node and its children into the texture data.
 * 
 * @param [in] node Pointer to the octree node.
 * @param [in] index Where to store the node in the array.
 * @param [in] depth Current number of levels down from the root
 */
void Octree::store(OctreeNode *node,
                   int index,
                   int depth) {
	
	// Store self
	textureData[index] = (int)(node->isEmpty()) * 255;
	
	// Store children
	if (depth < height) {
		for (int i=0; i<8; ++i) {
			store(node->getChild(i), ++index, depth+1);
		}
	}
}


string Octree::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << Texture::toString();
	stream << " link='" << link << "'"
	       << " threshold='" << threshold << "'"
	       << " size='" << size << "'"
	       << " height='" << height << "'";
	return stream.str();
}

