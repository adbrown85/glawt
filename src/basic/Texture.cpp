/*
 * Texture.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Texture.hpp"


/** Creates a new texture from an XML tag.
 * 
 * @param [in] type 1D, 2D, or 3D.
 * @param [in] tag XML tag with "type", "name", and "filename" attributes.
 */
Texture::Texture(GLenum type, const Tag &tag) : Node(tag), Nameable(tag) {
	
	// Initialize
	this->unit = 0;
	this->handle = 0;
	this->type = type;
	tag.get("file", filename, false, false);
}


/** Binds the texture. */
void Texture::apply() {
	
	activate();
	bind();
}


/** Finds out which texture unit to use and generates the texture object. */
void Texture::associate() {
	
	Texture *texture;
	
	// Find the right unit
	texture = Texture::find(this);
	if (texture != NULL)
		unit = texture->getUnit() + 1;
	
	// Generate
	glGenTextures(1, &handle);
}


/** @return How much memory the texture uses. */
GLint Texture::getFootprint() const {
	
	GLint fp;
	
	if (isCompressed()) {
		activate();
		glGetTexLevelParameteriv(type,0,GL_TEXTURE_COMPRESSED_IMAGE_SIZE,&fp);
	} else {
		fp = getRawFootprint();
	}
	return fp;
}


/** Checks if the texture was successfully compressed. */
bool Texture::isCompressed() const {
	
	GLint compressed;
	
	activate();
	glGetTexLevelParameteriv(type, 0, GL_TEXTURE_COMPRESSED, &compressed);
	return compressed;
}


/** Forms a string using the Texture's attributes. */
string Texture::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	if (hasName())
		stream << " name='" << getName() << "'";
	stream << " unit='" << unit << "'"
	       << " handle='" << handle << "'";
	if (!filename.empty())
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


/** Finds the first texture above node. */
Texture* Texture::find(Node *node) {
	
	Texture *texture;
	
	// Check input
	if (node == NULL)
		return NULL;
	
	// Look for texture above node
	node = node->getParent();
	while (node != NULL) {
		texture = dynamic_cast<Texture*>(node);
		if (texture != NULL)
			return texture;
		node = node->getParent();
	}
	return NULL;
}

