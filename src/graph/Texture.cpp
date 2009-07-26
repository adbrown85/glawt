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
 * Binds the texture.
 */
void Texture::apply() {
	
	// Bind texture
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0 + unit);
	ilBindImage(image);
	ilutGLBindTexImage();
}



/**
 * Finds out which texture unit 
 */
void Texture::associate() {
	
	Node *current;
	Texture *texture;
	string className;
	
	// Activate textures
	glEnable(GL_TEXTURE_2D);
	load();
	
	// Find out how many above
	current = this->parent;
	while (current != NULL) {
		className = current->getClassName();
		if (className.compare("Texture") == 0) {
			texture = static_cast<Texture*>(current);
			unit = texture->getUnit() + 1;
			break;
		}
		current = current->getParent();
	}
	cout << "Gander,Texture: Using unit " << unit << "." << endl;
}



/**
 * Loads an image into the texture.
 */
void Texture::load() {
	
	char file[64];
	
	// Check DevIL version and initialize
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) {
		cerr << "Gander,Texture: DevIL versions do not match." << endl;
	}
	ilInit();
	
	// Load image as texture
	ilGenImages(1, &image);
	ilBindImage(image);
	if (ilLoadImage(filename.c_str()))
		cout << "Gander,Texture: DevIL loaded '" 
		     << filename
		     << "'." << endl;
	else {
		cerr << "Gander,Texture: DevIL could not load '" 
		     << filename 
		     << "'." << endl;
		exit(1);
	}
}



void Texture::print() const {
	
	cout << "  " << *this << endl;
}



/**
 * Unbinds the texture.
 */
void Texture::remove() {
	
	// Unbind texture
	glDisable(GL_TEXTURE_2D);
}



ostream& operator<<(ostream& stream,
                    const Texture &texture) {
	
	stream << static_cast<Node>(texture) << " "
	       << "filename='" << texture.filename << "' "
	       << "unit='" << texture.unit << "'";
	return stream;
}
