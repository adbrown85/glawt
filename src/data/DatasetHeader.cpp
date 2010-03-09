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
 * @param [in] filename
 *     Path to the file.
 * 
 * @throws const_char* from check()
 */
DatasetHeader::DatasetHeader(string filename) {
	
	// Initialize
	this->filename = filename;
	
	// Check and read
	check();
	read();
}



/**
 * Reads a header from a dataset file specified by an XML tag.
 * 
 * @param [in] tag
 *     XML tag with file attribute specifying path to the file.
 * 
 * @throws const_char* from check()
 */
DatasetHeader::DatasetHeader(const Tag &tag) {
	
	// Initialize
	tag.get("file", filename);
	
	// Check and read
	check();
	read();
}



/**
 * Checks if a file has a good header, then finds its beginning.
 * 
 * Determines if the header is good by reading the first line of the file as 
 * text.  It will only be deemed appropriate if the first line is equal to 
 * @e VLIB.1.
 * 
 * To find the beginning of the actual information in the header, it continues 
 * reading the file by skipping over any comments.  Note that comments are 
 * lines in which the first character is @e #.
 * 
 * At the end of the execution of this method, @c beginning will be set to the 
 * number of lines that should be skipped to get to the start of the metadata 
 * in the file's header.  In other words, the next line after that will be the 
 * first line containing metadata.
 * 
 * @throws const_char* if the file could not be opened.
 * @throws const_char* if the file does not have an appropriate header.
 */
void DatasetHeader::check() {
	
	ifstream file;
	string line;
	
	// Open file
	file.open(filename.c_str());
	if (!file)
		throw "[DatasetHeader] Could not open file.";
	
	// Look for file descriptor
	getline(file, line);
	if (line.compare("VLIB.1") != 0)
		throw "[DatasetHeader] First line of file is not 'VLIB.1'.";
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
 * 
 * @see getWidth()
 * @see getHeight()
 * @see getDepth()
 * @see getType()
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
 * Reads the details in the header and sets @c offset.
 * 
 * @see getOffset()
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

