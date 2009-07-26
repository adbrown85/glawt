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
	unit = 0;
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
	       << "unit='" << texture.unit << "'";
	return stream;
}
