/*
 * VlbMaker.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "VlbMaker.hpp"


VlbMaker::VlbMaker(const string &inFilename,
                   const string &outFilename) :
                   header(inFilename) {
	
	this->inFilename = inFilename;
	this->outFilename = outFilename;
}


void VlbMaker::start() {
	
	ifstream inFile;
	ofstream outFile;
	
	// Open files and process them
	inFile.open(inFilename.c_str());
	outFile.open(outFilename.c_str(), ios_base::binary);
	process(inFile, outFile);
	inFile.close();
	outFile.close();
}


void VlbMaker::process(istream &inStream,
                       ostream &outStream) {
	
	processHeader(inStream, outStream);
	processData(inStream, outStream);
}


void VlbMaker::processData(istream &inStream,
                           ostream &outStream) {
	
	int sample;
	
	// Read data
	inStream >> sample;
	while (inStream) {
		outStream.put((char)sample);
		inStream >> sample;
	}
}


void VlbMaker::processHeader(istream &inStream,
                             ostream &outStream) {
	
	int offset;
	string line;
	
	// Write header
	header.write(outStream);
	
	// Skip past header in input
	offset = header.getOffset();
	for (int i=0; i<offset; ++i) {
		getline(inStream, line);
	}
}

