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
Dataset::Dataset(const string &filename) : 
                 filename(filename),
                 data(NULL) {
	
	// Read the file
	readHeader();
	initData();
	readData();
}



/**
 * Deallocates the data array.
 */
Dataset::~Dataset() {
	
	if (data != NULL)
		delete[] data;
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
 * Sets 'length' and allocates the 'data' array.
 */
void Dataset::initData() {
	
	// Allocate new array
	length = size[0] * size[1] * size[2];
	data = new short[length];
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
	file >> type;
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
	
	short bytes[2];
	ifstream file;
	string line;
	
	// Open the file
	file.open(filename.c_str(), ios_base::binary);
	if (!file)
		throw "Gander,Dataset: Could not open file in binary mode.";
	
	// Skip everything up to the data
	for (int i=0; i<dataOffset; ++i)
		getline(file, line);
	
	// Read the data
	for (int i=0; i<length; ++i) {
		for (int j=0; j<2; ++j)
			bytes[j] = file.get();
		data[i] = (bytes[0]) | (bytes[1] << 8);
	}
}



/**
 * Prints details from the file header.
 */
void Dataset::print() const {
	
	cout << left;
	cout << setw(10) << "Size"
	     << size[0] << " " << size[1] << " " << size[2] << endl;
	cout << setw(10) << "Type" << type << endl;
	cout << setw(10) << "Endian" << endian << endl;
	cout << setw(10) << "Pitch"
	     << pitch[0] << " " << pitch[1] << " " << pitch[2] << endl;
	cout << setw(10) << "Min/max"
	     << min << " " << max << endl;
	cout << setw(10) << "Range"
	     << range[0] << " " << range[1] << endl;
	cout << right;
}
