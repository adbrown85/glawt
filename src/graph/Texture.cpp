/*
 * Texture.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"



/**
 * Initializes a texture that will be bound to the first texture unit.
 */
Texture::Texture(string filename) {
	
	// Initialize
	className = "Texture";
	this->filename = filename;
	this->unit = 0;
	this->name = "";
}



/**
 * Initializes a texture that will be bound to the first texture unit and can 
 * be referenced by a name.
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



void Texture::print() const {
	
	cout << "  " << *this << endl;
}



ostream& operator<<(ostream& stream,
                    const Texture &texture) {
	
	stream << static_cast<Node>(texture) << " "
	       << "filename='" << texture.filename << "' "
	       << "unit='" << texture.unit << "' "
	       << "name='" << texture.name << "'";
	return stream;
}
