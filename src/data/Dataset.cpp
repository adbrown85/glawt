/*
 * Dataset.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Dataset.hpp"



/**
 * Creates a new %Dataset from a file.
 */
Dataset::Dataset(const string &filename) {
	
	// Initialize attributes
	this->filename = filename;
	
	// Read the file
	readHeader();
	initTypeEnum();
	initDimensions();
	initData();
	readData();
}



/**
 * Deallocates any data arrays that were allocated.
 */
Dataset::~Dataset() {
	
	if (floatData != NULL)
		delete[] floatData;
	if (shortData != NULL)
		delete[] shortData;
	if (ubyteData != NULL)
		delete[] ubyteData;
	if (ushortData != NULL)
		delete[] ushortData;
}



/**
 * Checks that the file is a vlib file.
 * 
 * Makes sure the file can be opened and that the first line is the file 
 * descriptor 'VLIB.1'.  Also finds where the header details start by counting 
 * the number of comments, which start with a hash ('#'), immediately after 
 * the descriptor.
 */
void Dataset::checkHeader() {
	
	ifstream file;
	string line;
	
	// Open file
	file.open(filename.c_str());
	if (!file)
		throw "Gander,Dataset: Could not open file to read header.";
	
	// Look for file descriptor
	getline(file, line);
	if (line.compare("VLIB.1") != 0)
		throw "Gander,Dataset: First line of header is not 'VLIB.1'.";
	headerOffset = 1;
	
	// Skip comments
	getline(file, line);
	while (line[0] == '#') {
		++headerOffset;
		getline(file, line);
	}
	
	// Finish
	file.close();
}



/**
 * Sets 'count' and allocates one of the data arrays.
 */
void Dataset::initData() {
	
	// Initialize all to NULL
	this->floatData = NULL;
	this->shortData = NULL;
	this->ubyteData = NULL;
	this->ushortData = NULL;
	
	// Calculate size of array
	count = size[0] * size[1] * size[2];
	
	// Allocate
	switch (typeEnum) {
		case GL_FLOAT :
			floatData = new float[count];
			break;
		case GL_SHORT :
			shortData = new short[count];
			break;
		case GL_UNSIGNED_BYTE : 
			ubyteData = new unsigned char[count];
			break;
		case GL_UNSIGNED_SHORT :
			ushortData = new unsigned short[count];
			break;
	}
}



/**
 * Decides which dimensions to use for width, height, and depth.
 */
void Dataset::initDimensions() {
	
	int best, x=size[0], y=size[1], z=size[2];
	map<int,int> differences;
	
	// Find differences
	differences.insert(make_pair(abs(x-y), 1));
	differences.insert(make_pair(abs(x-z), 2));
	differences.insert(make_pair(abs(y-z), 3));
	
	// Find best
	best = differences.begin()->second;
	switch (best) {
		case 1 :
			break;
		case 2 :
			cerr << "Gander,Dataset: Warning: x and z are best pair." << endl;
			break;
		case 3 :
			cerr << "Gander,Dataset: Warning: y and z are best pair." << endl;
			break;
	}
	setDimensions(x, y, z);
}



/**
 * Initializes 'typeEnum' for fast type checking.
 */
void Dataset::initTypeEnum() {
	
	// Convert string to enum
	if (typeString.compare("float") == 0)
		typeEnum = GL_FLOAT;
	else if (typeString.compare("int16") == 0)
		typeEnum = GL_SHORT;
	else if (typeString.compare("uint8") == 0)
		typeEnum = GL_UNSIGNED_BYTE;
	else if (typeString.compare("uint16") == 0)
		typeEnum = GL_UNSIGNED_SHORT;
	else
		throw "Gander,Dataset: Data type not currently supported.";
}



/**
 * Reads the details in the header and sets 'dataOffset'.
 * 
 * First calls 'checkHeader', then reads the size, type, endianness, pitch
 * minimum and maxium values, and the range of the data.  Also sets 
 * 'dataOffset', which is the number of lines that should be skipped in order 
 * to start reading the data.
 */
void Dataset::readHeader() {
	
	ifstream file;
	string line;
	
	// Validate
	checkHeader();
	
	// Open file, skip to offset
	file.open(filename.c_str());
	for (int i=0; i<headerOffset; ++i)
		getline(file, line);
	
	// Get details
	file >> size[0] >> size[1] >> size[2];
	file >> typeString;
	file >> endian;
	file >> pitch[0] >> pitch[1] >> pitch[2];
	file >> min >> max;
	file >> range[0] >> range[1];
	
	// Finish
	dataOffset = headerOffset + 6;
	file.close();
}



/**
 * Reads the data from the file into the data array.
 */
void Dataset::readData() {
	
	ifstream file;
	string line;
	
	// Open the file
	file.open(filename.c_str(), ios_base::binary);
	if (!file)
		throw "Gander,Dataset: Could not open file in binary mode.";
	
	// Skip everything up to the data
	for (int i=0; i<dataOffset; ++i)
		getline(file, line);
	
	// Read the data by type
	switch (typeEnum) {
		case GL_FLOAT :
			readDataAsFloat(file);
			break;
		case GL_SHORT :
			readDataAsShort(file);
			break;
		case GL_UNSIGNED_BYTE :
			readDataAsUByte(file);
			break;
		case GL_UNSIGNED_SHORT :
			readDataAsUShort(file);
			break;
	}
}



/**
 * Reads in the entire data section as floats.
 */
void Dataset::readDataAsFloat(ifstream &file) {
	
	unsigned char *ptr;
	
	// Reconstruct each float from four bytes
	for (int i=0; i<count; ++i) {
		ptr = reinterpret_cast<unsigned char*>(&floatData[i]);
		ptr[0] = file.get();
		ptr[1] = file.get();
		ptr[2] = file.get();
		ptr[3] = file.get();
	}
}



/**
 * Reads in the entire data section as signed shorts.
 */
void Dataset::readDataAsShort(ifstream &file) {
	
	unsigned char *ptr;
	
	// Reconstruct each short from two bytes
	for (int i=0; i<count; ++i) {
		ptr = reinterpret_cast<unsigned char*>(&shortData[i]);
		ptr[0] = file.get();
		ptr[1] = file.get();
	}
}



/**
 * Reads in the entire data section as unsigned bytes.
 */
void Dataset::readDataAsUByte(ifstream &file) {
	
	// Reconstruct each short from two bytes
	for (int i=0; i<count; ++i)
		ubyteData[i] = file.get();
}



/**
 * Reads in the entire data section as unsigned shorts.
 */
void Dataset::readDataAsUShort(ifstream &file) {
	
	unsigned char *ptr;
	
	// Reconstruct each short from two bytes
	for (int i=0; i<count; ++i) {
		ptr = reinterpret_cast<unsigned char*>(&ushortData[i]);
		ptr[0] = file.get();
		ptr[1] = file.get();
	}
}



/**
 * Sets width, height, and depth.
 */
void Dataset::setDimensions(int width,
                            int height,
                            int depth) {
	
	this->width = width;
	this->height = height;
	this->depth = depth;
}



/**
 * Prints details from the file header.
 */
void Dataset::print() const {
	
	// Path to file
	cout << filename << endl;
	
	// Attributes
	cout << left;
	cout << setw(12) << "  Width" << width << endl;
	cout << setw(12) << "  Height" << height << endl;
	cout << setw(12) << "  Depth" << depth << endl;
	cout << setw(12) << "  Type" << typeString << endl;
	cout << setw(12) << "  Endian" << endian << endl;
	cout << setw(12) << "  Min" << min << endl;
	cout << setw(12) << "  Max"<< max << endl;
	cout << setw(12) << "  Low" << range[0] << endl;
	cout << setw(12) << "  High" << range[1] << endl;
	cout << right;
}
