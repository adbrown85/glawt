/*
 * TextureFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureFactory.hpp"
map<string,TextureInvoice> TextureFactory::inventory;
TextureBuilder2D TextureFactory::builder2D;
TextureBuilder3D TextureFactory::builder3D;


/** Creates a texture from a file. */
TextureInvoice TextureFactory::create(const string& filename, bool compress) {
	
	map<string,TextureInvoice>::iterator it;
	string extension;
	TextureInvoice invoice;
	
	// Check if already built
	it = inventory.find(filename);
	if (it != inventory.end()) {
		return it->second;
	}
	
	// Otherwise build correct type
	extension = Path::getExtension(filename);
	if (Text::toLower(extension) == "vlb") {
		invoice = builder3D.build(filename);
	} else {
		invoice = builder2D.build(filename);
	}
	
	// Store and finish
	inventory[filename] = invoice;
	return invoice;
}


/** Creates a blank texture with characteristics specified by @e order. */
TextureInvoice TextureFactory::create(const TextureOrder &order) {
	
	// Give to correct builder
	switch (order.type) {
	case GL_TEXTURE_2D:
		return builder2D.build(order);
	case GL_TEXTURE_1D:
	case GL_TEXTURE_3D:
	default:
		throw Exception("[TextureFactory] Order type not supported.");
	}
}

