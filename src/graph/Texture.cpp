/*
 * Texture.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"



/**
 * Initializes a texture.
 * 
 * @param name
 *     Name of the texture.
 * @param filename
 *     Path to a file containing the texture.
 */
Texture::Texture(string name,
                 string filename) {
	
	// Initialize
	className = "Texture";
	this->name = name;
	this->filename = filename;
	this->unit = 0;
}



/**
 * Finds out which texture unit to use by looking for other %Texture ancestors.
 */
void Texture::associate() {
	
	Node *current;
	Texture *texture=NULL;
	
	// Find the closest Texture ancestor
	current = this->parent;
	while (current != NULL) {
		texture = dynamic_cast<Texture*>(current);
		if (texture != NULL)
			break;
		current = current->getParent();
	}
	
	// Change unit
	if (texture != NULL)
		unit = texture->getUnit() + 1;
}



/**
 * Forms a string using the Texture's attributes.
 */
string Texture::toString() const {
	
	stringstream stream;
	
	stream << Node::toString();
	stream << " name='" << name << "'"
	       << " unit='" << unit << "'"
	       << " file='" << filename << "'";
	return stream.str();
}

