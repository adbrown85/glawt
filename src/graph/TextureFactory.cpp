/*
 * TextureFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureFactory.hpp"


TextureFactory::TextureFactory() {
	
	tags.insert("octree");
	tags.insert("texture2d");
	tags.insert("texture3d");
}


/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag XML tag with name and attributes.
 * @throws const_char* if tag name not supported.
 */
Node* TextureFactory::create(const Tag &tag) const {
	
	// Supported nodes
	if (tag.name == "octree")
		return new Octree(tag);
	else if (tag.name == "texture2d")
		return new Texture2D(tag);
	else if (tag.name == "texture3d")
		return new Texture3D(tag);
	else
		throw "[TextureFactory] Tag not supported by this factory.";
}
