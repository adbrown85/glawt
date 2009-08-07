/*
 * Texture.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"
bool Texture::asserted=false;



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
	if (!asserted)
		assertions();
}



/**
 * Ensures that the first 16 texture units are consecutively numbered.
 */
void Texture::assertions() {
	
	GLuint units[16];
	GLint maxUnits;
	
	// Initialize
	units[0] = GL_TEXTURE0;
	units[1] = GL_TEXTURE1;
	units[2] = GL_TEXTURE2;
	units[3] = GL_TEXTURE3;
	units[4] = GL_TEXTURE4;
	units[5] = GL_TEXTURE5;
	units[6] = GL_TEXTURE6;
	units[7] = GL_TEXTURE7;
	units[8] = GL_TEXTURE8;
	units[9] = GL_TEXTURE9;
	units[10] = GL_TEXTURE10;
	units[11] = GL_TEXTURE11;
	units[12] = GL_TEXTURE12;
	units[13] = GL_TEXTURE13;
	units[14] = GL_TEXTURE14;
	units[15] = GL_TEXTURE15;
	
	// Check for consecutive numbers
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);
	maxUnits = maxUnits < 16 ? maxUnits : 16;
	for (int i=0; i<maxUnits-1; ++i)
		assert(units[i+1] == units[i] + 1);
	asserted = true;
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
	
	cout << "  " << toString() << endl;
}



string Texture::toString() const {
	
	stringstream stream;
	
	stream << Node::toString();
	stream << " file='" << filename << "'"
	       << " unit='" << unit << "'"
	       << " name='" << name << "'";
	return stream.str();
}
