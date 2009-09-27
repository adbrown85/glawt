/*
 * Texture2D.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture2D.hpp"



/**
 * Creates a new 2D texture that can be referenced by name.
 * 
 * @param filename
 *     Path to the file.
 * @param name
 *     Name another node can reference.
 */
Texture2D::Texture2D(string name) :
                     Texture(name) {
	
	// Initialize
	className = "Texture2D";
	this->type = "2D";
	this->image = 0;
	this->blank = true;
}



/**
 * Creates a new 2D texture from a file that can be referenced by name.
 * 
 * @param filename
 *     Path to the file.
 * @param name
 *     Name another node can reference.
 */
Texture2D::Texture2D(string filename,
                     string name) :
                     Texture(filename,name) {
	
	// Initialize
	className = "Texture2D";
	this->type = "2D";
	this->image = 0;
	this->blank = false;
}



/**
 * Enables 2D texturing, activates a texture unit, and binds the texture to it.
 */
void Texture2D::apply() {
	
	// Bind texture
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_2D);
	if (!blank) {
		ilBindImage(image);
		ilutGLBindTexImage();
	}
}



/**
 * Activates the texture on the unit.
 */
void Texture2D::finalize() {
	
	// Activate texture unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_2D);
	
	// Generate or load
	if (blank)
		generate();
	else
		load();
}



/**
 * Finds a %Texture2D with a specific name.
 * 
 * @param node
 *     Node to start looking.
 * @param pointer
 *     Pointer to the Texture2D.
 * @param name
 *     Name of the node as specified by the user.
 */
void Texture2D::find(Node *node,
                     Texture2D *&pointer,
                     string name) {
	
	// Search
	node = node->parent;
	while (node != NULL) {
		pointer = dynamic_cast<Texture2D*>(node);
		if (pointer != NULL) {
			if (name.compare(pointer->getName()) == 0)
				break;
			else
				pointer = NULL;
		}
		node = node->parent;
	}
}



/**
 * Generates a blank texture.
 */
void Texture2D::generate() {
	
	// Create the texture
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             GL_RGBA8,
	             width,
	             height,
	             0,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             NULL);
	
	// Set parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}



/**
 * Initializes required libraries, currently just DevIL.
 * 
 * Checks that DevIL libraries being run by the user are not older than the 
 * libraries used to compile Gander.  If they are, warnings are issued.  Either
 * way DevIL is initialized by calling 'ilInit'.
 */
void Texture2D::initLibraries() {
	
	ILint ilVersion, iluVersion, ilutVersion;
	
	// Check DevIL components
	ilVersion = ilGetInteger(IL_VERSION_NUM);
	if (ilVersion < IL_VERSION)
		cerr << "Gander,Texture2D: DevIL (IL) compiled with "
		     << IL_VERSION
		     << " but running "
		     << ilVersion
		     << "." << endl;
	iluVersion = iluGetInteger(ILU_VERSION_NUM);
	if (iluVersion < ILU_VERSION)
		cerr << "Gander,Texture2D: DevIL (ILU) compiled with "
		     << ILU_VERSION
		     << " but running "
		     << iluVersion
		     << "." << endl;
	ilutVersion = ilutGetInteger(ILUT_VERSION_NUM);
	if (ilutVersion < ILUT_VERSION)
		cerr << "Gander,Texture2D: DevIL (ILUT) compiled with "
		     << ILUT_VERSION
		     << " but running "
		     << ilutVersion
		     << "." << endl;
	
	// Initialize DevIL
	ilInit();
}



/**
 * Loads an image into the texture.
 */
void Texture2D::load() {
	
	// Initialize DevIL
	initLibraries();
	
	// Load image as texture
	ilGenImages(1, &image);
	ilBindImage(image);
	if (ilLoadImage(filename.c_str()))
		cerr << "Gander,Texture2D: DevIL loaded '" 
		     << filename
		     << "'." << endl;
	else {
		cerr << "Gander,Texture2D: DevIL could not load '" 
		     << filename 
		     << "'." << endl;
		exit(1);
	}
}



/**
 * Disables 2D texturing so other objects will not be textured.
 */
void Texture2D::remove() {
	
	// Disable texturing
	glActiveTexture(GL_TEXTURE0 + unit);
	glDisable(GL_TEXTURE_2D);
}
