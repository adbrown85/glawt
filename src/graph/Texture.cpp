/*
 * Texture.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"
bool Texture::asserted=false;



/**
 * Initializes a texture.
 * 
 * @param filename
 *     Path to the file containing the texture.
 * @param name
 *     Name of the texture.
 */
Texture::Texture(string filename,
                 string name) {
	
	// Initialize
	className = "Texture";
	this->filename = filename;
	this->unit = 0;
	this->name = name;
}



/**
 * Finds out which texture unit to use by looking for other %Texture ancestors.
 */
void Texture::associate() {
	
	Node *current;
	Texture *texture=NULL;
	string className;
	
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
	stream << " file='" << filename << "'"
	       << " unit='" << unit << "'"
	       << " name='" << name << "'";
	return stream.str();
}

