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


class VlbMaker {
	
	public:
		
		VlbMaker(const string &inFilename,
		         const string &outFilename);
		void process(istream &inStream,
		             ostream &outStream);
		void processData(istream &inStream,
		                 ostream &outStream);
		void processHeader(istream &inStream,
		                   ostream &outStream);
		void start();
	
	private:
		
		DatasetHeader header;
		string inFilename, outFilename;
};
