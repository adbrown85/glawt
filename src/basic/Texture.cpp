/*
 * Texture.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture.hpp"


/** Creates a new texture from an XML tag.
 * 
 * @param [in] tag XML tag with "type", "name", and "filename" attributes.
 */
Texture::Texture(const Tag &tag) : Node(tag), Nameable(tag) {
	
	// Retrieve from tag
	tag.get("file", filename, false, false);
	tag.get("size", size, false);
	tag.get("format", format, false, true);
	
	// Defaults
	this->unit = 0;
	this->handle = 0;
	this->type = GL_TEXTURE_2D;
	
	// Check
	check();
}


/** Enables the texture. */
void Texture::apply() {
	
	activate();
	bind();
}


/** Checks the size and format. */
void Texture::check() {
	
	// Size
	if (size == 0)
		size = CANVAS_WIDTH;
	
	// Format
	if (format.empty())
		format = "rgba";
}


/** Finds out which texture unit to use and generates the texture object. */
void Texture::associate() {
	
	Texture *texture;
	
	// Find the right unit
	texture = Scout<Texture>::locate(getParent());
	if (texture != NULL)
		unit = texture->getUnit() + 1;
}


/** Requests a texture from the factory. */
void Texture::finalize() {
	
	TextureInvoice invoice;
	
	// Get texture from factory
	if (hasFilename()) {
		invoice = TextureFactory::create(filename);
	} else {
		invoice = TextureFactory::create(makeOrder());
	}
	
	// Copy details
	type   = invoice.type;
	format = invoice.format;
	handle = invoice.handle;
}


/** Creates an order for the texture factory. */
TextureOrder Texture::makeOrder() const {
	
	TextureOrder order;
	
	// Fill out
	order.type   = type;
	order.format = format;
	order.width  = size;
	order.height = size;
	order.depth  = size;
	
	// Finish
	return order;
}


/** Forms a string using the Texture's attributes. */
string Texture::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	if (hasName())
		stream << " name='" << getName() << "'";
	stream << " unit='" << unit << "'"
	       << " handle='" << handle << "'"
	       << " format='" << format << "'";
	if (hasFilename())
		stream << " file='" << filename << "'";
	return stream.str();
}


/** Discover all texture nodes under a node. */
list<Texture*> Texture::search(Node *node) {
	
	Node::iterator it;
	list<Texture*> T;
	Texture* t;
	queue<Node*> Q;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		t = dynamic_cast<Texture*>(node);
		if (t != NULL) {
			T.push_back(t);
		}
		for (it=node->begin(); it!=node->end(); ++it) {
			Q.push(*it);
		}
		Q.pop();
	}
	return T;
}

