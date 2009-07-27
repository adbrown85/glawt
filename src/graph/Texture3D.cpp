/*
 * Texture3D.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture3D.hpp"



/**
 * Creates a new, empty 3D texture.
 * 
 * @param filename
 *     Path to the file.
 * @param name
 *     Name another node can reference.
 */
Texture3D::Texture3D(string filename,
                     string name) :
                     Texture(filename,name) {
	
	// Initialize
	className = "Texture3D";
	type = "3D";
	pitch = 0;
	width = 0;
	data = NULL;
}



/**
 * Calls 'deallocate' for this texture.
 */
Texture3D::~Texture3D() {
	
	// Destroy
	deallocate();
}



/**
 * Creates an array in dynamic memory for the texture according to 'width'.
 */
void Texture3D::allocate() {
	
	// Allocate array
	if (data != NULL)
		throw "Data already allocated for Texture3D.  Must deallocate first.";
	data = new byte[width*width*width];
}



/**
 * Enables 3D texturing, activates a texture unit, and binds the texture to it.
 */
void Texture3D::apply() {
	
	// Enable texturing
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_3D);
}



/**
 * 
 */
void Texture3D::associate() {
	
	// Find out which texture unit to use
	Texture::associate();
	
	// Load the texture
	load();
}



/**
 * Removes the array created for the texture.
 */
void Texture3D::deallocate() {
	
	// Deallocate array
	if (data != NULL)
		delete[] data;
	data = NULL;
}



/**
 * Loads the file specified by 'filename' into the array.
 */
void Texture3D::load() {
	
	ifstream file;
	int token, width2;
	unsigned int index;
	
	// Read width and pitch, allocate data
	file.open(filename.c_str());
	file >> width;
	file >> pitch;
	allocate();
	
	// Read slices
	width2 = width * width;
	for (int k=0; k<width; ++k) {
		for (int i=0; i<width; ++i) {
			for (int j=0; j<width && file; ++j) {
				file >> token;
				index = (k*width2) + (i*width) + j;
				data[index] = (byte)token;
			}
		}
	}
	file.close();
	
	// Bind the texture to the right unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &id);
	cerr << "Texture: " << id << endl;
	glBindTexture(GL_TEXTURE_3D, id);
	
	// Pass the texture to OpenGL
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexImage3D(GL_TEXTURE_3D,
	             0,
	             1,
	             width,
	             width,
	             width,
	             0,
	             GL_RED,
	             GL_UNSIGNED_BYTE,
	             data);
	
	for (int i=0; i<width; ++i)
		printSlice(i);
}



/**
 * Prints each cell in a slice to standard error.
 * 
 * @param slice
 *     Index of the slice to print.
 */
void Texture3D::printSlice(int slice) {
	
	int index, k;
	
	// Check for data
	if (data == NULL)
		cerr << "Gander,Texture3D: Data not loaded." << endl;
	
	// Print each cell
	k = width * width * slice;
	for (int i=0; i<width; ++i) {
		cerr << "  ";
		for (int j=0; j<width; j++) {
			index = k + (i*width) + j;
			cerr << setw(3) << (int)data[index] << " ";
		}
		cerr << endl;
	}
}



/**
 * Disables 3D texturing on the unit so other objects will not be textured.
 */
void Texture3D::remove() {
	
	// Disable texturing
	glActiveTexture(GL_TEXTURE0 + unit);
	glDisable(GL_TEXTURE_3D);
}

