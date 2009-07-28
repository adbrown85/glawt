/*
 * Slice.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Slice.hpp"



Slice::Slice(Sequence *sequence,
             int width,
             int number) {
	
	// Initialize attributes
	this->sequence = sequence;
	this->width = width;
	this->number = number;
	
	// Create and load array
	size = width * width;
	data = new unsigned short[size];
	load();
}



/**
 * Deallocates the data array for this slice.
 */
Slice::~Slice() {
	
	// Delete
	if (data != NULL)
		delete[] data;
}



/**
 * Loads the data from a file into the data array.
 */
void Slice::load() {
	
	ifstream file;
	string filename;
	
	// Get the filename
	filename = sequence->getFilename(number);
	cerr << filename << endl;
	file.open(filename.c_str(), ios_base::binary);
	if (!file)
		throw "Gander,Slice: Could not open file.";
	
	// Read data
	for (int i=size-1; i>=0; --i)
		data[i] = readShort(file);
}



unsigned short Slice::readShort(ifstream &file) {
	
	unsigned short bytes[2];
	
	// Read two bytes
	for (int i=0; i<2; ++i)
		bytes[i] = file.get();
	
	// Make short
	return (bytes[1] << 8) | bytes[0];
}



/**
 * Prints the slice's data array to standard error as a matrix.
 */
void Slice::printData() {
	
	for (int i=0; i<width; ++i) {
		cerr << "  ";
		for (int j=0; j<width; ++j)
			cerr << setw(4) << (int)data[i*width+j];
		cerr << endl;
	}
}

