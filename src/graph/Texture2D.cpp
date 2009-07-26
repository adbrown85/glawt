/*
 * Texture2D.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture2D.hpp"



/**
 * Creates a new 2D texture from a file.
 * 
 * @param filename
 *     Path to the file.
 */
Texture2D::Texture2D(string filename) :
                     Texture(filename) {
	
	// Initialize
	className = "Texture2D";
	type = "2D";
	image = 0;
}



/**
 * Enables 2D texturing, activates a texture unit, and binds the texture to it.
 */
void Texture2D::apply() {
	
	// Bind texture
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0 + unit);
	ilBindImage(image);
	ilutGLBindTexImage();
}



/**
 * Activates the texture on the correct unit.
 */
void Texture2D::associate() {
	
	// Find out which texture unit to use
	Texture::associate();
	
	// Activate textures
	glEnable(GL_TEXTURE_2D);
	load();
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
	glDisable(GL_TEXTURE_2D);
}
