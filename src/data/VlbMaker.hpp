/*
 * VlbMaker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "DatasetHeader.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Creates a VLB file from a text file.
 * 
 * The text file should follow the basic form of a VLB file, except the data is 
 * human readable.  In fact, the header is exactly the same, and DatasetHeader 
 * is even used to process it.  The data meanwhile is read in one slice at a 
 * time from front to back.  Each slice starts with the bottom left row and 
 * then proceeds upwards through the rows.  Each value should be separated by 
 * spaces, and line breaks do not matter within the data section, so feel free 
 * to format the data as you wish.  Data is written out as unsigned bytes with 
 * no spaces.
 * 
 * @note Currently the only type supported is <i>unit8</i> (unsigned bytes).
 * 
 * @see DatasetHeader
 */
class VlbMaker {
	
	public:
		
		VlbMaker(const string &inFilename,
		         const string &outFilename);
		void start();
	
	protected:
		
		void process(istream &inStream,
		             ostream &outStream);
		void processData(istream &inStream,
		                 ostream &outStream);
		void processHeader(istream &inStream,
		                   ostream &outStream);
	
	private:
		
		DatasetHeader header;
		string inFilename, outFilename;
};

