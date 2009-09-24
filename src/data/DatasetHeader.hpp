/*
 * DatasetHeader.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASETHEADER_HPP
#define DATASETHEADER_HPP
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;



class DatasetHeader {
	
	
	public :
		
		DatasetHeader(string filename);
		void check();
		void print() const;
		void read();
		
		int getDepth() const {return depth;}
		string getFilename() const {return filename;}
		int getHeight() const {return height;}
		int getOffset() const {return offset;}
		string getType() const {return type;}
		int getWidth() const {return width;}
	
	
	private:
		
		float pitch[3];
		int beginning, offset;
		int high, low, max, min;
		int width, height, depth;
		string endian, filename, type;
		vector<string> comments;
};


#endif
