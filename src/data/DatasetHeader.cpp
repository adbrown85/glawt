/*
 * DatasetHeader.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetHeader.hpp"



/**
 * Reads a header from a dataset file.
 * 
 * @param filename
 *     Path to the file.
 */
DatasetHeader::DatasetHeader(string filename) {
	
	// Initialize
	this->filename = filename;
	
	// Check and read
	check();
	read();
}



/**
 * Creates a new %DatasetHeader from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
DatasetHeader::DatasetHeader(const Tag &tag) {
	
	// Initialize
	tag.get("file", filename);
	
	// Check and read
	check();
	read();
}



/**
 * Checks if a file has a good header and finds its beginning.
 */
void DatasetHeader::check() {
	
	ifstream file;
	string line;
	
	// Open file
	file.open(filename.c_str());
	if (!file)
		throw "Gander,DatasetHeader: Could not open file.";
	
	// Look for file descriptor
	getline(file, line);
	if (line.compare("VLIB.1") != 0)
		throw "Gander,DatasetHeader: First line of file is not 'VLIB.1'.";
	beginning = 1;
	
	// Skip comments
	getline(file, line);
	while (line[0] == '#') {
		comments.push_back(line.substr(1, line.length()-1));
		getline(file, line);
	}
	beginning += comments.size();
	
	// Finish
	file.close();
}



/**
 * Prints details of the header.
 */
void DatasetHeader::print() const {
	
	// Filename
	cout << filename << endl;
	
	// Attributes
	cout << left;
	cout << setw(12) << "  Width" << width << endl;
	cout << setw(12) << "  Height" << height << endl;
	cout << setw(12) << "  Depth" << depth << endl;
	cout << setw(12) << "  Type" << type << endl;
	cout << setw(12) << "  Endian" << endian << endl;
	cout << setw(12) << "  Min" << min << endl;
	cout << setw(12) << "  Max"<< max << endl;
	cout << setw(12) << "  Low" << low << endl;
	cout << setw(12) << "  High" << high << endl;
	if (comments.size() > 0)
		cout << setw(12) << "  Comments" << endl;
	cout << right;
	for (int i=0; i<comments.size(); ++i)
		cout << "    " << comments[i] << endl;
}



/**
 * Reads the details in the header and sets 'offset'.
 */
void DatasetHeader::read() {
	
	ifstream file;
	string line;
	
	// Open file, skip to beginning of details
	file.open(filename.c_str());
	for (int i=0; i<beginning; ++i)
		getline(file, line);
	
	// Get details
	file >> width >> height >> depth;
	file >> type;
	file >> endian;
	file >> pitch[0] >> pitch[1] >> pitch[2];
	file >> min >> max;
	file >> low >> high;
	
	// Finish
	offset = beginning + 6;
	file.close();
}

