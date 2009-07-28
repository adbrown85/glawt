/*
 * Sequence.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Sequence.hpp"



Sequence::Sequence(string directory) {
	
	// Directory and basename
	this->directory = directory;
	verifyDirectory();
	initBasename();
	
	// Filenames
	initFilenames();
	verifyFilenames();
}



/**
 * Initializes 'basename' by removing the 
 */
void Sequence::initBasename() {
	
	int length, index;
	
	// Get length
	length = directory.length();
	
	// Forward slash separator
	index = directory.rfind('/');
	if (index < length) {
		basename = directory.substr(index+1, length-index-1);
		return;
	}
	
	// Backslash separator
	index = directory.rfind('\\');
	if (index < length) {
		basename = directory.substr(index+1, length-index-1);
		return;
	}
	
	// No separator found
	basename = directory;
}



/**
 * Initializes the 'filenames' list by looking in 'directory'
 */
void Sequence::initFilenames() {
	
	bool found;
	ifstream file;
	string filename, fullname;
	stringstream stream;
	
	// Get fullname
	fullname = directory + '/' + basename;
	
	// Add files to list
	found = true;
	for (int i=1; found; ++i) {
		stream.str("");
		stream << fullname << '.' << i;
		filename = stream.str();
		file.open(filename.c_str(), ios_base::binary);
		if (!file)
			found = false;
		else
			filenames.push_back(filename);
		file.close();
	}
}



/**
 * Prints all the filenames to standard error.
 */
void Sequence::printFilenames() const {
	
	int size;
	
	// Print all files
	size = filenames.size();
	for (int i=0; i<size; ++i)
		cerr << "  " << filenames[i] << endl;
}



/**
 * Makes sure directory is not the empty string and does not end in a 
 * trailing slash.
 */
void Sequence::verifyDirectory() {
	
	char last;
	int length, index;
	
	// Get length
	length = directory.length();
	if (length == 0)
		throw "Gander,Sequence: Empty directory string specified.";
	
	// Check for trailing slash
	last = directory[length-1];
	if (last == '/' || last == '\\')
		directory = directory.substr(0,length-1);
}



/**
 * Makes sure files were found.
 */
void Sequence::verifyFilenames() {
	
	string msg;
	
	// Check number of files found
	if (filenames.size() == 0) {
		msg =  "Gander,Sequence: No sequence files for '";
		msg += basename;
		msg += "' found in '";
		msg += directory;
		msg += "'.";
		throw msg.c_str();
	}
}
