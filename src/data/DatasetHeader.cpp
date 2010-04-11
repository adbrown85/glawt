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
 * Reads a dataset header directly from an input stream.
 * 
 * @param [in] stream
 *     Input stream to read from.
 * 
 * @throws const_char* from check()
 */
DatasetHeader::DatasetHeader(istream &stream) {
	
	check(stream);
	read(stream);
}


/**
 * Checks if the file exists, then calls check(istream&).
 * 
 * @throws const_char* if the file could not be opened.
 */
void DatasetHeader::check() {
	
	ifstream file;
	
	// Open file and check it
	file.open(filename.c_str());
	if (!file) {
		ostringstream message;
		message << "[DatasetHeader] Could not open '"
		        << filename << "'." << endl;
		throw message.str().c_str();
	}
	check(file);
	file.close();
}


/**
 * Checks if the stream has a good header, then finds its beginning.
 * 
 * Determines if the header is good by reading the first line of the stream as 
 * text.  It will only be deemed appropriate if the first line is equal to 
 * @e VLIB.1.
 * 
 * To find the beginning of the actual information in the header, it continues 
 * reading the stream by skipping over any comments.  Note that comments are 
 * lines in which the first character is @e #.
 * 
 * At the end of the execution of this method, @c beginning will be set to the 
 * number of lines that should be skipped to get to the start of the metadata 
 * in the stream's header.  In other words, the next line after that will be 
 * the first line containing metadata.
 * 
 * @throws const_char* if the stream does not have an appropriate header.
 */
void DatasetHeader::check(istream &stream) {
	
	string line;
	
	// Look for descriptor
	getline(stream, line);
	if (line != "VLIB.1")
		throw "[DatasetHeader] First line of stream is not 'VLIB.1'.";
	beginning = 1;
	
	// Skip comments
	getline(stream, line);
	while (line[0] == '#') {
		comments.push_back(line.substr(1, line.length()-1));
		getline(stream, line);
	}
	beginning += comments.size();
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
	for (size_t i=0; i<comments.size(); ++i)
		cout << "    " << comments[i] << endl;
}


/**
 * Opens the file then calls read(istream&).
 */
void DatasetHeader::read() {
	
	ifstream file;
	
	// Open file and read it
	file.open(filename.c_str());
	read(file);
	file.close();
}


/**
 * Reads the details in the header and sets @c offset.
 * 
 * @see getOffset()
 */
void DatasetHeader::read(istream &stream) {
	
	string line;
	
	// Skip to beginning of details
	for (int i=0; i<beginning; ++i)
		getline(stream, line);
	
	// Get details
	stream >> width >> height >> depth;
	stream >> type;
	stream >> endian;
	stream >> pitch[0] >> pitch[1] >> pitch[2];
	stream >> min >> max;
	stream >> low >> high;
	
	// Finish
	offset = beginning + 6;
}


void DatasetHeader::write(ostream &stream) {
	
	// Descriptor and comments
	stream << "VLIB.1" << endl;
	for (size_t i=0; i<comments.size(); ++i) {
		stream << '#' << comments[i] << endl;
	}
	
	// Details
	stream << width << " " << height << " " << depth << endl;
	stream << type << endl;
	stream << endian << endl;
	stream << pitch[0] << " " << pitch[1] << " " << pitch[2] << endl;
	stream << min << " " << max << endl;
	stream << low << " " << high << endl;
}

