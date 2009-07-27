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
 * Creates a 3D array in dynamic memory for the texture according to 'width'.
 */
void Texture3D::allocate() {
	
	// Allocate array
	if (data != NULL)
		throw "Data already allocated for Texture3D.  Must deallocate first.";
	data = new byte**[width];
	for (int i=0; i<width; i++) {
		data[i] = new byte*[width];
		for (int j=0; j<width; j++) {
			data[i][j] = new byte[width];
		}
	}
}



/**
 * Enables 3D texturing, activates a texture unit, and binds the texture to it.
 */
void Texture3D::apply() {
	
	// Bind the 
	glEnable(GL_TEXTURE_3D);
	glActiveTexture(GL_TEXTURE0 + unit);
}



/**
 * 
 */
void Texture3D::associate() {
	
	// Find out which texture unit to use
	Texture::associate();
	
	// Activate textures
	glEnable(GL_TEXTURE_3D);
	load();
}



/**
 * Removes the 3D array created for the texture.
 */
void Texture3D::deallocate() {
	
	// Deallocate array
	if (data != NULL) {
		for (int i=0; i<width; i++) {
			for (int j=0; j<width; j++)
				delete[] data[i][j];
			delete[] data[i];
		}
		delete[] data;
	}
	data = NULL;
}



/**
 * Loads the file specified by 'filename' into the array.
 */
void Texture3D::load() {
	
	ifstream file;
	int token;
	
	// Read width and pitch, allocate data
	file.open(filename.c_str());
	file >> width;
	file >> pitch;
	allocate();
	
	// Read slices
	for (int i=0; i<width && file; i++) {
		for (int j=0; j<width && file; j++) {
			for (int k=0; k<width && file; k++) {
				file >> token;
				data[i][j][k] = (byte)token;
			}
		}
	}
	file.close();
}



/**
 * Prints each cell in a slice to standard error.
 * 
 * @param index
 *     Index of the slice to print.
 */
void Texture3D::printSlice(int index) {
	
	// Check for data
	if (data == NULL)
		cerr << "Gander,Texture3D: Data not loaded." << endl;
	
	// Print each cell
	for (int j=0; j<width; j++) {
		cerr << "  ";
		for (int k=0; k<width; k++)
			cerr << setw(3) << (int)data[index][j][k] << " ";
		cerr << endl;
	}
}



/**
 * Disables 3D texturing so other objects will not be textured.
 */
void Texture3D::remove() {
	
	// Disable texturing
	glDisable(GL_TEXTURE_3D);
}

